#include "types.h"
#include "stat.h"
#include "user.h"

#define NUM_TICKETS 10

void long_task() {
  int i, j;
  for (i = 0; i < 100000; i++) {
    for (j = 0; j < 10000; j++) {
      asm("nop");  // 빈 명령어 실행 (Busy Wait)
    }
  }
  printf(1, "Long task completed.\n");
  exit();
}

void short_task() {
  for(int i =0; i < 10000; i++){
    asm("nop");
  }
  printf(1, "Short task completed.\n");
  exit();
}

int main() {
  int pid;

  printf(1, "Lottery Scheduling Test\n");

  // Long task with 80% of tickets
  pid = fork();
  if (pid == 0) {
    ticketset(NUM_TICKETS * 0.8);
    long_task();
  }

  // Short task with 20% of tickets
  pid = fork();
  if (pid == 0) {
    ticketset(NUM_TICKETS * 0.2);
    short_task();
  }

  // Wait for child processes to complete
  wait();
  wait();

  printf(1, "All tasks completed.\n");

  exit();
}
