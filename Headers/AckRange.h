#pragma once

#include "OutputMemoryBitStream.h"
#include "InputMemoryBitStream.h"

using PacketSequenceNumber = uint16_t;

class AckRange
{
public:
	AckRange();
	AckRange(PacketSequenceNumber start);
	~AckRange();

	bool ExtendIfShould(PacketSequenceNumber inSequenceNumber);
	void Write(OutputMemoryBitStream& inPacket) const;
	void Read(InputMemoryBitStream& inPacket);
	PacketSequenceNumber GetStart() const;
	PacketSequenceNumber GetCount() const;
private:
	uint16_t mCount;
	PacketSequenceNumber mStart;
};

