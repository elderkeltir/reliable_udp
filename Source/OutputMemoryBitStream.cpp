#include "stdafx.h"
#include "OutputMemoryBitStream.h"


OutputMemoryBitStream::OutputMemoryBitStream() : MemoryStream(nullptr, 0)
{
	ReallocBuffer(256);
}


void OutputMemoryBitStream::ReallocBuffer(uint32_t inNewBitCapacity)
{
	mBuffer = static_cast<char*>(std::realloc(mBuffer, inNewBitCapacity));
	//handle realloc failure
	//...
	mCapacity = inNewBitCapacity;
}


void OutputMemoryBitStream::WriteBits(uint8_t inData, size_t inBitCount)
{
	uint32_t nextBitHead = mHead + static_cast<uint32_t>(inBitCount);
	if (nextBitHead > mCapacity)
	{
		ReallocBuffer(std::max(mCapacity * 2, nextBitHead));
	}
	//calculate the byteOffset into our buffer
	//by dividing the head by 8
	//and the bitOffset by taking the last 3 bits
	uint32_t byteOffset = mHead >> 3;
	uint32_t bitOffset = mHead & 0x7;

	//calculate which bits of the current byte to preserve
	uint8_t currentMask = ~(0xff << bitOffset);
	mBuffer[byteOffset] = (mBuffer[byteOffset] & currentMask) | (inData << bitOffset);
	//calculate how many bits were not yet used in
	//our target byte in the buffer
	uint32_t bitsFreeThisByte = 8 - bitOffset;
	//if we needed more than that, carry to the next byte
	if (bitsFreeThisByte < inBitCount)
	{
		//we need another byte
		mBuffer[byteOffset + 1] = inData >> bitsFreeThisByte;
	}
	mHead = nextBitHead;
}

void OutputMemoryBitStream::WriteBits(const void * inData, size_t inBitCount)
{
	const char* srcByte = static_cast<const char*>(inData);
	//write all the bytes
	while (inBitCount > 8)
	{
		WriteBits(*srcByte, 8);
		++srcByte;
		inBitCount -= 8;
	}
	//write anything left
	if (inBitCount > 0)
	{
		WriteBits(*srcByte, inBitCount);
	}
}
