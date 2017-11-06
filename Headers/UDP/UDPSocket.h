#pragma once

#include "stdafx.h"
#include "SocketAddress.h"

class UDPSocketFactory;
class UDPSocket;
typedef std::shared_ptr<UDPSocket> UDPSocketPtr;

class UDPSocket
{
public:
	~UDPSocket();
	int Bind(const SocketAddress& inToAddress);
	int SendTo(const void* inData, int inLen, const SocketAddress& inTo);
	int ReceiveFrom(void* inBuffer, int inLen, SocketAddress& outFrom);
	int SetNonBlockingMode(bool inShouldBeNonBlocking);
private:
	friend class UDPSocketFactory;
	UDPSocket(SOCKET inSocket) : mSocket(inSocket) {}
	SOCKET mSocket;
};

