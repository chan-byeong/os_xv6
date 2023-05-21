#include "types.h"
#include "user.h"
#include "rand.h"
#define NUM_TICKETS 10

void test_process() {
  int i, j;
  for (i = 0; i < 5; i++) {
    printf(1, "Test Process: Executing iteration %d\n", i);
    for (j = 0; j < 10000000; j++) {
      // Busy wait to simulate workload
    }
  }
  exit();
}

int main(void) {
  int i;

  // Create multiple test processes with different ticket numbers
  for (i = 0; i < 5; i++) {
    int pid = fork();
    if (pid == 0) {
      // Child process
      int tickets = get_rand() % NUM_TICKETS + 1; // Assign random ticket number
      ticketset(tickets); // Set the number of tickets for the process
      test_process();
    }
  }

  // Wait for all child processes to finish
  for (i = 0; i < 5; i++) {
    wait();
  }

  exit();
}