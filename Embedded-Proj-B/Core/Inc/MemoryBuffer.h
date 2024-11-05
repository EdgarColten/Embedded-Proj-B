/*
 * MemoryBuffer.h
 *
 *  Created on: Nov 4, 2024
 *      Author: LogMa
 */
#include <cstdint>

#ifndef INC_MEMORYBUFFER_H_
#define INC_MEMORYBUFFER_H_


class MemoryBuffer{
	uint8_t memArr[6] = {0,1,2,3,4,5};

public:
	MemoryBuffer();
	void check_memory();

};


#endif /* INC_MEMORYBUFFER_H_ */
