// 内存使用小于 1Mib
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
const unsigned kMax = 10000000;
const size_t kDivideCount = 10;
const size_t kLength = kMax / kDivideCount;
const char *kSortFileName = "sort.txt";
const char kMinCount = 'A',
           kMaxCount = 'K';
void InitializeArray(char *arr);
void ReadArrayFromFile(char *arr, const char *const file_name, size_t index);
void WriteFileFromArray(const char *const arr, size_t index);

int main(int argc, char *argv[])
{
  const unsigned kStart = time(NULL);
  if (argc < 2)
  {
    fprintf(stderr, "需要指定输入文件。\n");
    exit(EXIT_FAILURE);
  }

  const char *const kFileName = argv[1];
  for (size_t i = 0; i < kDivideCount; i++)
  {
    char vector_array[kLength];
    InitializeArray(vector_array);
    ReadArrayFromFile(vector_array, kFileName, i);
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

void ReadArrayFromFile(char *arr, const char *const file_name, size_t index)
{
  FILE *fp;
  char string_value[8];
  size_t value;
  if (!(fp = fopen(file_name, "r")))
  {
    fprintf(stderr, "Failed to open file %s\n", file_name);
    exit(EXIT_FAILURE);
  }
  while (fscanf(fp, "%s", string_value) == 1)
  {
    value = (size_t)(strtoull(string_value, NULL, 10) - kLength * index);
    if (value >= 0 && value < kLength)
      arr[value] += 1;
  }
  if (fclose(fp))
    fprintf(stderr, "Failed to close %s\n", file_name);
}

void WriteFileFromArray(const char *const arr, size_t index)
{
  FILE *fp;
  if (!(fp = fopen(kSortFileName, index ? "a" : "w")))
  {
    fprintf(stderr, "Failed to open file %s\n", kSortFileName);
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < kLength; i++)
  {
    for (size_t j = kMinCount; j < arr[i]; j++)
      fprintf(fp, "%u\n", (unsigned)(i + kLength * index));
  }
  if (fclose(fp))
    fprintf(stderr, "Failed to close %s\n", kSortFileName);
}
