#pragma once

#include "OutputMemoryBitStream.h"
#include "InputMemoryBitStream.h"

using PacketSequenceNumber = uint16_t;

class AckRange
{
public:
	AckRange();
	~AckRange();

	bool ExtendIfShould(PacketSequenceNumber inSequenceNumber);
	void Write(OutputMemoryBitStream& inPacket) const;
	void Read(InputMemoryBitStream& inPacket);
private:
	uint32_t mCount;
	uint32_t mStart;
};

