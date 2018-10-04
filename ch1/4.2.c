#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
const size_t kDivideConut = 2;
const size_t kLength = 10;
const unsigned kMin = 10;
const unsigned kMax = 20;
const size_t kUnit = kLength / kDivideConut;
const size_t kUnitReminder = kLength % kDivideConut;
const unsigned kInterval = (kMax - kMin) / kDivideConut;
const char *kFileName = "rand.txt";

size_t GetLength(const size_t index);
bool IsUnique(unsigned *arr[], const unsigned target);
void MakeSectionArray(unsigned *arr[]);
void MakeRandArray(unsigned *arr);
void MakeFileByRandArray(const unsigned *arr);

int main(void)
{
  // int 32位长
  // 7位十进制正整数，使用 unsgined
  // [kMin, kMax) 区间
  printf("sizeof kLength %zu\n", sizeof(kLength));
  // return 0;
  printf("kUnit %zu\n", kUnit);
  printf("kUnitReminder %zu\n", kUnitReminder);
  printf("kInterval %u\n", kInterval);
  const unsigned kStart = time(NULL);
  unsigned arr[kLength];
  MakeRandArray(arr);
  MakeFileByRandArray(arr);
  printf("Take time %u s\n", (unsigned)time(NULL) - kStart);
  return 0;
}

size_t GetLength(const size_t index)
{
  const bool kIsLastEle = index + 1 == kDivideConut;
  return kIsLastEle ? kUnit + kUnitReminder : kUnit;
}

bool IsUnique(unsigned *arr[], const unsigned target)
{
  bool result = true;
  const size_t index = (target - kMin) / kInterval;
  const size_t length = GetLength(index);
  printf("index %zu\n", index);
  printf("length %zu\n", length);
  for (size_t i = 0; i < length; i++)
  {
    printf("arr[%zu][%zu] %u\n", index, i, arr[index][i]);
    if (arr[index][i] == 0)
    {
      arr[index][i] = target;
      break;
    }

    if (arr[index][i] == target)
    {
      result = false;
      break;
    }
  }
  printf("result %d\n", result);
  return result;
}

void MakeSectionArray(unsigned *arr[])
{
  for (size_t i = 0; i < kDivideConut; i++)
  {
    const size_t length = GetLength(i);
    printf("MakeSectionArray length %zu\n", length);
    for (size_t j = 0; j < length; j++)
      arr[i][j] = 0;
  }
}

void MakeRandArray(unsigned *arr)
{
  srand((unsigned)time(NULL));
  unsigned *temp_arr[kDivideConut];
  MakeSectionArray(temp_arr);

  for (size_t i = 0; i < kLength; i++)
  {
    unsigned _rand = rand() % kMax;
    printf("_rand %u\n", _rand);
    while (_rand < kMin || !IsUnique(temp_arr, _rand))
    {
      _rand = (unsigned)rand() % kMax;
      printf("_rand %u\n", _rand);
    }

    // 显示进度条会影响性能
    // printf("The processing is %zu/%zu\r", i, kLength);
    arr[i] = _rand;
  }
}

void MakeFileByRandArray(const unsigned *arr)
{
  FILE *fp;
  if (!(fp = fopen(kFileName, "w")))
  {
    fprintf(stderr, "Failed to open file %s\n", kFileName);
    exit(EXIT_FAILURE);
  }

  for (size_t i = 0; i < kLength; i++)
    fprintf(fp, "%u\n", arr[i]);

  if (fclose(fp))
    fprintf(stderr, "Failed to close %s\n", kFileName);
}