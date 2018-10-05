#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

bool IsUnique(const unsigned *arr, const size_t length, const unsigned target, FILE *fp);
void MakeRandArray(unsigned *arr, const size_t length, const unsigned min, const unsigned max);
void MakeFileByRandArray(const unsigned *arr, const size_t length);

int main(void)
{
  // int 32位长
  // 7位十进制正整数，使用 unsgined
  // [min, max] 闭区间
  const unsigned kMin = 1000000;
  const size_t kLength = 1000000;
  const unsigned kMax = 9999999;
  unsigned arr[kLength];
  MakeRandArray(arr, kLength, kMin, kMax);
  MakeFileByRandArray(arr, kLength);
  return 0;
}

bool IsUnique(const unsigned *arr, const size_t length, const unsigned target, FILE *fp)
{
  bool result = true;
  size_t i;

  for (i = 0; i < length; i++)
  {
    if (arr[i] == target)
    {
      result = false;
      fprintf(fp, "%zu\n", i);
      break;
    }
  }
  return result;
}

void MakeRandArray(unsigned *arr, const size_t length, const unsigned min, const unsigned max)
{
  srand((unsigned)time(NULL));
  FILE *fp;
  const char *kFileName = "rand_times.log";
  if (!(fp = fopen(kFileName, "w")))
  {
    fprintf(stderr, "Failed to open file %s\n", kFileName);
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < length; i++)
  {
    unsigned _rand = (unsigned)rand() % max;
    while (_rand < min || !IsUnique(arr, i, _rand, fp))
      _rand = (unsigned)rand() % max + 1;

    arr[i] = _rand;
  }
  if (fclose(fp))
    fprintf(stderr, "Failed to close %s\n", kFileName);
}

void MakeFileByRandArray(const unsigned *arr, const size_t length)
{
  const char *const kFileName = "rand.txt";
  FILE *fp;
  if (!(fp = fopen(kFileName, "w")))
  {
    fprintf(stderr, "Failed to open file %s\n", kFileName);
    exit(EXIT_FAILURE);
  }

  for (size_t i = 0; i < length; i++)
    fprintf(fp, "%u\n", arr[i]);

  if (fclose(fp))
    fprintf(stderr, "Failed to close %s\n", kFileName);

  fprintf(stdout, "The program is done\n");
}