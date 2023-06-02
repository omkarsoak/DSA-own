// min_priority_queue.c
#include <stdio.h>
#include "PQ.h"
#include <stdlib.h>

PriorityQueue* createMinPriorityQueue() {
    PriorityQueue* queue = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    queue->size = 0;
    return queue;
}

void destroyMinPriorityQueue(PriorityQueue* queue) {
    free(queue);
}

void insert(PriorityQueue* queue, Edge item) {
    if (queue->size >= MAX_SIZE) {
        // Queue is full, handle the error
        return;
    }

    int i = queue->size;
    while (i > 0 && item.weight < queue->items[(i - 1) / 2].weight) {
        queue->items[i] = queue->items[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    queue->items[i] = item;
    queue->size++;
}

int is_Empty(PriorityQueue* queue) {
    return queue->size == 0;
}

Edge deleteMin(PriorityQueue* queue) {
    if (is_Empty(queue)) {
        // Queue is empty, handle the error
        Edge emptyItem = {0, 0, 0};
        return emptyItem;
    }

    Edge minItem = queue->items[0];
    queue->size--;

    Edge lastItem = queue->items[queue->size];
    int i = 0;
    int child = 1;

    while (child < queue->size) {
        if (child + 1 < queue->size && queue->items[child + 1].weight < queue->items[child].weight) {
            child++;
        }

        if (lastItem.weight <= queue->items[child].weight) {
            break;
        }

        queue->items[i] = queue->items[child];
        i = child;
        child = 2 * i + 1;
    }

    queue->items[i] = lastItem;
    return minItem;
}

Edge edge(int u,int v,int weight)
{
    Edge edge;
    edge.u = u;
    edge.v = v;
    edge.weight = weight;
    return edge;
}