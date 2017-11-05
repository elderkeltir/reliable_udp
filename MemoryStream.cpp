#include "stdafx.h"
#include "MemoryStream.h"


MemoryStream::MemoryStream(char* inBuffer, uint32_t inByteCount) : mBuffer(inBuffer), mCapacity(inByteCount), mHead(0)
{
}


