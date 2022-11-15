#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef struct Node Node;

struct Node {
    void *num;
    char *word;
    Node *next;
    Node *prev;
};

Node *node_create(void *num);

void node_delete(Node **n);

void* getNum(Node *n);

void nodeChange(Node *n, void *x);


typedef struct queue queue_t;

queue_t *queue_new(int size);

void queue_delete(queue_t **q);

int length(queue_t *q);

void *get(queue_t *q);

void clear(queue_t *q);

void moveFront(queue_t *q);

void moveBack(queue_t *q); 

void movePrev(queue_t *q);

void moveNext(queue_t *q);

bool queue_push(queue_t *q, void *elem);

bool queue_pop(queue_t *q, void **elem);

void queue_popper(queue_t *q);
#endif












