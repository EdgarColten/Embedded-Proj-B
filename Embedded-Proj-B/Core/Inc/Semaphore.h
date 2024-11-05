/*
 * Semaphor.h
 *
 *  Created on: Oct 29, 2024
 *      Author: credgar21
 */

/**
*@file Semaphore.h
*@brief Semaphore (FIFO queue).
*/
#include <cstdint>

#ifndef INC_SEMAPHOR_H_
#define INC_SEMAPHOR_H_


#define SEMA_SIZE 2
#define SEMA_END 1


class Semaphore{
    uint32_t buffer[SEMA_SIZE];
    uint8_t head = 0;
    uint8_t tail = 0;

public:
    Semaphore();
    /**
        * @brief Write a msg into the FIFO queue; and return true if successful.
        * This function uses a circular buffer to implement a FIFO queue.
	    * The algorithm is head-and-load instead of head-and-tail, However I called "load" tail.
	    * The queue size is fixed by #define SEMA_SIZE in this header file.       
        *
        *
        * @param x msg An unsigned integer written to the FIFO buffer.
        * @return false if the buffer is full, true if the write is OK.
        */
    bool enqueue(uint32_t msg);
    /**
        * @brief Read unsigned integer from FIFO buffer; and return true if successful.
        * This function uses a circular buffer to implement a FIFO queue.
	    * The algorithm is head-and-load instead of head-and-tail, However I called "load" tail.
	    * The queue size is fixed by #define SEMA_SIZE in this header file.       
        *
        *
        * @param x msg An unsigned integer pointer read from the FIFO buffer.
        * @return false if the buffer is empty, true if the read is OK.
        */
    bool dequeue(uint32_t* msg);
};




#endif /* INC_SEMAPHOR_H_ */
