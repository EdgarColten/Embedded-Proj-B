/*
 * Queue.h
 *
 *  Created on: Sep 12, 2024
 *      Author: LogMa
 */
#include <cstdint>

#ifndef INC_QUEUE_H_
#define INC_QUEUE_H_

#define QUEUE_BUFFER_SIZE 10
#define BUFFER_END 15


class Queue{
    int32_t buffer[QUEUE_BUFFER_SIZE];
    uint8_t head = 0;
    uint8_t tail = 0;

public:
    Queue();
    bool enqueue(int32_t msg);
    bool dequeue(int32_t* msg);
};

#endif /* INC_QUEUE_H_ */
