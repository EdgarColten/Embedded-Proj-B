/*
 * cpp_main.cpp
 *
 *  Created on: Sep 3, 2024
 *      Author: LogMa
 */
#include <cstdint>
#include <stdio.h>
#include "main.h"
#include "Queue.h"



Queue::Queue(){
    // q_load = 0 via "attribute = 0" style
}

bool Queue::enqueue(int32_t msg){ //works with the tail
    bool ok = false;
    if ((tail == BUFFER_END && head == 0) || (tail + 1) == head){ //This means that the buffer will be "empty" and we will be unable to dequeue
        ok = false;
    }
    else{
        buffer[tail] = msg;

        if(tail == BUFFER_END){
            tail = 0;
        }
        else
            tail++;

        ok = true;
    }
    return ok;
}

bool Queue::dequeue(int32_t *msg){ //works with the head
    bool ok = false;
    if (head == tail) {
        ok = false;
    }
    else{
        *msg = buffer[head];
        /*for (uint16_t n = 0; n<q_load; n++){
            buffer[n] = buffer[n+1];
        }*/
        buffer[head] = 0;

        if(head == (BUFFER_END))
            head = 0;
        else
            head++;
        ok=true;
    }
    return ok;
}



