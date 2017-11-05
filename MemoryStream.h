#pragma once
class MemoryStream
{
public:
	MemoryStream(char* inBuffer, uint32_t inByteCount);

	virtual bool IsInput() const = 0;

	const char* GetBufferPtr() const { return mBuffer; }
	uint32_t GetLength() const { return mHead; }

	virtual ~MemoryStream() { std::free(mBuffer); }
protected:
	char* mBuffer;
	uint32_t mHead;
	uint32_t mCapacity;
};

