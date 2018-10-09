// 生成 800W 个属于区间[0, 10000000)的随机整数，每个整数最多出现10次。
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
const size_t kDivideConut = 2500,
             kLength = 8000000;
const unsigned kMax = 10000000;
const char kMinCount = 'A',
           kMaxCount = 'K';
typedef struct Rand
{
  unsigned number;
  char count;
} Rand;

void DividArray(const char *const file_name);
void InitializeArray(Rand *arr, size_t length);
bool MakeNewRand(Rand *arr, size_t length, unsigned target);
size_t SumCount(const Rand *const arr, size_t length);
void FillArray(Rand *arr, size_t length, unsigned min, unsigned max);
void WriteArrayToFile(const Rand *const arr, size_t length, const char *const file_name, const char *const open_mode);

int main(int argc, char *argv[])
{
  // const unsigned kStart = time(NULL);
  if (argc < 2)
  {
    fprintf(stderr, "需要指定输出文件。\n");
    exit(EXIT_FAILURE);
  }
  const char *const kFileName = argv[1];
  DividArray(kFileName);
  // printf("Time %us\n", (unsigned)time(NULL) - kStart);
  return 0;
}

void DividArray(const char *const file_name)
{
  // int 32位长
  // 7位十进制正整数，使用 unsgined
  const size_t kUnit = kLength / kDivideConut;
  const size_t kUnitReminder = kLength % kDivideConut;
  const unsigned kInterval = kMax / kDivideConut;
  for (size_t i = 0; i < kDivideConut; i++)
  {
    bool last_index = i + 1 == kDivideConut;
    size_t length = last_index ? kUnit + kUnitReminder : kUnit;
    unsigned min = i * kInterval;
    unsigned max = last_index ? kMax : min + kInterval;
    Rand arr[length];

    InitializeArray(arr, length);
    FillArray(arr, length, min, max);
    WriteArrayToFile(arr, length, file_name, i ? "a" : "w");

    fprintf(stdout, "Processing %zu/%zu\r", i, kDivideConut);
  }
}

void InitializeArray(Rand *arr, size_t length)
{
  for (size_t i = 0; i < length; i++)
    arr[i].count = kMinCount;
}

bool MakeNewRand(Rand *arr, size_t length, unsigned target)
{
  bool result = false;
  for (size_t i = 0; i < length; i++)
  {
    if (arr[i].number == target)
    {
      if (arr[i].count < kMaxCount)
        arr[i].count += 1;

      result = true;
      break;
    }
  }
  return result;
}

size_t SumCount(const Rand *const arr, size_t length)
{
  size_t sum = 0;
  for (size_t i = 0; i < length; i++)
    sum += (size_t)(arr[i].count - 'A');
  return sum;
}

void FillArray(Rand *arr, size_t length, unsigned min, unsigned max)
{
  srand((unsigned)time(NULL));
  for (size_t i = 0; i < length; i++)
  {
    unsigned _rand = (unsigned)rand() % max;
    while (_rand < min ||
           (SumCount(arr, i) < length && MakeNewRand(arr, i, _rand)))
      _rand = (unsigned)rand() % max;

    if (SumCount(arr, i) >= length)
      break;

    arr[i].number = _rand;
    arr[i].count += 1;
  }
}

void WriteArrayToFile(const Rand *const arr, size_t length, const char *const file_name, const char *const open_mode)
{
  FILE *fp;
  if (!(fp = fopen(file_name, open_mode)))
  {
    fprintf(stderr, "Failed to open file %s\n", file_name);
    exit(EXIT_FAILURE);
  }

  for (size_t i = 0; i < length; i++)
  {
    for (char j = kMinCount; j < arr[i].count; j++)
      fprintf(fp, "%u\n", arr[i].number);
  }

  if (fclose(fp))
    fprintf(stderr, "Failed to close %s\n", file_name);
}