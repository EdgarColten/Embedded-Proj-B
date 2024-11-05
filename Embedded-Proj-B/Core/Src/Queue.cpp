/*
 * cpp_main.cpp
 *
 *  Created on: Sep 3, 2024
 *      Author: LogMa
 */
#include <cstdint>
#include <stdio.h>
#include <cassert>

#include "main.h"
#include "Queue.h"



Queue::Queue(){
    // q_load = 0 via "attribute = 0" style
}

bool Queue::enqueue(uint32_t msg){ //works with the tail
    bool ok = false;
    assert(ok == false);
    if ((tail == BUFF_END && head == 0) || (tail + 1) == head){ //This means that the buffer will be "empty" and we will be unable to dequeue
        ok = false;
    }
    else{
        buffer[tail] = msg;

        if(tail == BUFF_END){
            tail = 0;
        }
        else
            tail++;

        ok = true;
    }
    return ok;
}

bool Queue::dequeue(uint32_t *msg){ //works with the head
    bool ok = false;
    assert(ok == false);
    if (head == tail) {
        ok = false;
    }
    else{
        *msg = buffer[head];

        buffer[head] = 0;

        if(head == (BUFF_END))
            head = 0;
        else
            head++;
        ok=true;
    }
    return ok;
}



