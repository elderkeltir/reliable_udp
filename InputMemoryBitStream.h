#pragma once

#include "MemoryStream.h"
class InputMemoryBitStream :
	public MemoryStream
{
public:
	InputMemoryBitStream(char * inBuffer, int inHead);
	void ReadBits(uint8_t& outData, uint32_t inBitCount);
	void ReadBits(void* outData, uint32_t inBitCount);
	~InputMemoryBitStream();
};

