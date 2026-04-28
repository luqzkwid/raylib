#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define WIDTH 400
int main(void){
  srand(time(NULL));
  float r_value =  rand() % WIDTH + 1;
  float width   =  rand() % WIDTH + 50;
  printf("\n%f\n", r_value);
  return 0;
}
