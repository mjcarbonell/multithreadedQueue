#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <pthread.h> 
#include <stdbool.h>
struct ThreadStruct{
	pthread_mutex_t mutexLock; 
	pthread_cond_t untilNotFull; 
	pthread_cond_t untilNotEmpty; 
	int threadAmount; 
};
// NODE 
struct ThreadStruct threadStruct;
Node *node_create(void *num){ 
    Node *n = (Node *) malloc(sizeof(Node));
    assert(n);
    n->num = num;
    return n;
}
void node_delete(Node **n) {
    free(*n);
    *n = NULL;
    return;
}
void* getNum(Node *n){
	return n->num;
}

void nodeChange(Node *n, void *x){
	n->num = x;
}

typedef struct queue {
    int size; 
    int length;
    int index;
    Node *cursor;
    Node *front;
    Node *back;
} queue;

queue_t *queue_new(int size) { 
	//struct ThreadStruct threadStruct;
	threadStruct.threadAmount = 5; 
	threadStruct.untilNotFull = (pthread_cond_t)PTHREAD_COND_INITIALIZER; 
	threadStruct.untilNotEmpty = (pthread_cond_t) PTHREAD_COND_INITIALIZER; 
	
	pthread_mutex_init(&threadStruct.mutexLock, NULL); 
	
	queue_t *l = (queue_t *) malloc(sizeof(queue));
	//printf("SIZE: %ld\n", sizeof(queue));
	Node *front = node_create(0);
	Node *back = node_create(0);
	if (l) {
		l->size = size; 
		l->length = 0;
		l->index = 0;
		l->front = front; 
		l->front->next = l->back;
		l->back = back;
		l->back->prev = l->front;
		return l;
	}
	return NULL;
}

void queue_delete(queue_t **q) { 
	clear(*q);
	free(*q);
	return;
}

int length(queue_t *q) {
    return (q->length);
}

void *get(queue_t *q){ 
	if (q->cursor != NULL){
		return getNum(q->cursor);	
	}
	return (void *)-1;
}

void clear(queue_t *q){
	if (q->length > 0){
		for (int i=0; i < q->length; i++){
			queue_popper(q);
		}
		q->length = 0;
		q->index = 0;
	}
	return;
} 


void moveFront(queue_t *q){
	if (q->length > 0){ // IF LENGTH IS GREATER THAN ZERO 
		q->cursor = q->front->next;	
		q->index = 0;
	}
	return;
}
void moveBack(queue_t *q){
	if (q->length > 0){ // IF LENGTH IS GREATER THAN ZERO 
		q->cursor = q->back->prev;	
		q->index = (q->length - 1);
	}
	return;
}
void movePrev(queue_t *q){
	if (q->cursor != NULL){ // ENSURED CURSOR IS DEFINED 
		if (q->index > 0){ // CURSOR IS NOT AT FRONT 
			q->cursor = q->cursor->prev;
			q->index -= 1;
		}
		else{ // IF CURSOR AT FRONT 
			q->cursor = NULL;
		}
	}
	
}
void moveNext(queue_t *q){
	if (q->cursor != NULL){ // ENSURE CURSOR IS DEFINED 
		if (q->index < (q->length - 1)){ // CURSOR IS AT THE BACK 
			q->cursor = q->cursor->next;
			q->index += 1;
		}
		else{ // IF CURSOR AT BACK 
			q->cursor = NULL;
		}
	}
	
}

bool queue_push(queue_t *q, void *x){
	if(q == NULL){
		return false; 
	}
	pthread_mutex_lock(&threadStruct.mutexLock); 
	while(q->size == q->length){
		pthread_cond_wait(&threadStruct.untilNotFull, &threadStruct.mutexLock);
	}
	if (q->length == 0){
		Node *n = node_create(x);
	        q->front->next = n;
	        n->prev = q->front;
	        n->next = q->back;
	        q->back->prev = n;
	        q->index = 0;
	        q->length += 1;
	        q->cursor = n; 
	        //printf("num: %d\n", (int)ll->front->next->num);
	        pthread_cond_signal(&threadStruct.untilNotEmpty);
	        pthread_mutex_unlock(&threadStruct.mutexLock); 
	        return true;
	}
	Node *n = node_create(x);
	n->prev = q->back->prev;
	q->back->prev->next = n;
	q->back->prev = n;
	n->next = q->back;
	q->length += 1;
	q->cursor = n;
	pthread_cond_signal(&threadStruct.untilNotEmpty);
	pthread_mutex_unlock(&threadStruct.mutexLock); 
	return true;
	
}

bool queue_pop(queue_t *q, void **x){
	pthread_mutex_lock(&threadStruct.mutexLock); 
	while(q->length == 0){
		pthread_cond_wait(&threadStruct.untilNotEmpty, &threadStruct.mutexLock);
	}
	if(q == NULL){
		return false; 
	}
	if(&(*x) == NULL){
		return false; 
	}
	if (q->length > 0){
		
		//int new = (*(int *) ll->front->next);
		int new = (*(int *) q->front->next);
		//memcpy(x, new, sizeof(int)); 
		//printf("new is: %d\n", new);
		
		*(int *)x = (new) ;
		
		// ACTUAL DELETION 
		Node *temp = node_create((void *)99);
		temp->next = q->front->next; // TEMP NODE USED tO DELETE OTHERS AROUND IT
		q->front->next->next->prev = q->front;
		q->front->next = q->front->next->next;
		node_delete(&temp->next);
		node_delete(&temp);
		q->length -= 1;
		q->index -= 1;	
		pthread_cond_signal(&threadStruct.untilNotFull);
		pthread_mutex_unlock(&threadStruct.mutexLock); 
		return true; 
	}
	pthread_cond_signal(&threadStruct.untilNotFull);
	pthread_mutex_unlock(&threadStruct.mutexLock); 
	//printf("queue is empty\n"); 
	return false;
}


void queue_popper(queue_t *q){
	if (q->length > 0){
		Node *temp = node_create((void *)99);
		temp->next = q->front->next; // TEMP NODE USED tO DELETE OTHERS AROUND IT
		q->front->next->next->prev = q->front;
		q->front->next = q->front->next->next;
		node_delete(&temp->next);
		node_delete(&temp);
		q->length -= 1;
		q->index -= 1;
	}
	return;
}














