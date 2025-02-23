#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>

// Need to link with Ws2_32.lib
#pragma comment(lib, "ws2_32.lib")

#define PORT 8080  //i need more infor regarding this port

int main()
{
    WORD wVersionRequested;
    WSADATA wsaData;

    wVersionRequested = MAKEWORD(2, 2);

    int err = WSAStartup(wVersionRequested, &wsaData);
    if(err != 0 )
    {
        printf("WSAStartup failed\n");
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //we created a new socket

    if(sock == INVALID_SOCKET)
    {
        printf("Socket coundn't be created\n");
        printf("Error code: %d\n", WSAGetLastError());
    }
    else
    {
        printf("Socket successfully created\n");
    }

    Sleep(1000);

    /*
        int status = shutdown(sock, 2);
        if(status != 0)
        {
            printf("Socket coundn't be shut down\n");
            printf("Error code: %d\n", WSAGetLastError());
        }
        else
        {
            printf("Socket successfully shut down\n");
        }

        WSACleanup();
    */

    return 0;
}