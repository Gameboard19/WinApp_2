#include "pch.h"
#include "Network.h"

Network::Network(SOCKET_MODE mode) {
	currentMode_ = mode;
}
bool Network::Init() {
	int result = WSAStartup(MAKEWORD(2, 2), &wsadata_);
	if (result != 0 || (LOBYTE(wsadata_.wVersion) != 2 || HIBYTE(wsadata_.wVersion) != 2)) {
		//implement a return statement here. this will happen but not yet.
		return false;
	}
	return true;
}
bool Network::ShutDown() {
	//until I get this coded
	return false;
}