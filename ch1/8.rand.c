// 将区号存储于数组 [800, 877, 888] 中
// 结构体中的 area_code 存放区号数组的元素索引，以此类推
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct Phone
{
  char area_code;
  unsigned number;
} Phone;

const size_t kAreaCodeLength = 3,
             kDivideConut = 2500,
             kLength = 8000000;
const unsigned short kAreaCode[kAreaCodeLength] = {800, 877, 888};
const unsigned kMax = 10000000;
const char *const kRandFileName = "8.rand.txt";

static size_t phone_number_index = 0;
static Phone phone_number[kAreaCodeLength * kLength];

void MakeRandArray(Phone *arr, size_t length, unsigned min, unsigned max);
bool IsUnique(const Phone *const arr, size_t length, unsigned target);
void DividArray(char area_code_index);
void LoopAreaCode();
void InitializePhone(Phone *arr, size_t length, char area_code_index);
void AppendPhoneNumber(Phone phone);
void Disorder();
void MakeFile();

int main(int argc, char *argv[])
{
  // const unsigned kStart = time(NULL);
  const char *const kFileName = argv[1];
  LoopAreaCode();
  Disorder();
  MakeFile();
  // printf("Time %us\n", (unsigned)time(NULL) - kStart);
  return 0;
}

void MakeFile()
{
  FILE *fp;
  if (!(fp = fopen(kRandFileName, "w")))
  {
    fprintf(stderr, "Failed to open file %s\n", kRandFileName);
    exit(EXIT_FAILURE);
  }

  for (size_t i = 0; i < kAreaCodeLength * kLength; i++)
    fprintf(fp,
            "%hu-%07u\n",
            kAreaCode[phone_number[i].area_code], phone_number[i].number);

  if (fclose(fp))
    fprintf(stderr, "Failed to close %s\n", kRandFileName);
}

// 将数组乱序，因为相同区号的号码在一起
void Disorder()
{
  srand((unsigned)time(NULL));
  size_t length = kAreaCodeLength * kLength;
  for (size_t i = 0; i < length; i++)
  {
    unsigned _rand = (unsigned)rand() % length;
    Phone temp = phone_number[_rand];
    phone_number[_rand] = phone_number[i];
    phone_number[i] = temp;
  }
}

void AppendPhoneNumber(Phone phone)
{
  if (phone_number_index < kAreaCodeLength * kLength)
    phone_number[phone_number_index++] = phone;
}

void InitializePhone(Phone *arr, size_t length, char area_code_index)
{
  for (size_t i = 0; i < length; i++)
    arr[i].area_code = area_code_index;
}

void LoopAreaCode()
{

  for (size_t i = 0; i < kAreaCodeLength; i++)
  {
    const unsigned kStart = time(NULL);
    fprintf(stdout, "生成区号为 %hu 的号码\n", kAreaCode[i]);
    DividArray(i);
    fprintf(stdout, "耗时：%us           \n", (unsigned)time(NULL) - kStart);
  }
}

void DividArray(char area_code_index)
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
    Phone arr[length];

    InitializePhone(arr, length, area_code_index);
    MakeRandArray(arr, length, min, max);

    fprintf(stdout, "Processing %zu/%zu\r", i, kDivideConut);
  }
}

bool IsUnique(const Phone *const arr, size_t length, unsigned target)
{
  bool result = true;
  for (size_t i = 0; i < length; i++)
  {
    if (arr[i].number == target)
    {
      result = false;
      break;
    }
  }
  return result;
}

void MakeRandArray(Phone *arr, size_t length, unsigned min, unsigned max)
{
  srand((unsigned)time(NULL));
  for (size_t i = 0; i < length; i++)
  {
    unsigned _rand = (unsigned)rand() % max;
    while (_rand < min || !IsUnique(arr, i, _rand))
      _rand = (unsigned)rand() % max;

    arr[i].number = _rand;
    AppendPhoneNumber(arr[i]);
  }
}