#include "stdafx.h"
#include "InFlightPacket.h"


InFlightPacket::InFlightPacket(PacketSequenceNumber secNumber) : mSequenceNumber(secNumber)
{
}


InFlightPacket::~InFlightPacket()
{
}


void InFlightPacket::SetTransmissionData(int inKey,	TransmissionDataPtr inTransmissionData)
{
	mTransmissionDataMap[inKey] = inTransmissionData;
}


const TransmissionDataPtr InFlightPacket::GetTransmissionData(int inKey) const
{
	auto it = mTransmissionDataMap.find(inKey);
	return (it != mTransmissionDataMap.end()) ? it->second : nullptr;
}


void InFlightPacket::HandleDeliveryFailure(DeliveryNotificationManager* inDeliveryNotificationManager) const
{
	for (const auto& pair : mTransmissionDataMap)
	{
		pair.second->HandleDeliveryFailure(inDeliveryNotificationManager);
	}
}


void InFlightPacket::HandleDeliverySuccess(DeliveryNotificationManager* inDeliveryNotificationManager) const
{
	for (const auto& pair : mTransmissionDataMap)
	{
		pair.second->HandleDeliverySuccess(inDeliveryNotificationManager);
	}
}

PacketSequenceNumber InFlightPacket::GetSequenceNumber() const
{
	return mSequenceNumber;
}

float InFlightPacket::GetTimeDispatched() const
{
	return mTimeDispatched;
}
