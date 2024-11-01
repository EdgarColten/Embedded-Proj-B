/*
 * Semaphor.h
 *
 *  Created on: Oct 29, 2024
 *      Author: credgar21
 */

#include <cstdint>

#ifndef INC_SEMAPHOR_H_
#define INC_SEMAPHOR_H_


#define QUEUE_BUFF_SIZE 1
#define BUFF_END 0


class Semaphor{
    uint32_t buffer[QUEUE_BUFF_SIZE];
    uint8_t head = 0;
    uint8_t tail = 0;

public:
    Semaphor();
    bool enqueue(uint32_t msg);
    bool dequeue(uint32_t* msg);
};




#endif /* INC_SEMAPHOR_H_ */
