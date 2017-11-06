#pragma once

#include "TransmissionData.h"

class DeliveryNotificationManager;
using TransmissionDataPtr = std::shared_ptr<TransmissionData>;
using PacketSequenceNumber = uint16_t;

class InFlightPacket
{
public:
	InFlightPacket(PacketSequenceNumber secNumber);
	~InFlightPacket();
	void SetTransmissionData(int inKey, TransmissionDataPtr inTransmissionData);
	const TransmissionDataPtr GetTransmissionData(int inKey) const;
	void HandleDeliveryFailure(DeliveryNotificationManager* inDeliveryNotificationManager) const;
	void HandleDeliverySuccess(DeliveryNotificationManager* inDeliveryNotificationManager) const;
	PacketSequenceNumber GetSequenceNumber() const;
	float GetTimeDispatched() const;
private:
	PacketSequenceNumber mSequenceNumber;
	float mTimeDispatched;
	std::unordered_map<int, TransmissionDataPtr> mTransmissionDataMap;
};

