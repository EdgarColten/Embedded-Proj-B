/*
 * inputQueue.cpp
 *
 *  Created on: Nov 1, 2024
 *      Author: LogMa
 */
#include <cassert>

#include "main.h"
#include "cpp_main.h"
#include "inputQueue.h"

inputQueue::inputQueue(){
    // q_load = 0 via "attribute = 0" style
}

bool inputQueue::enqueue(nextState msg){ //works with the tail
    bool ok = false;
    if ((tail == Q_BUFFER_END && head == 0) || (tail + 1) == head){ //This means that the buffer will be "empty" and we will be unable to dequeue
        ok = false;
    }
    else{
    	assert((tail + 1) != head);
        buffer[tail] = msg;

        if(tail == Q_BUFFER_END){
            tail = 0;
        }
        else
            tail++;

        ok = true;
    }
    return ok;
}

bool inputQueue::dequeue(nextState *msg){ //works with the head
    bool ok = false;
    if (head == tail) {
        ok = false;
        assert(ok == false);
    }
    else{
        *msg = buffer[head];
        /*for (uint16_t n = 0; n<q_load; n++){
            buffer[n] = buffer[n+1];
        }*/
        nextState clear;
        clear.btn_S = 0;
        clear.knobA = 0;
        clear.knobD = 0;
        clear.knobF = 0;
        clear.sw_select = 1;

        buffer[head] = clear;

        if(head == (Q_BUFFER_END))
            head = 0;
        else
            head++;
        ok=true;
    }
    return ok;
}

