#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t i = 0; ///< Counter variable, updated by signal handler.
volatile sig_atomic_t sign = 1; ///< Direction of counting: 1 for increasing, -1 for decreasing.

/**
 * @brief Signal handler for SIGUSR1 and SIGUSR2 signals.
 *
 * This function handles two types of signals:
 * - SIGUSR1: Resets the counter variable `i` to 0.
 * - SIGUSR2: Toggles the direction of counting by changing the `sign` variable.
 *
 * @param sig The signal number received.
 */
void handler(int sig) {
  if (sig == SIGUSR1) {
    i = 0; ///< Reset counter to 0 on SIGUSR1.
  }
  if (sig == SIGUSR2) {
    sign = -sign; ///< Toggle counting direction on SIGUSR2.
  }
}

int main() {
  // Register the signal handler for SIGUSR1 and SIGUSR2.
  signal(SIGUSR1, handler);
  signal(SIGUSR2, handler);

  while (1) {
    // Print the current count and process ID.
    printf("current count is '%d' : %d\n", i, getpid());

    // Update the counter based on the current sign.
    i += sign;

    // Sleep for 1 second before the next update.
    sleep(1);
  }

  return 0;
}

