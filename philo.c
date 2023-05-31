#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "semaphore.c.c"

#define NUM_PHILOSOPHERS 4

typedef struct {
    int id;
    int left_fork;
    int right_fork;
} Philosopher;

typedef struct
{
    int semId;
} Semaphore;


Philosopher philosophers[NUM_PHILOSOPHERS];
Semaphore forks[NUM_PHILOSOPHERS];

void think(int philosopher_id) {
    printf("Philosopher %d is thinking.\n", philosopher_id);
    sleep(rand() % 2);
}

void eat(int philosopher_id) {
    printf("Philosopher %d is eating.\n", philosopher_id);
    sleep(rand() % 2);
}

void take_forks(int philosopher_id) {
    V(forks[philosopher_id].semId);
    V(forks[(philosopher_id + 1) % NUM_PHILOSOPHERS].semId);
        printf("Philosopher %d takes the fork.\n", philosopher_id);

}

void put_forks(int philosopher_id) {
    P(forks[philosopher_id].semId);
    P(forks[(philosopher_id + 1) % NUM_PHILOSOPHERS].semId);
    printf("Philosopher %d puts the fork back.\n", philosopher_id);

}


void philosopher_process(int philosopher_id) {
    while (1) {
        think(philosopher_id);
        take_forks(philosopher_id);
        eat(philosopher_id);
        put_forks(philosopher_id);
    }
}

int main() {
    srand(time(NULL));

    // Initialize the forks (semaphores)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        initSem(1, "semaphore.c.c", NULL);
    }


    // Create philosopher processes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosophers[i].id = i;
        philosophers[i].left_fork = i;
        philosophers[i].right_fork = (i + 1) % NUM_PHILOSOPHERS;

        if (fork() == 0) {
            // Child process (philosopher)
            philosopher_process(i);
        }
    }


    // Wait for all philosopher processes to finish
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        wait(NULL);
    }

    // Clean up semaphores
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        libereSem();
    }

    return 0;
}
