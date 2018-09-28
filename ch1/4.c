#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

bool IsUnique(const int *arr, const int length, const int target);
void MakeRandArray(int *arr, const int count, const int max);
void MakeFileByRandArray(const int *arr, const int length, const char *file_name);

int main(void)
{
  // 1000万的数字大小，可能需要用 long 或者 long long
  const int length = 10000;
  const int max = 20000;
  int arr[length];
  MakeRandArray(arr, length, max);
  MakeFileByRandArray(arr, length, "rand_int.txt");
  return 0;
}

bool IsUnique(const int *arr, const int length, const int target)
{
  bool result = true;
  int i = 0;
  while (i < length)
  {
    if (arr[i] == target)
    {
      result = false;
      break;
    }
    i++;
  }
  return result;
}

void MakeRandArray(int *arr, const int length, const int max)
{
  srand((unsigned int)time(NULL));
  int i = 0;
  while (i < length)
  {
    int _rand = rand() % max;
    while (_rand == 0 || !IsUnique(arr, i, _rand))
      _rand = rand() % max;

    arr[i] = _rand;
    i++;
  }
}

void MakeFileByRandArray(const int *arr, const int length, const char *file_name)
{
  FILE *fp;
  if (!(fp = fopen(file_name, "w")))
  {
    fprintf(stderr, "Failed to open file %s\n", file_name);
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < length; i++)
    fprintf(fp, "%d\n", arr[i]);

  if (fclose(fp))
    fprintf(stderr, "Failed to close %s\n", file_name);
}