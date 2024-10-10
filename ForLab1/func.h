#define _CRT_SECURE_NO_WARNINGS

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
  int bin_array[4] = { 0,0,0,0 };
  bin_array[0] = bin % 10000 / 1000;
  bin_array[1] = bin % 1000 / 100;
  bin_array[2] = bin % 100 / 10;
  bin_array[3] = bin % 10;
  bin_array[num] = 1;
  return bin_array[0] * 8 + bin_array[1] * 4 + bin_array[2] * 2 + bin_array[3];
}

int bin_encode(char dec)
{
  int bin = 0;
  bin = 1 * 10000 + dec / 2 / 2 / 2 % 2 * 1000 + dec / 2 / 2 % 2 * 100 + dec / 2 % 2 * 10 + dec % 2;
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
