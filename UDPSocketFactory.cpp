#include "stdafx.h"
#include "UDPSocketFactory.h"
#include "SocketUtil.h"


UDPSocketPtr UDPSocketFactory::CreateUDPSocket(SocketAddressFamily inFamily)
{
	SOCKET s = socket(inFamily, SOCK_DGRAM, IPPROTO_UDP);
	if (s != INVALID_SOCKET)
	{
		return UDPSocketPtr(std::make_shared<UDPSocket>(UDPSocket(s)));
	}
	else
	{
		SocketUtil::ReportError(L"SocketUtil::CreateUDPSocket");
		return nullptr;
	}
}