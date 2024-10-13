/*
 * displayQueue.h
 *
 *  Created on: Oct 12, 2024
 *      Author: LogMa
 */

#include <cstdint>
#include "cpp_main.h"

#ifndef INC_DISPLAYQUEUE_H_
#define INC_DISPLAYQUEUE_H_

#define QUEUE_BUFFER_SIZE 10
#define BUFFER_END 15


class displayQueue{
	displayValues buffer[QUEUE_BUFFER_SIZE];
    uint8_t head = 0;
    uint8_t tail = 0;

public:
    displayQueue();
    bool enqueue(displayValues msg);
    bool dequeue(displayValues* msg);
};



#endif /* INC_DISPLAYQUEUE_H_ */
