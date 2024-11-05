/*
 * Queue.h
 *
 *  Created on: Sep 12, 2024
 *      Author: LogMa
 */

/**
*@file Queue.h
*@brief FIFO queue.
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
    /**
        * @brief Write msg into the FIFO queue; and return true if successful.
        * This function uses a circular buffer to implement a FIFO queue.
	    * The algorithm is head-and-load instead of head-and-tail, However I called "load" tail.
	    * The queue size is fixed by #define QUEUE_BUFF_SIZE in this header file.       
        *
        *
        * @param x msg An unsigned integer written to the FIFO buffer. 
        * @return false if the buffer is full, true if the write is OK.
        */
    bool enqueue(uint32_t msg);
    /**
        * @brief Read unsigned integer from the FIFO queue; and return true if successful.
        * This function uses a circular buffer to implement a FIFO queue.
	    * The algorithm is head-and-load instead of head-and-tail, However I called "load" tail.
	    * The queue size is fixed by #define QUEUE_BUFF_SIZE in this header file.       
        *
        *
        * @param x msg An unsigned integer read from the FIFO buffer.
        * @return false if the buffer is empty, true if the read is OK.
        */
    bool dequeue(uint32_t* msg);
};

#endif /* INC_QUEUE_H_ */
