#include "types.h"
#include "user.h"

//인자 전달 오류
//Thread JOIN X -> zombie

// Thread start function
void thread_start(void* arg1, void* arg2)
{
  int* a = (int*)arg1;
  *a = 100;
  int b = *(int*)arg2;
  printf(1,"b == %d\n",b);

  for (int i = 0; i < 5; i++)
  {
    printf(1, "Thread: %d\n", i);
    sleep(100);
  }
}

int main()
{
  int a = 0;
  int b = 44;
  // Create a new thread
  int tid = thread_create(thread_start,(void *)&a,&b);

  if (tid < 0)
  {
    printf(1, "Thread creation failed!\n");
    exit();
  }

  tid = thread_join();
  if(tid == -1) { 
    printf(1, "Thread join failed!\n");
    exit();
  }

  sleep(100);

  int i;
  for (i = 0; i < 5; i++)
  {
    printf(1, "Main Thread: %d\n", i);
    sleep(100);
  }

  printf(1,"a : %d\n",a);

  exit();
}