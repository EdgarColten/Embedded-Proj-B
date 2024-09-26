/*
 * Queue.h
 *
 *  Created on: Sep 12, 2024
 *      Author: LogMa
 */
#include <cstdint>

#ifndef INC_QUEUE_H_
#define INC_QUEUE_H_

#define Q_SIZE 10


class Queue{ //Logan Martin wrote this
private:
	int32_t tail;
	int32_t buffer[Q_SIZE];

public:
	Queue();
	bool enqueue(int32_t);
	bool dequeue(int32_t*);
};

bool queueTestCase();

#endif /* INC_QUEUE_H_ */
