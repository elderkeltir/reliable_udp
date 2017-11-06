#pragma once

#include "stdafx.h"


class SocketUtil
{
private:
public:
	
	static void ReportError(const std::wstring &msg) { std::wcout << msg << std::endl; }
	static int GetLastError() { return WSAGetLastError(); }
};

