#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

bool IsUnique(const unsigned *arr, const size_t length, const unsigned target);
void MakeRandArray(unsigned *arr, const size_t length, const unsigned min, const unsigned max);
void MakeFileByRandArray(const unsigned *arr, const size_t length, const char *file_name);

int main(void)
{
  // int 32位长
  // 7位十进制正整数，使用 unsgined
  // [min, max] 闭区间
  const size_t kLength = 1000000;
  const unsigned kMin = 1000000;
  const unsigned kMax = 9999999;
  unsigned arr[kLength];
  MakeRandArray(arr, kLength, kMin, kMax);
  MakeFileByRandArray(arr, kLength, "rand_int.txt");
  return 0;
}

bool IsUnique(const unsigned *arr, const size_t length, const unsigned target)
{
  bool result = true;
  // TODO 需要提升效率
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

void MakeRandArray(unsigned *arr, const size_t length, const unsigned min, const unsigned max)
{
  srand((unsigned)time(NULL));
  for (size_t i = 0; i < length; i++)
  {
    unsigned _rand = (unsigned)rand() % max;
    while (_rand < min || !IsUnique(arr, i, _rand))
      _rand = (unsigned)rand() % max + 1;

    arr[i] = _rand;
  }
}

void MakeFileByRandArray(const unsigned *arr, const size_t length, const char *file_name)
{
  FILE *fp;
  if (!(fp = fopen(file_name, "w")))
  {
    fprintf(stderr, "Failed to open file %s\n", file_name);
    exit(EXIT_FAILURE);
  }

  for (size_t i = 0; i < length; i++)
    fprintf(fp, "%u\n", arr[i]);

  if (fclose(fp))
    fprintf(stderr, "Failed to close %s\n", file_name);
}