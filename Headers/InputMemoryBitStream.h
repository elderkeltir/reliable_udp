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

	template<typename T>
	void Read(T& inData, size_t inBitCount = sizeof(T) * 8)
	{
		static_assert(std::is_arithmetic<T>::value ||
			std::is_enum<T>::value,
			"Generic Read only supports primitive data types");
		ReadBits(&inData, inBitCount);
	}

	template<typename bool>
	void Read(bool inData, size_t inBitCount = 1)
	{
		ReadBits(&inData, inBitCount);
	}
};

