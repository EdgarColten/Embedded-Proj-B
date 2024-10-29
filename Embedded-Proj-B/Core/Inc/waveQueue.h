/*
 * waveQueue.h
 *
 *  Created on: Oct 22, 2024
 *      Author: LogMa
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
    bool enqueue(waveProp);
    bool dequeue(waveProp*);
};



#endif /* INC_WAVEQUEUE_H_ */
