#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>

// Need to link with Ws2_32.lib
#pragma comment(lib, "ws2_32.lib")

#define PORT 8080  //need more info regarding this port

int main()
{
    //start using windows socket dll
    WORD wVersionRequested;
    WSADATA wsaData;
    wVersionRequested = MAKEWORD(2, 2);

    int err = WSAStartup(wVersionRequested, &wsaData); 
    if(err != 0 )
    {
        printf("WSAStartup failed\n");
        printf("Error code: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    else
    {
        printf("WSAStartup called successfully\n");
    }

    //create a server/listening socket
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //created a new socket

    if(sock == INVALID_SOCKET)
    {
        printf("Socket coundn't be created\n");
        printf("Error code: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    else
    {
        printf("Socket created successfully\n");
    }

    //bind the socket
    struct sockaddr_in sa_server;
    struct hostent* local_host;
    char * local_ip;

    local_host = gethostbyname("");
    printf("Hostname: %s\n", local_host->h_name);
    local_ip = inet_ntoa(*(struct in_addr*)*local_host->h_addr_list);
    printf("Local IP: %s\n", local_ip);

    sa_server.sin_family = AF_INET;
    sa_server.sin_addr.s_addr = inet_addr(local_ip);
    sa_server.sin_port = htons(PORT);

    err = bind(sock, (SOCKADDR*) &sa_server, sizeof(sa_server));
    if(err != 0)
    {
        printf("Socket binding failed\n");
        printf("Error code: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    else
    {
        printf("Socket binded successfully\n");
    }

    //set the socket to listen to any incoming connection requests
    if(listen(sock, SOMAXCONN) == SOCKET_ERROR)
    {
        printf("Socket listening failed\n");
        printf("Error code: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    else
    {
        printf("Sever successfully initialized. The socket is listening ...");
    }

    //create another socket to accept the connection
    SOCKET acceptSock = accept(sock, NULL, NULL); //the accept function creates a new socket that represents the acctual connection between the client and the server
    if(acceptSock == INVALID_SOCKET)
    {
        printf("Accept socket couldn't be created\n");
        printf("Error code: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    else
    {
        printf("Accept socket created successfully\n");
    }
    
    //receive data

    //clean up
    WSACleanup();
   
    return 0;
}