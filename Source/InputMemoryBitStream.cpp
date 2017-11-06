#include "stdafx.h"
#include "InputMemoryBitStream.h"


InputMemoryBitStream::InputMemoryBitStream(char * inBuffer, int inHead) : MemoryStream(inBuffer, inHead)
{
}


InputMemoryBitStream::~InputMemoryBitStream()
{
}


void InputMemoryBitStream::ReadBits(uint8_t& outData, uint32_t inBitCount)
{
	uint32_t byteOffset = mHead >> 3;
	uint32_t bitOffset = mHead & 0x7;

	outData = static_cast< uint8_t >(mBuffer[byteOffset]) >> bitOffset;

	uint32_t bitsFreeThisByte = 8 - bitOffset;
	if (bitsFreeThisByte < inBitCount)
	{
		//we need another byte
		outData |= static_cast< uint8_t >(mBuffer[byteOffset + 1]) << bitsFreeThisByte;
	}

	//don't forget a mask so that we only read the bit we wanted...
	outData &= (~(0x00ff << inBitCount));

	mHead += inBitCount;
}

void InputMemoryBitStream::ReadBits(void* outData, uint32_t inBitCount)
{
	uint8_t* destByte = reinterpret_cast< uint8_t* >(outData);
	//write all the bytes
	while (inBitCount > 8)
	{
		ReadBits(*destByte, 8);
		++destByte;
		inBitCount -= 8;
	}
	//write anything left
	if (inBitCount > 0)
	{
		ReadBits(*destByte, inBitCount);
	}
}