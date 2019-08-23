// SocketServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


using namespace std;

int main()
{
    OutputDebugStringA("");
    WSADATA WSAData;

    SOCKET server, client;

    SOCKADDR_IN serverAddr, clientAddr;

    WSAStartup(MAKEWORD(2, 0), &WSAData);
    server = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5555);

    bind(server, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
    listen(server, 0);

    cout << "Listening for incoming connections..." << endl;

    char buffer[30000];
    int clientAddrSize = sizeof(clientAddr);
    if ((client = accept(server, (SOCKADDR *)&clientAddr, &clientAddrSize)) != INVALID_SOCKET)
    {
        cout << "Client connected!" << endl;
        recv(client, buffer, sizeof(buffer), 0);
        //cout << "Message from Client : " << buffer << endl;
        //fill(std::begin(buffer), std::end(buffer), 'b');
        send(client, buffer, sizeof(buffer), 0);
        //cout << "Message sent to Client : " << buffer << endl;

        closesocket(client);
        cout << "Client disconnected." << endl;
    }
    getchar();
}