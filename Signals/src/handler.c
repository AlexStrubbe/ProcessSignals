#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * @brief Main function to manage infinite counter processes.
 *
 * This program allows the user to manage a specified number of infinite counter
 * processes by interacting with them through signals. Users can start, stop,
 * continue, change the counting direction, reset, or kill these processes.
 * The program dynamically allocates memory to store the PIDs of the processes
 * and allows interaction based on user input.
 *
 * @return int Exit status of the program. Returns 0 on successful completion.
 */
int main() {
  int i = 0;             ///< Loop counter variable.
  int qty = 0;           ///< Number of infinite counter processes to manage.
  int *pids;             ///< Pointer to an array of process IDs (PIDs).
  int gate = 1;          ///< Gate variable to control the loop for valid input.
  int selection = 0;     ///< User's selection for the action to perform.
  int spec_counter = 0;  ///< Index of the process to interact with.

  // Loop until a valid number of processes is entered (1-5).
  while (gate) {
    printf(
        "Hello and welcome to the infinite counter handler, please indicate "
        "the amount (up to 5) of infinite counters you would like to have "
        "running: \n");
    scanf("%d", &qty);
    if (qty > 5 || qty < 0) {
      printf("You have input a wrong option please try again.");
      qty = 0;
    } else {
      gate = 0;
    }
  }

  // Allocate memory for pids array to store process IDs.
  pids = (int *)malloc(qty * sizeof(int));
  if (pids == NULL) {
    perror("Failed to allocate memory");
    return 1;
  }

  // Read the PIDs of the infinite counter programs from the user.
  printf(
      "Please insert the PID of the programs you wish to handle separated by "
      "spaces: \n");
  for (int i = 0; i < qty; i++) {
    scanf("%d", &pids[i]);
  }

  // Main interaction loop for managing the processes.
  while (qty > 0) {
    printf(
        "Select the instance of the infinite counter you wish to interact "
        "with: \n");
    for (i = 0; i < qty; i++) {
      printf("%d) %d\n", i + 1, pids[i]);
    }
    scanf("%d", &spec_counter);

    // Display options for actions to perform on the selected process.
    printf(
        "Now select the function you wish to execute:\n"
        "1) Stop\n"
        "2) Continue\n"
        "3) Change the counting direction\n"
        "4) Reset counter\n"
        "5) Kill\n");

    scanf("%d", &selection);
    __pid_t p = pids[spec_counter - 1];  ///< PID of the selected process.

    switch (selection) {
      case 1:
        // Fork a new process to send SIGSTOP to the selected process.
        if (fork() == 0) {
          kill(p, SIGSTOP);
          exit(1);
        }
        break;
      case 2:
        // Fork a new process to send SIGCONT to the selected process.
        if (fork() == 0) {
          kill(p, SIGCONT);
          exit(1);
        }
        break;
      case 3:
        // Fork a new process to send SIGUSR2 to change counting direction.
        if (fork() == 0) {
          kill(p, SIGUSR2);
          exit(1);
        }
        break;
      case 4:
        // Fork a new process to send SIGUSR1 to reset the counter.
        if (fork() == 0) {
          kill(p, SIGUSR1);
          exit(1);
        }
        break;
      case 5:
        // Fork a new process to send SIGKILL to terminate the selected process.
        if (fork() == 0) {
          kill(p, SIGKILL);
          exit(1);
        }
        // Remove the terminated process from the list and resize the array.
        for (int i = spec_counter - 1; i < qty - 1; i++) {
          pids[i] = pids[i + 1];
        }
        qty--;
        pids = (int *)realloc(pids, qty * sizeof(int));
        if (pids == NULL && qty > 0) {
          perror("Failed to reallocate memory");
          return 1;
        }
        break;
      default:
        // Handle invalid selections.
        break;
    }
  }

  // Notify user that there are no more processes to manage.
  printf(
      "No more Infinite counter programs found, exiting the program, Good "
      "bye.");
  return 0;
}
