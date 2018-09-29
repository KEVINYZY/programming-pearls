#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

bool IsUnique(const unsigned long *arr, const unsigned long length, const unsigned long target);
void MakeRandArray(unsigned long *arr, const unsigned long length, const unsigned long min, const unsigned long max);
void MakeFileByRandArray(const unsigned long *arr, const unsigned long length, const char *file_name);

int main(void)
{
  // 7位十进制整数，需要 unsigned long
  // [min, max] 闭区间
  const unsigned long length = 10;
  const unsigned long min = 10;
  const unsigned long max = 19;
  unsigned long arr[length];
  MakeRandArray(arr, length, min, max);
  MakeFileByRandArray(arr, length, "rand_int.txt");
  return 0;
}

bool IsUnique(const unsigned long *arr, const unsigned long length, const unsigned long target)
{
  bool result = true;
  for (unsigned long i = 0; i < length; i++)
  {
    if (arr[i] == target)
    {
      result = false;
      break;
    }
  }
  return result;
}

void MakeRandArray(unsigned long *arr, const unsigned long length, const unsigned long min, const unsigned long max)
{
  srand((unsigned int)time(NULL));
  for (unsigned long i = 0; i < length; i++)
  {
    int _rand = rand() % max;
    while (_rand < min || !IsUnique(arr, i, _rand))
      _rand = rand() % max + 1;

    arr[i] = _rand;
  }
}

void MakeFileByRandArray(const unsigned long *arr, const unsigned long length, const char *file_name)
{
  FILE *fp;
  if (!(fp = fopen(file_name, "w")))
  {
    fprintf(stderr, "Failed to open file %s\n", file_name);
    exit(EXIT_FAILURE);
  }

  for (unsigned long i = 0; i < length; i++)
    fprintf(fp, "%lu\n", arr[i]);

  if (fclose(fp))
    fprintf(stderr, "Failed to close %s\n", file_name);
}