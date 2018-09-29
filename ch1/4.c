#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

bool IsUnique(const unsigned *arr, const unsigned length, const unsigned target);
void MakeRandArray(unsigned *arr, const unsigned length, const unsigned min, const unsigned max);
void MakeFileByRandArray(const unsigned *arr, const unsigned length, const char *file_name);

int main(void)
{
  // int 32位长
  // 7位十进制正整数，使用 unsgined
  // [min, max] 闭区间
  const unsigned length = 1000000;
  const unsigned min = 1000000;
  const unsigned max = 9999999;
  unsigned arr[length];
  MakeRandArray(arr, length, min, max);
  MakeFileByRandArray(arr, length, "rand_int.txt");
  return 0;
}

bool IsUnique(const unsigned *arr, const unsigned length, const unsigned target)
{
  bool result = true;
  for (unsigned i = 0; i < length; i++)
  {
    if (arr[i] == target)
    {
      result = false;
      break;
    }
  }
  return result;
}

void MakeRandArray(unsigned *arr, const unsigned length, const unsigned min, const unsigned max)
{
  srand((unsigned)time(NULL));
  for (unsigned i = 0; i < length; i++)
  {
    unsigned _rand = (unsigned)rand() % max;
    while (_rand < min || !IsUnique(arr, i, _rand))
      _rand = (unsigned)rand() % max + 1;

    arr[i] = _rand;
  }
}

void MakeFileByRandArray(const unsigned *arr, const unsigned length, const char *file_name)
{
  FILE *fp;
  if (!(fp = fopen(file_name, "w")))
  {
    fprintf(stderr, "Failed to open file %s\n", file_name);
    exit(EXIT_FAILURE);
  }

  for (unsigned i = 0; i < length; i++)
    fprintf(fp, "%u\n", arr[i]);

  if (fclose(fp))
    fprintf(stderr, "Failed to close %s\n", file_name);
}