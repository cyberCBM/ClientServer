// SocketClient.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

using namespace std;

int main()
{
    WSADATA WSAData;
    SOCKET server;
    SOCKADDR_IN addr;

    WSAStartup(MAKEWORD(2, 0), &WSAData);
    server = socket(AF_INET, SOCK_STREAM, 0);

    //addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    // replace the ip with your future server ip address. If server AND client are running on the same computer, you can use the local ip 127.0.0.1
    InetPton(AF_INET, _T("127.0.0.1"), &addr.sin_addr.s_addr);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(5555);

    std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();
    connect(server, (SOCKADDR *)&addr, sizeof(addr));
    cout << "Connected to server!" << endl;
    std::chrono::high_resolution_clock::time_point endConn = std::chrono::high_resolution_clock::now();
    char buffer[30000];
    fill(std::begin(buffer), std::end(buffer), 'a');
    std::chrono::high_resolution_clock::time_point beginSend = std::chrono::high_resolution_clock::now();
    send(server, buffer, sizeof(buffer), 0);
    //cout << "Message sent to server!" << buffer << endl;
    std::chrono::high_resolution_clock::time_point endSend = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point beginRecv = std::chrono::high_resolution_clock::now();
    recv(server, buffer, sizeof(buffer), 0);
    //cout << "Message received from server!" << buffer << endl;
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    
    std::cout << "Time difference connection = " << std::chrono::duration<double>(endConn - begin).count() * 1000 << "[ms]" << std::endl;
    std::cout << "Time difference 30000k data send = " << std::chrono::duration<double>(endSend - beginSend).count() * 1000 << "[ms]" << std::endl;
    std::cout << "Time difference 30000k data transfer receive = " << std::chrono::duration<double>(end - beginRecv).count() * 1000 << "[ms]" << std::endl;
    std::cout << "Time difference 30000k data transfer round trip = " << std::chrono::duration<double>(end - beginSend).count() * 1000 << "[ms]" << std::endl;
    std::cout << "Time difference total = " << std::chrono::duration<double>(end - begin).count() * 1000 << "[ms]" << std::endl;

    closesocket(server);
    WSACleanup();
    cout << "Socket closed." << endl << endl;
    getchar();
}