
#include <ws2tcpip.h>
#include <string.h>
#include <iostream>

#define LHOST "127.0.0.1"
#define LPORT 26437
#define BUFF  4096

// this server is the most secure server ever haha no buffer overflow risk xd

#pragma comment(lib, "ws2_32.lib")

int main(int argc, char* argv[]) {

	int iResult;

	// initialize Winsock
	WSADATA wsaData;

	// Initialize Winsock
	if ((iResult = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) {
		// write debug message to stdout
		std::cerr << "Could not Initialize Winsock!!!" << std::endl;
		// exit Process
		ExitProcess(EXIT_FAILURE);
	}
	// Create Socket object
	SOCKET ServerSocket = INVALID_SOCKET;

	// Initialize Socket and check for error
	if ((ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
		// write debug message to stdout
		std::cerr << "Error could not create Socket" << std::endl;
		// Unload dll
		WSACleanup();
		// exit Process
		ExitProcess(EXIT_FAILURE);
	}
	// set the structure needed for the bind function
	struct sockaddr_in sa;
	// convert ip to bytes
	inet_pton(AF_INET, LHOST, (sockaddr*)&sa.sin_addr);
	// host to network short
	sa.sin_port = htons(LPORT);
	// set adress family
	sa.sin_family = AF_INET;
	// bind socket 
	if ((iResult = bind(ServerSocket, (struct sockaddr*)&sa, sizeof(sa))) == SOCKET_ERROR) {
		// write debug message to stdout
		std::cerr << "Could not bind socket!!!" << WSAGetLastError() << std::endl;
		// close socket
		closesocket(ServerSocket);
		// wsa cleanup
		WSACleanup();
		// exit process
		ExitProcess(EXIT_FAILURE);
	}
	// listen for client ...
	if ((iResult = listen(ServerSocket, 1)) != 0) {
		// write debug message to stdout
		std::cerr << "Could not set socket into listen mode" << std::endl;
		// close socket
		closesocket(ServerSocket);
		// wsa cleanup
		WSACleanup();
		// exit process
		ExitProcess(EXIT_FAILURE);
	}
	// accept incomming connetion
	SOCKET AcceptSocket = INVALID_SOCKET;
	// waiting for the client to connect
	if ((AcceptSocket = accept(ServerSocket, NULL, NULL)) == INVALID_SOCKET) {
		// write debug message to stdout
		std::cerr << "Could not Create AcceptSocket" << std::endl;
		// close socket
		closesocket(ServerSocket);
		// wsa cleanup
		WSACleanup();
		// exit process
		ExitProcess(EXIT_FAILURE);
	}
	// allocate some bytes on the stack and overwrite memory with 0
	char data[BUFF]; 
	ZeroMemory(data, BUFF);

	recv(AcceptSocket, data, BUFF, 0);

	std::cout << data << std::endl;

	// cleanup
	closesocket(AcceptSocket);
	WSACleanup();

	return 0;

}
