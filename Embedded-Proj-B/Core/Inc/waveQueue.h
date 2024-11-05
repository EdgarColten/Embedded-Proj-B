/*
 * waveQueue.h
 *
 *  Created on: Oct 22, 2024
 *      Author: LogMa
 */

/**
*@file waveQueue.h
*@brief FIFO queue.
*/
#include "cpp_main.h"
#include <cstdint>

#ifndef INC_WAVEQUEUE_H_
#define INC_WAVEQUEUE_H_

#define QSIZE 6

class waveQueue{
private:
    int8_t tail = -1;
    int8_t head = -1;
    waveProp buffer[QSIZE];

public:
    waveQueue();
    /**
        * @brief Write msg into the FIFO queue; and return true if successful.
        * This function uses a circular buffer to implement a FIFO queue.
	    * The algorithm is head-and-load instead of head-and-tail, However I called "load" tail.
	    * The queue size is fixed by #define QSIZE in this header file.       
        *
        *
        * @param x msg A waveProp (waveProp is defined in cpp_main.h) struct written to the FIFO buffer. 
        * @return false if the buffer is full, true if the write is OK.
        */
    bool enqueue(waveProp);
    /**
        * @brief Read waveProp struct from the FIFO queue; and return true if successful.
        * This function uses a circular buffer to implement a FIFO queue.
	    * The algorithm is head-and-load instead of head-and-tail, However I called "load" tail.
	    * The queue size is fixed by #define QSIZE in this header file.       
        *
        *
        * @param x msg A waveProp (waveProp is defined in cpp_main.h) struct pointer read from the FIFO buffer.
        * @return false if the buffer is empty, true if the write is OK.
        */
    bool dequeue(waveProp*);
};



#endif /* INC_WAVEQUEUE_H_ */
