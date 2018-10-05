#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "_sort.h"
const char *kSortFileName = "sort.txt";

void ReadArrayFromFile(bool *arr, const char *const file_name);
void WriteFileFromArray(bool *arr);

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    fprintf(stderr, "Program required a file name.\n");
    exit(EXIT_FAILURE);
  }

  const char *const kFileName = argv[1];
  bool *vector_array;
  if (!(vector_array = (bool *)malloc(sizeof(bool) * (kMax - kMin))))
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
    arr[value - kMin] = true;
  }
  if (fclose(fp))
    fprintf(stderr, "Failed to close %s\n", file_name);
}

void WriteFileFromArray(bool *arr)
{
  FILE *fp;
  if (!(fp = fopen(kSortFileName, "w")))
  {
    fprintf(stderr, "Failed to open file %s\n", kSortFileName);
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < kMax - kMin; i++)
  {
    if (arr[i])
      fprintf(fp, "%u\n", (unsigned)i + kMin);
  }
  if (fclose(fp))
    fprintf(stderr, "Failed to close %s\n", kSortFileName);
}