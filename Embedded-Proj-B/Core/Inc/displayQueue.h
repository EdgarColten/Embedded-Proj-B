/*
 * displayQueue.h
 *
 *  Created on: Oct 12, 2024
 *      Author: LogMa
 */

/**
*@file	displayQueue.h
*@brief FIFO queue.
*/
#include <cstdint>
#include "cpp_main.h"

#ifndef INC_DISPLAYQUEUE_H_
#define INC_DISPLAYQUEUE_H_

#define QUEUE_BUFFER_SIZE 16
#define BUFFER_END 15


class displayQueue{
	displayValues buffer[QUEUE_BUFFER_SIZE];
    uint8_t head = 0;
    uint8_t tail = 0;

public:
    displayQueue();
    /**
        * @brief Write msg into the FIFO queue; and return true if successful.
        * This function uses a circular buffer to implement a FIFO queue.
	    * The algorithm is head-and-load instead of head-and-tail, However I called "load" tail.
	    * The queue size is fixed by #define QUEUE_BUFFER_SIZE in this header file.       
        *
        *
        * @param x msg A displayValues (displayValues is defined in cpp_main.h) struct written to the FIFO buffer.
        * @return false if the buffer is full, true if the write is OK.
        */
    bool enqueue(displayValues msg);

   /**
        * @brief Read displayValues struct from the FIFO buffer; and return true if successful.
        * This function uses a circular buffer to implement a FIFO queue.
	    * The algorithm is head-and-load instead of head-and-tail, However I called "load" tail.
	    * The queue size is fixed by #define QUEUE_BUFFER_SIZE in this header file.       
        *
        *
        * @param x msg A displayValues (displayValues is defined in cpp_main.h) struct pointer read from the FIFO buffer.
        * @return false if the buffer is empty, true if the read is OK.
        */
    bool dequeue(displayValues* msg);
};



#endif /* INC_DISPLAYQUEUE_H_ */
