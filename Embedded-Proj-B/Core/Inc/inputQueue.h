/*
 * inputQueue.h
 *
 *  Created on: Nov 1, 2024
 *      Author: LogMa
 */

#include "cpp_main.h"
#include <cstdint>


#ifndef INC_INPUTQUEUE_H_
#define INC_INPUTQUEUE_H_


#define Q_BUFFER_SIZE 16
#define Q_BUFFER_END 15


class inputQueue{
	nextState buffer[Q_BUFFER_SIZE];
    uint8_t head = 0;
    uint8_t tail = 0;

public:
    inputQueue();
    bool enqueue(nextState msg);
    bool dequeue(nextState* msg);
};





#endif /* INC_INPUTQUEUE_H_ */
