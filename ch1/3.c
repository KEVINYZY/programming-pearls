// 不限制内存的方式，需要 8789KiB 内存
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
const unsigned kMax = 10000000;
const char *kSortFileName = "sort.txt";

void ReadArrayFromFile(bool *arr, const char *const file_name);
void WriteFileFromArray(const bool *const arr);

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    fprintf(stderr, "需要指定输入文件。\n");
    exit(EXIT_FAILURE);
  }

  const char *const kFileName = argv[1];
  bool *vector_array;
  if (!(vector_array = (bool *)malloc(sizeof(bool) * kMax)))
  {
    fprintf(stderr, "Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }
  ReadArrayFromFile(vector_array, kFileName);
  WriteFileFromArray(vector_array);
  free(vector_array);
  return 0;
}

void ReadArrayFromFile(bool *arr, const char *const file_name)
{
  FILE *fp;
  char string_value[8];
  unsigned value;
  if (!(fp = fopen(file_name, "r")))
  {
    fprintf(stderr, "Failed to open file %s\n", file_name);
    exit(EXIT_FAILURE);
  }
  while (fscanf(fp, "%s", string_value) == 1)
  {
    value = (unsigned)strtoull(string_value, NULL, 10);
    arr[value] = true;
  }
  if (fclose(fp))
    fprintf(stderr, "Failed to close %s\n", file_name);
}

void WriteFileFromArray(const bool *const arr)
{
  FILE *fp;
  if (!(fp = fopen(kSortFileName, "w")))
  {
    fprintf(stderr, "Failed to open file %s\n", kSortFileName);
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < kMax; i++)
  {
    if (arr[i])
      fprintf(fp, "%u\n", (unsigned)i);
  }
  if (fclose(fp))
    fprintf(stderr, "Failed to close %s\n", kSortFileName);
}