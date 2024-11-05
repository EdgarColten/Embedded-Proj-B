/*
 * MemoryBuffer.cpp
 *
 *  Created on: Nov 4, 2024
 *      Author: LogMa
 */
#include "main.h"
#include "MemoryBuffer.h"
#include <cstdint>

MemoryBuffer::MemoryBuffer()
{

}

void MemoryBuffer::check_memory()
{

	for(uint8_t i = 0; i < 6; i++)
		if(memArr[i] != i)
			NVIC_SystemReset();
}

