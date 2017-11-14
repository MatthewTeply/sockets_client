#include <iostream>
#include <windows.h>
#include <stdio.h>

using namespace std;

#pragma comment(lib, "ws2_32.lib")

SOCKET sock;
SOCKADDR_IN i_sock;
WSADATA data;

int Connect(char *IP, int port) {

	WSAStartup(MAKEWORD(2,2), &data);
	sock = socket(AF_INET, SOCK_STREAM, 0);

	if(sock == INVALID_SOCKET)
		return 1;

	i_sock.sin_family = AF_INET;
	i_sock.sin_addr.s_addr = inet_addr(IP);
	i_sock.sin_port = htons(port);

	int ss = connect(sock, (struct sockaddr *)&i_sock, sizeof(i_sock));

	if(ss != 0) {
	
		cout << "Cannot connect!" << endl;
		return 0;
	}

	cout << "Successfuly connected!" << endl;
	return 1;
}

int send(char *Buf, int len, int client) { //int len = size of data that will be sent to the Buf, int client = client ID

	int slen = send(sock, Buf, len, 0); //'sock2[client]' = accepted client ID, Buf = data sent, len = size of sent data, 0 = specifying call (ignore for now)

	if(slen < 0) { //If the size of the data is zero, meaning there is no data, data won't be sent
	
		cout << "Cannot send data!" << endl;
		return 1;
	}

	return slen; //Return the length of the sent data, in bytes
}

int recieve(char *Buf, int len, int client) { //Buf = data, len = data length, client = client ID

	int slen = recv(sock, Buf, len, 0); //Length of recieved data

	if(len < 0) {
	
		cout << "Cannot send data!" << endl;
		return 1;
	}

	return slen; //Return length of the recieved data
}

int main() {

	Connect("172.16.2.17", 3000);
	cout << "Client still working!" << endl;
	
	getchar();
	getchar();

	return 0;
}