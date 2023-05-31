#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "semaphore.c.c"

typedef struct
{
    int semId;
} Semaphore;

Semaphore semaphores[2]; // Array of semaphores

void childProcess()
{
    printf("arrivee RdV fils\n");
    V(semaphores[0].semId); // Signal that child has arrived
    P(semaphores[1].semId); // Wait for parent to arrive
    printf("le fils repart\n");
    exit(0);
}

void parentProcess()
{
    printf("arrivee RdV pere\n");
    V(semaphores[1].semId); // Signal that parent has arrived
    P(semaphores[0].semId); // Wait for child to arrive
    printf("le pere repart\n");
    exit(0);
}

int main()
{
    initSem(2, "semaphore.c", NULL); // Initialize semaphores

    semaphores[0].semId = 0; // Set the semaphore IDs
    semaphores[1].semId = 1;
    if (fork() == 0)
    {
        // Child process
        childProcess();
    }
    else
    {
        // Parent process
        parentProcess();
    }

    return 0;
}