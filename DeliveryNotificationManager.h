#pragma once

#include "OutputMemoryBitStream.h"
#include "InputMemoryBitStream.h"
#include "InFlightPacket.h"
#include "AckRange.h"

using PacketSequenceNumber = uint16_t;

class DeliveryNotificationManager
{
public:
	DeliveryNotificationManager();
	InFlightPacket* WriteSequenceNumber(OutputMemoryBitStream& inPacket);
	bool ProcessSequenceNumber(InputMemoryBitStream& inPacket);
	void AddPendingAck(PacketSequenceNumber inSequenceNumber);
	void WritePendingAcks(OutputMemoryBitStream& inPacket);
	void ProcessAcks(InputMemoryBitStream& inPacket);
	void ProcessTimedOutPackets();
	void HandlePacketDeliveryFailure(const InFlightPacket& inFlightPacket);
	void HandlePacketDeliverySuccess(const InFlightPacket& inFlightPacket);
	~DeliveryNotificationManager();
private:
	PacketSequenceNumber mNextOutgoingSequenceNumber;
	PacketSequenceNumber mDispatchedPacketCount;
	PacketSequenceNumber mNextExpectedSequenceNumber;
	std::vector<InFlightPacket> mInFlightPackets;
	std::deque<AckRange> mPendingAcks;
};

