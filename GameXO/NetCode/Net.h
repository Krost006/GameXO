#pragma once

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

class Socket {
protected:
	
	SOCKET socket_fd = 0;
	int port = 8080;
	sockaddr_in addr{};
	void send_msg(std::string msg) {};
	//Socket second;
public:
	Socket(int port);
	Socket(SOCKET soc);
	std::string recieve(SOCKET soc);
	~Socket();
};

class ServerSocket :public Socket {
public:
	ServerSocket(int port) : Socket(port) {};
	SOCKET list();
	void send_msg(SOCKET soc, std::string msg);
	SOCKET data();
};

class ClientSocket :public Socket {
	
public:
	ClientSocket(int port) : Socket(port) {};
	void set_server(std::string ip, int port);
	void send_msg(std::string msg);
	std::string recieve();
	~ClientSocket();
};