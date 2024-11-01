/*
 * Semaphor.cpp
 *
 *  Created on: Oct 29, 2024
 *      Author: credgar21
 */

#include "Semaphor.h"

Semaphor::Semaphor(){
}

bool Semaphor::enqueue(uint32_t msg){ 
    bool ok = false;
    if ((tail == SEMA_END && head == 0) || (tail + 1) == head){
        ok = false;
    }
    else{
        buffer[tail] = msg;

        if(tail == SEMA_END){
            tail = 0;
        }
        else
            tail++;

        ok = true;
    }
    return ok;
}

bool Semaphor::dequeue(uint32_t *msg){ 
    bool ok = false;
    if (head == tail) {
        ok = false;
    }
    else{
        *msg = buffer[head];

        buffer[head] = 0;

        if(head == (SEMA_END))
            head = 0;
        else
            head++;
        ok=true;
    }
    return ok;
}


