#pragma once

class DeliveryNotificationManager;

class TransmissionData
{
public:
	TransmissionData();
	~TransmissionData();
	virtual void HandleDeliveryFailure(DeliveryNotificationManager*) = 0;
	virtual void HandleDeliverySuccess(DeliveryNotificationManager*) = 0;
};

