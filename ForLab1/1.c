#define _CRT_SECURE_NO_WARNINGS
#define CLOCK_PER_SEC

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double make_random_number(double min_ch, double max_ch, int sid_variable)
{
  double zero_one = 0, random_number = 0, zero_max_ch = 0;
  int randomization = 0;
  srand(clock() + sid_variable * 1000);
  randomization = rand();
  zero_one = (double)randomization / RAND_MAX;
  zero_max_ch = zero_one * (max_ch - min_ch);
  random_number = zero_max_ch + min_ch;
  return random_number;
}



int make_dec_remain(double double_variable)
{
  double remain = 0;
  int int_remain = 1;
  if (double_variable >= 0)
  {
    remain = double_variable - floor(double_variable);
  }
  else
    remain = (-double_variable) + ceil(double_variable);
  remain *= 1000000;
  int_remain = (int)round(remain);
  return int_remain;
}

char encoder(char num, char code)
{
  int bin = bin_encode(code);
  int bin_array[4] = {0,0,0,0};
  bin_array[0] = bin % 10000 / 1000;
  bin_array[1] = bin % 1000 / 100;
  bin_array[2] = bin % 100 / 10;
  bin_array[3] = bin % 10;
  bin_array[num] = 1;
  return bin_array[0]*8+bin_array[1]*4+bin_array[2]*2+bin_array[3];
}

int bin_encode(char dec)
{
  int bin = 0;
  bin = 1*10000+dec / 2 / 2 / 2 % 2 * 1000 + dec / 2 / 2 % 2 * 100 + dec / 2 % 2 * 10 + dec % 2;
  return(bin);
}


int decoder(char encode, int index)
{
  int bin = bin_encode(encode);
  int bin_array[4] = { 0,0,0,0 };
  bin_array[0] = bin % 10000 / 1000;
  bin_array[1] = bin % 1000 / 100;
  bin_array[2] = bin % 100 / 10;
  bin_array[3] = bin % 10;
  return bin_array[index];
}


int main()
{
  double random_number, min_ch, max_ch, result =0, number = 0;
  int count_of_numbers, counter, dec_remain, index_for_encoder,index;
  char num_for_encoding;
  char mas[250000];
  double time_spent = 0.0;
  clock_t begin = 0, end = 0;
  FILE* file_of_numbers;
  for (int i = 0; i < 250000; i++)
    mas[i] = (char)0;
  printf("Enter the minimum number to generate: ");
  scanf("%lf", &min_ch);
  printf("Enter the maximum number to generate: ");
  scanf("%lf", &max_ch);
  printf("Enter the count of generated numbers: ");
  scanf("%d", &count_of_numbers);

  begin = clock();
  file_of_numbers = fopen("stor.txt", "w");
  for (counter = 0; counter < count_of_numbers; counter++)
  {
    random_number = make_random_number(min_ch, max_ch, counter);
    dec_remain = make_dec_remain(random_number);

    if (counter < 1000000)
    {
      if (file_of_numbers != NULL)
        fprintf(file_of_numbers, "%lf\n", random_number);
      else
        printf("ERROR!!!");
    }
    else
    {
      result += random_number;
    }
    num_for_encoding = (char)(dec_remain % 4);
    index_for_encoder = dec_remain / 4;
    mas[index_for_encoder] = (char)encoder(num_for_encoding, mas[index_for_encoder]);
  }
  fclose(file_of_numbers);
  file_of_numbers = fopen("stor.txt", "r");
  if (count_of_numbers > 1000000)
    count_of_numbers = 1000000;
  for (counter = 0; counter < count_of_numbers; counter++)
  {
    fscanf(file_of_numbers, "%lf\n", &number);
    index = decoder(mas[counter / 4], counter % 4);
    if (index == 1)
    {
      result -= number;
    }

    else
    {
      result += number;
    }
  }
  fclose(file_of_numbers);
  end = clock();
  time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Result: %lf.\nExcecution time: %lf seconds.", result, time_spent);
}