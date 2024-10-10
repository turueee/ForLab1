#define _CRT_SECURE_NO_WARNINGS
#define CLOCK_PER_SEC

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "func.h"



int main()
{
  double random_number, min_ch, max_ch, result =0, number = 0;
  int count_of_numbers, counter, dec_remain, index_for_encoder,index;
  char num_for_encoding;
  char mas[250000];
  double time_spent = 0.0;
  clock_t begin = 0, end = 0;
  FILE* file_of_numbers;


  printf("Enter the minimum number to generate: ");
  scanf("%lf", &min_ch);
  printf("Enter the maximum number to generate: ");
  scanf("%lf", &max_ch);
  printf("Enter the count of generated numbers: ");
  scanf("%d", &count_of_numbers);


  for (int i = 0; i < 250000; i++)
    mas[i] = (char)0;
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