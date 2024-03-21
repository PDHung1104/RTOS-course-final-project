#pragma once
#define Q_SIZE 32

typedef struct {
	unsigned char Data[Q_SIZE];
	unsigned int Head; // points to oldest data element
	unsigned int Tail; // points to next free space
	unsigned int Size; // quantity of elements in queue
} Q_T;

int Q_Empty(Q_T*);

int Q_Full(Q_T*);

void Q_init(Q_T*);

int enqueue(Q_T*, unsigned char);

unsigned char dequeue(Q_T*);
