/*
 * cpp_main.cpp
 *
 *  Created on: Sep 3, 2024
 *      Author: LogMa
 */
#include <cstdint>
#include <stdio.h>
#include "main.h"
#include "Queue.h"



Queue::Queue(void)
{
		tail = 0;
		for(int32_t i = 0; i < Q_SIZE; i++)
		{
			buffer[i] = 0;
		}
	}

bool Queue::enqueue(int32_t msg)//adds msg to the queue at the indicated index by tail. Returns true if successful and false if buffer is full.
{
	if (tail >= Q_SIZE)
	{
		return false;
	}

	else
	{
		buffer[tail] = msg;
		tail++;
		return true;
	}
}

bool Queue::dequeue(int32_t *msg) //removes message at index 0 and shifts everything left (forward) and writes the removed message to *msg. Returns true if successful and false if if the queue is empty.
{
	tail--;

	if(tail < 0)
	{
		tail++;
		return false;
	}

	else
	{
		*msg = buffer[0];

		for(int32_t i = 1; i < Q_SIZE; i++){buffer[i - 1] = buffer[i];}

		buffer[Q_SIZE - 1] = 0;

		return true;
	}
}


bool queueTestCase()
{
	Queue line;
	bool decision[100];
	uint32_t outsideBoundary;

	for(uint32_t i = 0; i < 13; i++)
	{
		decision[i] = line.enqueue(i);
		if(decision[i] == false && decision[i-1] == true)
		{
			outsideBoundary = i;
		}
	}

	if(outsideBoundary == 0)
	{
		return true;
	}

	else
		return false;

}
