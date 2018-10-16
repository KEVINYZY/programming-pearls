// 内存使用小于 1Mib
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
const unsigned kMax = 10000000;
const size_t kDivideCount = 10;
const size_t kLength = kMax / kDivideCount;
const char *const kSortFilename = "sort.txt";
const char kMinCount = 'A',
           kMaxCount = 'K';
void InitializeArray(char *arr);
void ReadArrayFromFile(char *arr, const char *const filename, size_t index);
void WriteFileFromArray(const char *const arr, size_t index);

int main(int argc, char *argv[])
{
  const unsigned kStart = time(NULL);
  if (argc < 2)
  {
    fprintf(stderr, "需要指定输入文件。\n");
    exit(EXIT_FAILURE);
  }

  const char *const kFilename = argv[1];
  for (size_t i = 0; i < kDivideCount; i++)
  {
    char vector_array[kLength];
    InitializeArray(vector_array);
    ReadArrayFromFile(vector_array, kFilename, i);
    WriteFileFromArray(vector_array, i);
  }
  printf("Time %us\n", (unsigned)time(NULL) - kStart);
  return 0;
}

void InitializeArray(char *arr)
{
  for (size_t i = 0; i < kLength; i++)
    arr[i] = kMinCount;
}

void ReadArrayFromFile(char *arr, const char *const filename, size_t index)
{
  // 扫描整个文件，把在当前区间的号码读取出来
  // 比如当前号码区间是 [0, 100000)
  // 扫描整个文件后，只把属于这个区间的号码保留，其余丢弃
  // 下次，再次扫描整个文件，把属于 [100000, 200000) 的号码读取出来
  // 每次只有一个固定长度的数组在内存中，从而限制内存使用
  FILE *fp;
  unsigned value;
  if (!(fp = fopen(filename, "r")))
  {
    fprintf(stderr, "Failed to open file %s\n", filename);
    exit(EXIT_FAILURE);
  }
  while (fscanf(fp, "%u", &value) > 0)
  {
    value = value - kLength * index;
    if (value >= 0 && value < kLength)
      arr[value] += 1;
  }

  if (fclose(fp))
    fprintf(stderr, "Failed to close %s\n", filename);
}

void WriteFileFromArray(const char *const arr, size_t index)
{
  FILE *fp;
  if (!(fp = fopen(kSortFilename, index ? "a" : "w")))
  {
    fprintf(stderr, "Failed to open file %s\n", kSortFilename);
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < kLength; i++)
  {
    for (size_t j = kMinCount; j < arr[i]; j++)
      fprintf(fp, "%u\n", (unsigned)(i + kLength * index));
  }
  if (fclose(fp))
    fprintf(stderr, "Failed to close %s\n", kSortFilename);
}
