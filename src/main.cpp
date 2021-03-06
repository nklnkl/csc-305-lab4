#include <unistd.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int main () {

  // Spawn child process.
  pid_t pid = fork();

  // Pipes.
  int parentPipeFd [2];
  int childPipeFd [2];
  pipe(parentPipeFd);
  pipe(childPipeFd);

  // If in child process.
  if (pid == 0) {
    cout << "Child process started" << endl;
    
    // Close read of child pipe.
    close(childPipeFd[0]);

    // Close write of parent pipe.
    close(parentPipeFd[1]);

    // Partial sum of child.
    int childSum = 0;
    for (int i = 1; i <= 5; i++) {
      childSum += i;
    }
    cout << "Child partial sum is " << childSum << endl;

    cout << "Child sent " << childSum << " to parent" << endl;

    write(childPipeFd[1], &childSum, sizeof(childSum));

    close(childPipeFd[1]);
  }

  // Else if in parent proccess.
  else {

    sleep(1);

    cout << "Parent process received " << childPipeFd[0] << " from child" << endl;
    int totalSum = childPipeFd[0];
    
    // Close read of parent pipe.
    close(parentPipeFd[0]);

    // Close write of child pipe.
    close(childPipeFd[1]);

    // Partial sum of parent.
    int parentSum = 0;
    for (int i = 6; i <= 10; i++) {
      parentSum += i;
    }
    totalSum += parentSum;

    cout << "Parent partial sum is " << parentSum << endl;

    cout << "Parent computed final sum " << totalSum << endl;
  }
  
  return 0;
}