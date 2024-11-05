/*
 * displayQueue.cpp
 *
 *  Created on: Oct 12, 2024
 *      Author: LogMa
 */


#include <cstdint>
#include <cassert>

#include <stdio.h>
#include "main.h"
#include "displayQueue.h"


displayQueue::displayQueue(){
    // q_load = 0 via "attribute = 0" style
}

bool displayQueue::enqueue(displayValues msg){ //works with the tail
    bool ok = false;
    assert(ok == false);
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

bool displayQueue::dequeue(displayValues *msg){ //works with the head
    bool ok = false;
    assert(ok == false);
    if (head == tail) {
        ok = false;
    }
    else{
        *msg = buffer[head];
        /*for (uint16_t n = 0; n<q_load; n++){
            buffer[n] = buffer[n+1];
        }*/
        displayValues clear;
        clear.F1 = 0;
        clear.F2 = 0;
        clear.channel = 0;
        clear.offset = 0;
        clear.type1 = sine;
        clear.type2 = sine;

        buffer[head] = clear;

        if(head == (BUFFER_END))
            head = 0;
        else
            head++;
        ok=true;
    }
    return ok;
}

