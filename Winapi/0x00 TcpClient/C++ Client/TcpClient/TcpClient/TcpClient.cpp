
#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>

// link winsock
#pragma comment(lib, "ws2_32.lib")


#define RHOST "127.0.0.1"
#define RPORT 8080
#define BUFF  4096

int main(int argc, char* argv[]) {
	int iResult;
	// load dll to process (initialize winsock) and check for error
	WSADATA wsaData;
	if ((iResult = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) {
		std::cerr << "Could not Initialize Winsock" << iResult << std::endl;
		ExitProcess(EXIT_FAILURE);
	}
	// define socket
	SOCKET ConnectSocket = INVALID_SOCKET;

	// initialize socket
	if ((ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
		std::cerr << "Invalid Socket Error!!!" << std::endl;
		ExitProcess(EXIT_FAILURE);
	}
	// set up the struct needed by the connect function
	struct sockaddr_in sa;
	sa.sin_family = AF_INET;             // set af inet
	sa.sin_port = htons(RPORT);          // host to network short

	// convert string representation into bin repr
	inet_pton(AF_INET, RHOST, &sa.sin_addr);

	// connect to server
	if ((connect(ConnectSocket, (sockaddr*)&sa, sizeof(sa))) == INVALID_SOCKET) {
		std::cerr << "Invalid Socket Error" << std::endl;
		ExitProcess(EXIT_FAILURE);
	}
	// debug message
	std::cout << "Client is Connected!!!" << std::endl;
	
	// bytes to char
	const char* data = "Mirai Nikki";

	// send payload to the server
	if ((iResult = send(ConnectSocket, data, (int) strlen(data), 0)) == SOCKET_ERROR) {
		std::cerr << "Could not send message!!!" << std::endl;
		ExitProcess(EXIT_FAILURE);
	}
	// Close Socket and Unlaod DLL
	closesocket(ConnectSocket);
	WSACleanup();

	return 0;

}
