/*
 * inputQueue.h
 *
 *  Created on: Nov 1, 2024
 *      Author: LogMa
 */
/**
*@file	inputQueue.h
*@brief FIFO queue.
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
    /**
        * @brief Write msg into the FIFO queue; and return true if successful.
        * This function uses a circular buffer to implement a FIFO queue.
	    * The algorithm is head-and-load instead of head-and-tail, However I called "load" tail.
	    * The queue size is fixed by #define Q_BUFFER_SIZE in this header file.       
        *
        *
        * @param x msg A nextState (nextState is defined in cpp_main.h) struct written to the FIFO buffer. 
        * @return false if the buffer is full, true if the write is OK.
        */
    bool enqueue(nextState msg);
    /**
        * @brief Read nextState struct from the FIFO buffer; and return true if successful.
        * This function uses a circular buffer to implement a FIFO queue.
	    * The algorithm is head-and-load instead of head-and-tail, However I called "load" tail.
	    * The queue size is fixed by #define Q_BUFFER_SIZE in this header file.       
        *
        *
        * @param x msg A nextState (nextState is defined in cpp_main.h) struct pointer read from the FIFO buffer.
        * @return false if the buffer is empty, true if the write is OK.
        */
    bool dequeue(nextState* msg);
};





#endif /* INC_INPUTQUEUE_H_ */
