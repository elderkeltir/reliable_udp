#pragma once
#include "MemoryStream.h"

class OutputMemoryBitStream : public MemoryStream
{
public:
	OutputMemoryBitStream();

	uint32_t GetBitLength() const { return mHead; }
	uint32_t GetByteLength() const { return (mHead + 7) >> 3; }

	void WriteBytes(const void* inData, size_t inByteCount)
		{ WriteBits(inData, inByteCount << 3); }

	void WriteBits(uint8_t inData, size_t inBitCount);
	void WriteBits(const void* inData, size_t inBitCount);

private:
	void ReallocBuffer(uint32_t inNewBitCapacity);
};

