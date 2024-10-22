/*
 * Queue.h
 *
 *  Created on: Sep 12, 2024
 *      Author: LogMa
 */
#include <cstdint>

#ifndef INC_QUEUE_H_
#define INC_QUEUE_H_

#define QUEUE_BUFF_SIZE 256
#define BUFF_END 255


class Queue{
    uint32_t buffer[QUEUE_BUFF_SIZE];
    uint8_t head = 0;
    uint8_t tail = 0;

public:
    Queue();
    bool enqueue(uint32_t msg);
    bool dequeue(uint32_t* msg);
};

#endif /* INC_QUEUE_H_ */
