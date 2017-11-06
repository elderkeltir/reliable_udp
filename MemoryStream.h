#pragma once

class MemoryStream
{
public:
	MemoryStream(char* inBuffer, uint32_t inByteCount);

	const char* GetBufferPtr() const { return mBuffer; }
	uint32_t GetLength() const { return mHead; }

	virtual ~MemoryStream() { std::free(mBuffer); }
protected:
	char* mBuffer;
	uint32_t mHead;
	uint32_t mCapacity;
};

