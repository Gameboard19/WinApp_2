#pragma once
#include <Windows.h>
#include <Winsock2.h>

enum SOCKET_MODE {
	SERVER,
	CLIENT
};
class Network {
private:
	SOCKET_MODE currentMode_;
	SOCKET socket_;
	WSADATA wsadata_;
	sockaddr sockAddr_;
public:
	Network(SOCKET_MODE);
	Network();
	SOCKET_MODE GetMode() { return currentMode_; };
	bool Init();
	bool ShutDown();
	bool BindSocket();
	bool Accept();
};

