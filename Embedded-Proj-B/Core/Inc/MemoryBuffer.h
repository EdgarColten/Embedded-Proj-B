/*
 * MemoryBuffer.h
 *
 *  Created on: Nov 4, 2024
 *      Author: LogMa
 */

/**
 * @file	MemoryBuffer.h
 * @brief	Memory Barrier.
 */
#include <cstdint>

#ifndef INC_MEMORYBUFFER_H_
#define INC_MEMORYBUFFER_H_


class MemoryBuffer{
	uint8_t memArr[6] = {0,1,2,3,4,5};

public:
	MemoryBuffer();
	/**
	 * @brief checks values stored in the memory buffer
	 * This function uses a simple for loop to check that the value at each index is what is defined in the member variable "memArr".
	 * This is used to verify that no IPC enqueued beyond its defined size.
	 * If an IPC enqueues beyond its defined size it will change a value within memArr and the system will restart.
	 */
	void check_memory();

};


#endif /* INC_MEMORYBUFFER_H_ */
