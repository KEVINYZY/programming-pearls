// 1M 内存限制
// 将区号存储于数组 [800, 877, 888] 中
// 结构体中的 area_code 存放区号数组的元素索引，以此类推
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

const unsigned kMax = 10000000;
const size_t kAreaCodeLength = 3,
             kDivideCount = 10,
             kLength = kMax / kDivideCount;
const unsigned short kAreaCode[kAreaCodeLength] = {800, 877, 888};
const char *const kInputFile = "8.rand.txt";
const char *const kOutputFile = "8.sort.txt";

void InitializeArray(bool *arr);
void ReadArrayFromFile(bool *arr, size_t index, size_t area_code_index);
void WriteFileFromArray(const bool *const arr, size_t index, size_t area_code_index);

int main(void)
{
  for (size_t i = 0; i < kAreaCodeLength; i++)
  {
    const unsigned kStart = time(NULL);
    unsigned short area_code = kAreaCode[i];
    fprintf(stdout, "开始排序区号 %hu\n", area_code);
    for (size_t j = 0; j < kDivideCount; j++)
    {
      bool vector_array[kLength];
      InitializeArray(vector_array);
      ReadArrayFromFile(vector_array, j, i);
      WriteFileFromArray(vector_array, j, i);
    }
    fprintf(stdout, "耗时 %us\n", (unsigned)time(NULL) - kStart);
  }
  return 0;
}

void InitializeArray(bool *arr)
{
  for (size_t i = 0; i < kLength; i++)
    arr[i] = false;
}

void ReadArrayFromFile(bool *arr, size_t index, size_t area_code_index)
{
  const unsigned kStart = time(NULL);
  FILE *fp;
  unsigned short area_code;
  unsigned number;
  unsigned count = 0;
  if (!(fp = fopen(kInputFile, "r")))
  {
    fprintf(stderr, "Failed to open file %s\n", kInputFile);
    exit(EXIT_FAILURE);
  }

  while (count < kLength && fscanf(fp, "%hu-%7u", &area_code, &number) > 0)
  {
    number = number - kLength * index;
    if (area_code == kAreaCode[area_code_index] &&
        number >= 0 &&
        number < kLength)
    {
      arr[number] = true;
      count++;
    }
  }

  if (fclose(fp))
    fprintf(stderr, "Failed to close %s\n", kInputFile);

  fprintf(stdout, "Read  %us\n", (unsigned)time(NULL) - kStart);
}

void WriteFileFromArray(const bool *const arr, size_t index, size_t area_code_index)
{
  const unsigned kStart = time(NULL);
  FILE *fp;
  if (!(fp = fopen(kOutputFile, !area_code_index && !index ? "w" : "a")))
  {
    fprintf(stderr, "Failed to open file %s\n", kOutputFile);
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < kLength; i++)
  {
    if (arr[i])
      fprintf(fp, "%hu-%07u\n", kAreaCode[area_code_index], (unsigned)(i + kLength * index));
  }
  if (fclose(fp))
    fprintf(stderr, "Failed to close %s\n", kOutputFile);

  fprintf(stdout, "Write %us\n", (unsigned)time(NULL) - kStart);
}
