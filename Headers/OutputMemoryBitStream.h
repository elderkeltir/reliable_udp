#pragma once
#include "MemoryStream.h"

class OutputMemoryBitStream : public MemoryStream
{
public:
	OutputMemoryBitStream();

	uint32_t GetBitLength() const { return mHead; }
	uint32_t GetByteLength() const { return (mHead + 7) >> 3; }

	void WriteBits(uint8_t inData, size_t inBitCount);
	void WriteBits(const void* inData, size_t inBitCount);

	template<typename T>
	void Write(T inData, size_t inBitCount = sizeof(T) * 8)
	{
		static_assert(std::is_arithmetic<T>::value ||
			std::is_enum<T>::value,
			"Generic Write only supports primitive data types");
		WriteBits(&inData, inBitCount);
	}

	template<typename bool>
	void Write(bool inData, size_t inBitCount = 1)
	{
		WriteBits(&inData, inBitCount);
	}

private:
	void ReallocBuffer(uint32_t inNewBitCapacity);
};

