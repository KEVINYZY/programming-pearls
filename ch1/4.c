#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
// [min, max)
const size_t kDivideConut = 2500;
const size_t kLength = 7000000;
const unsigned kMin = 1000000;
const unsigned kMax = 10000000;
const size_t kUnit = kLength / kDivideConut;
const size_t kUnitReminder = kLength % kDivideConut;
const unsigned kInterval = (kMax - kMin) / kDivideConut;
const char *kFileName = "rand.txt";

bool IsUnique(const unsigned *arr, const size_t length, const unsigned target);
void MakeRandArray(unsigned *arr, const size_t length, const unsigned min, const unsigned max, FILE *fp);
void DividArray(void);

int main(void)
{
  // const unsigned kStart = time(NULL);
  DividArray();
  // printf("Time %us\n", (unsigned)time(NULL) - kStart);
  return 0;
}

void DividArray(void)
{
  // int 32位长
  // 7位十进制正整数，使用 unsgined
  // TODO 够简短高效吗？
  FILE *fp;
  if (!(fp = fopen(kFileName, "w")))
  {
    fprintf(stderr, "Failed to open file %s\n", kFileName);
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < kDivideConut; i++)
  {
    bool last_index = i + 1 == kDivideConut;
    size_t length = last_index ? kUnit + kUnitReminder : kUnit;
    unsigned min = kMin + i * kInterval;
    unsigned max = last_index ? kMax : min + kInterval;
    unsigned arr[length];

    MakeRandArray(arr, length, min, max, fp);
    fprintf(stdout, "Processing %zu/%zu\r", i, kDivideConut);
  }

  if (fclose(fp))
    fprintf(stderr, "Failed to close %s\n", kFileName);
}

bool IsUnique(const unsigned *arr, const size_t length, const unsigned target)
{
  bool result = true;
  for (size_t i = 0; i < length; i++)
  {
    if (arr[i] == target)
    {
      result = false;
      break;
    }
  }
  return result;
}

void MakeRandArray(unsigned *arr, const size_t length, const unsigned min, const unsigned max, FILE *fp)
{
  srand((unsigned)time(NULL));
  for (size_t i = 0; i < length; i++)
  {
    unsigned _rand = (unsigned)rand() % max;
    while (_rand < min || !IsUnique(arr, i, _rand))
      _rand = (unsigned)rand() % max;

    arr[i] = _rand;
    fprintf(fp, "%u\n", _rand);
  }
}