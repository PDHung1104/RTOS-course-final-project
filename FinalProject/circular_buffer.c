#include "circular_buffer.h"

int Q_Empty(Q_T * q) {
	return q->Size == 0;
}

int Q_Full(Q_T * q) {
	return q->Size == Q_SIZE;
}

void Q_init(Q_T* queue){
	for (int i = 0; i < Q_SIZE; i++){
		queue->Data[i] = 0;
	}
	queue->Head = 0;
	queue->Tail = 0;
	queue->Size = 0;
}

int enqueue(Q_T* queue, unsigned char data) {
	if (Q_Full(queue)){
		return 1;
	}
	queue->Data[queue->Tail++] = data;
	queue->Tail %= Q_SIZE;
	queue->Size++;
	return 0;
}

unsigned char dequeue(Q_T* queue) {
	if (Q_Empty(queue)) {
		return 0;
	}
	unsigned char t = queue->Data[queue->Head];
	queue->Data[queue->Head++] = 0;
	queue->Head %= Q_SIZE;
	queue->Size--;
	return t;
}