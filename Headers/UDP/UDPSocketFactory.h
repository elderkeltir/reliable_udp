#pragma once

#include "stdafx.h"
#include "UDPSocket.h"

enum SocketAddressFamily
{
	INET = AF_INET,
	INET6 = AF_INET6
};

class UDPSocketFactory
{
public:
	static UDPSocketPtr CreateUDPSocket(SocketAddressFamily inFamily);
};

