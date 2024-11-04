/*
 * Semaphor.h
 *
 *  Created on: Oct 29, 2024
 *      Author: credgar21
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
    bool enqueue(uint32_t msg);
    bool dequeue(uint32_t* msg);
};




#endif /* INC_SEMAPHOR_H_ */
