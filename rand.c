#include "rand.h"

#define SIZE 5

int randNum[SIZE]={11,22,33,44,55};

int idx = 0;

int get_rand(){
  idx = idx % 5;
  return randNum[idx++];
}