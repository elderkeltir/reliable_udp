// reliableudp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

BOOLEAN WINAPI DllMain(IN HINSTANCE hDllHandle,
	IN DWORD     nReason,
	IN LPVOID    Reserved)
{
	BOOLEAN bSuccess = TRUE;


	//  Perform global initialization.

	switch (nReason)
	{
	case DLL_PROCESS_ATTACH:

		//  For optimization.

		WORD wVersionRequested;
		WSADATA wsaData;
		int err;
		wVersionRequested = MAKEWORD(2, 2);
		err = WSAStartup(wVersionRequested, &wsaData);

		break;

	case DLL_PROCESS_DETACH:
		WSACleanup();

		break;
	}
}


int main()
{
	/*WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	





	WSACleanup();*/


	char * buff = nullptr;
	unsigned int Bsize = 256;
	unsigned int head = 0;
	buff = static_cast<char*>(std::realloc(buff, Bsize));

	// write

	int val1 = 20;
	void * val1p = reinterpret_cast<void*>(val1);
	std::memcpy(buff, &val1, sizeof(val1));

	head += sizeof(val1);

	char* val2 = "test";
	std::memcpy(buff + head, val2, sizeof(val2)+1);


	// read
	int val1R = 0;




	std::memcpy(&val1R, buff, sizeof(val1R));

	char* val2R = new char[5];

	std::memcpy(val2R, buff + head, sizeof(val2R));
	val2R[4] = '\0';

	return 0;
}