#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void PrintQueue(queue_t *queue)
{
    size_t size = QueueSize(queue);
    size_t i = 0;

    printf("Queue: ");

    for (i = 0; i < size; ++i)
    {
        void *data = QueuePeek(queue);
        printf("%d ", *(int *)data);
        QueueDequeue(queue);
        QueueEnqueue(queue, data);
    }

    printf("\n");
}

int main(void)
{
    int a = 10, b = 20, c = 30;
    queue_t *queue = QueueCreate();
    if (!queue)
    {
        printf("Failed to create queue.\n");
        return 1;
    }

    printf("Enqueuing 3 elements: 10, 20, 30\n");
    QueueEnqueue(queue, &a);
    QueueEnqueue(queue, &b);
    QueueEnqueue(queue, &c);

    PrintQueue(queue);

    printf("Peek: %d\n", *(int *)QueuePeek(queue));

    printf("Dequeue one element\n");
    QueueDequeue(queue);

    PrintQueue(queue);

    printf("Queue size: %lu\n", QueueSize(queue));
    printf("Is queue empty? %s\n", QueueIsEmpty(queue) ? "Yes" : "No");

    QueueDestroy(queue);
    printf("Queue destroyed successfully.\n");

    return 0;
}

