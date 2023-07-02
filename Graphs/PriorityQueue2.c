// min_priority_queue.c
#include <stdio.h>
#include <stdlib.h>
#include "PriorityQueue2.h"

PriorityQueue2* createMinPriorityQueue2() {
    PriorityQueue2* queue = (PriorityQueue2*)malloc(sizeof(PriorityQueue2));
    queue->size = 0;
    return queue;
}

void destroyMinPriorityQueue2(PriorityQueue2* queue) {
    free(queue);
}

void insert2(PriorityQueue2* queue, Pair item) {
    if (queue->size >= MAX_SIZE) {
        // Queue is full, handle the error
        return;
    }

    int i = queue->size;
    while (i > 0 && item.distance < queue->items[(i - 1) / 2].distance) {
        queue->items[i] = queue->items[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    queue->items[i] = item;
    queue->size++;
}

int is_Empty2(PriorityQueue2* queue) {
    return queue->size == 0;
}

Pair deleteMin2(PriorityQueue2* queue) {
    if (is_Empty2(queue)) {
        // Queue is empty, handle the error
        Pair emptyItem = {0, 0};
        return emptyItem;
    }

    Pair minItem = queue->items[0];
    queue->size--;

    Pair lastItem = queue->items[queue->size];
    int i = 0;
    int child = 1;

    while (child < queue->size) {
        if (child + 1 < queue->size && queue->items[child + 1].distance < queue->items[child].distance) {
            child++;
        }

        if (lastItem.distance <= queue->items[child].distance) {
            break;
        }

        queue->items[i] = queue->items[child];
        i = child;
        child = 2 * i + 1;
    }

    queue->items[i] = lastItem;
    return minItem;
}

Pair pair(int u,int distance)
{
    Pair edge;
    edge.u = u;
    edge.distance = distance;
    return edge;
}