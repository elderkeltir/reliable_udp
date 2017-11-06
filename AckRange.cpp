#include "stdafx.h"
#include "AckRange.h"


AckRange::AckRange() : mStart(0), mCount(0)
{
}


AckRange::AckRange(PacketSequenceNumber start) : mStart(start), mCount(0)
{
}


AckRange::~AckRange()
{
}


bool AckRange::ExtendIfShould(PacketSequenceNumber inSequenceNumber)
{
	if (inSequenceNumber == mStart + mCount)
	{
		++mCount;
		return true;
	}
	else
	{
		return false;
	}
}


void AckRange::Write(OutputMemoryBitStream& inPacket) const
{
	inPacket.Write(mStart);
	bool hasCount = mCount > 1;
	inPacket.Write(hasCount);
	if (hasCount)
	{
		//let's assume you want to ack max of 8 bits...
		uint32_t countMinusOne = mCount - 1;
		uint8_t countToAck = countMinusOne > 255 ?
			255 : static_cast<uint8_t>(countMinusOne);
		inPacket.Write(countToAck);
	}
}


void AckRange::Read(InputMemoryBitStream& inPacket)
{
	inPacket.Read(mStart);
	bool hasCount = false;
	inPacket.Read(hasCount);
	if (hasCount)
	{
		uint8_t countMinusOne = 0;
		inPacket.Read(countMinusOne);
		mCount = countMinusOne + 1;
	}
	else
	{
		//default!
		mCount = 1;
	}
}

PacketSequenceNumber AckRange::GetStart() const
{
	return mStart;
}

PacketSequenceNumber AckRange::GetCount() const
{
	return mCount;
}
