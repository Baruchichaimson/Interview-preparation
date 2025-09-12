#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_MESSAGES 10

static int message = 0;
static int lock = 0; 

/* ---------------- Test-and-Set ---------------- */
int test_and_set(int *lock_ptr)
{
    int old = *lock_ptr;
    *lock_ptr = 1;
    return old;
}

void spin_lock(int *lock_ptr)
{
    while (test_and_set(lock_ptr))
    {
        /* busy wait */
    }
}

void spin_unlock(int *lock_ptr)
{
    *lock_ptr = 0;
}

/* ---------------- Producer ---------------- */
void *producer()
{
    int i;
    for (i = 0; i < NUM_MESSAGES; ++i)
    {
        spin_lock(&lock);

        message = rand() % 100;
        printf("Producer produced: %d\n", message);

        spin_unlock(&lock);
    }
    return NULL;
}

/* ---------------- Consumer ---------------- */
void *consumer()
{
    int i;
    for (i = 0; i < NUM_MESSAGES; ++i)
    {
        spin_lock(&lock);

        printf("Consumer consumed: %d\n", message);

        spin_unlock(&lock);
    }
    return NULL;
}

/* ---------------- Main ---------------- */
int main(void)
{
    pthread_t prod, cons;

    srand((unsigned)time(NULL));

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    return 0;
}
