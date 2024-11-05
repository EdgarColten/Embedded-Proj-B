//Colten Queue

#include "waveQueue.h"
#include <cassert>

waveQueue::waveQueue()
{

}

bool waveQueue::enqueue(waveProp msg){
	//if queue is full
	if((tail + 1 == head) || (tail == QSIZE && head == 0)){
		return false;
	}
	//for empty queue
	if(head == -1){
		head = 0;
		assert(head == 0);
	}

	//Next Position
	if(tail + 1 == QSIZE){
		tail = 0;
	}
	else{
		tail++;
	}

	buffer[tail] = msg;

	return true;
}

bool waveQueue::dequeue(waveProp* msg){
	//if the queue is empty and can't dequeue
	if(head == -1){
		return false;
	}

	*msg = buffer[head];
	//waveProp qSelect = buffer[head];

	//if queue is now empty
	if(head == tail){
		head = -1;
		tail = -1;
	}
	else{
		if(head == (QSIZE - 1)){
			head = 0;
			assert(head == 0);
		}
		else{
			head++;
		}
	}
	//Might want to return the struct?
	return true;
}

