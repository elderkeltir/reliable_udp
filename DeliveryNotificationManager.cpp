#include "stdafx.h"
#include "DeliveryNotificationManager.h"


DeliveryNotificationManager::DeliveryNotificationManager() : kAckTimeout(60000)
{
}


DeliveryNotificationManager::~DeliveryNotificationManager()
{
}


InFlightPacket* DeliveryNotificationManager::WriteSequenceNumber(OutputMemoryBitStream& inPacket)
{
	PacketSequenceNumber sequenceNumber = mNextOutgoingSequenceNumber++;
	inPacket.Write(sequenceNumber);
	++mDispatchedPacketCount;
	auto inFlightPacket = InFlightPacket(sequenceNumber);
	mInFlightPackets.emplace_back(inFlightPacket);
	return &mInFlightPackets.back();
}


bool DeliveryNotificationManager::ProcessSequenceNumber(InputMemoryBitStream& inPacket)
{
	PacketSequenceNumber sequenceNumber;
	inPacket.Read(sequenceNumber);
	if (sequenceNumber == mNextExpectedSequenceNumber)
	{
		//is this expected? add ack to the pending list and process packet
		mNextExpectedSequenceNumber = sequenceNumber + 1;
		AddPendingAck(sequenceNumber);
		return true;
	}
	//otherwise, we missed some packets
	else if (sequenceNumber > mNextExpectedSequenceNumber)
	{
		//consider all skipped packets as dropped, so
		//our next expected packet comes after this one ...
		mNextExpectedSequenceNumber = sequenceNumber + 1;
		//add an ack for the packet and process it
		//when the sender detects break it acks, it can resend
		AddPendingAck(sequenceNumber);
		return true;
	}
	//is sequence number < current expected? Then silently drop old packet.
	else
	{
		return false;
	}
}


void DeliveryNotificationManager::AddPendingAck(PacketSequenceNumber inSequenceNumber)
{
	if (mPendingAcks.size() == 0 ||
		!mPendingAcks.back().ExtendIfShould(inSequenceNumber))
	{
		mPendingAcks.emplace_back(inSequenceNumber);
	}
}


void DeliveryNotificationManager::WritePendingAcks(OutputMemoryBitStream& inPacket)
{
	bool hasAcks = (mPendingAcks.size() > 0);
	inPacket.Write(hasAcks);
	if (hasAcks)
	{
		mPendingAcks.front().Write(inPacket);
		mPendingAcks.pop_front();
	}
}


void DeliveryNotificationManager::ProcessAcks(InputMemoryBitStream& inPacket)
{
	bool hasAcks;
	inPacket.Read(hasAcks);
	if (hasAcks)
	{
		AckRange ackRange;
		ackRange.Read(inPacket);
		//for each InFlightPacket with seq# < start, handle failure...
		PacketSequenceNumber nextAckdSequenceNumber =
			ackRange.GetStart();
		uint32_t onePastAckdSequenceNumber =
			nextAckdSequenceNumber + ackRange.GetCount();
		while (nextAckdSequenceNumber < onePastAckdSequenceNumber &&
			!mInFlightPackets.empty())
		{
			const auto& nextInFlightPacket = mInFlightPackets.front();
			//if the packet seq# < ack seq#, we didn't get an ack for it,
			//so it probably wasn't delivered
			PacketSequenceNumber nextInFlightPacketSequenceNumber =
				nextInFlightPacket.GetSequenceNumber();
			if (nextInFlightPacketSequenceNumber < nextAckdSequenceNumber)
			{
				//copy this so we can remove it before handling-
				//dependent modules shouldn't find it if seeing what's live
				auto copyOfInFlightPacket = nextInFlightPacket;
				mInFlightPackets.pop_front();
				HandlePacketDeliveryFailure(copyOfInFlightPacket);
			}
			else if (nextInFlightPacketSequenceNumber == nextAckdSequenceNumber)
			{
				HandlePacketDeliverySuccess(nextInFlightPacket);
				//received!
				mInFlightPackets.pop_front();
				++nextAckdSequenceNumber;
			}
			else if (nextInFlightPacketSequenceNumber > nextAckdSequenceNumber)
			{
				//somehow part of this range was already removed
				//(maybe from timeout) check rest of range
				nextAckdSequenceNumber = nextInFlightPacketSequenceNumber;
			}
		}
	}
}


void DeliveryNotificationManager::ProcessTimedOutPackets()
{
	uint64_t timeoutTime = std::chrono::system_clock::now().time_since_epoch().count() - kAckTimeout;
	while (!mInFlightPackets.empty())
	{
		//packets are sorted, so all timed out packets must be at front
		const auto& nextInFlightPacket = mInFlightPackets.front();
		if (nextInFlightPacket.GetTimeDispatched() < timeoutTime)
		{
			HandlePacketDeliveryFailure(nextInFlightPacket);
			mInFlightPackets.pop_front();
		}
		else
		{
			//no packets beyond could be timed out
			break;
		}
	}
}


void DeliveryNotificationManager::HandlePacketDeliveryFailure(const InFlightPacket& inFlightPacket)
{
	++mDroppedPacketCount;
	inFlightPacket.HandleDeliveryFailure(this);
}


void DeliveryNotificationManager::HandlePacketDeliverySuccess(const InFlightPacket& inFlightPacket)
{
	++mDeliveredPacketCount;
	inFlightPacket.HandleDeliverySuccess(this);
}