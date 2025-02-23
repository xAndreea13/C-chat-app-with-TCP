#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>

// need to link with Ws2_32.lib
#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    //initialize winsock
    WORD wVersionRequested;
    WSADATA wsaData;
    wVersionRequested = MAKEWORD(2, 2);

    int err = WSAStartup(wVersionRequested, &wsaData);
    if(err != 0 )
    {
        printf("WSAStartup failed\n");
    }

    //create a new socket
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(sock == INVALID_SOCKET)
    {
        printf("Socket coundn't be created\n");
        printf("Error code: %d\n", WSAGetLastError());
    }
    else
    {
        printf("Socket successfully created\n");
    }

    //set the server info and connect to the server socket
    struct sockaddr_in client_service;
    client_service.sin_family = AF_INET;
    client_service.sin_addr.s_addr = inet_addr("192.168.56.1");
    client_service.sin_port = htons(8080);

    err = connect(sock, (SOCKADDR*) &client_service, sizeof(client_service));
    if(err != 0)
    {
        printf("Socket connection failed\n");
        printf("Error code: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    else
    {
        printf("Socket connected successfully. App ready to send messages...\n");
    }

    char message[BUFFER_SIZE];
    printf("Message: ");
    fgets(message, BUFFER_SIZE, stdin);
    int len = strlen(message);
    if (len > 0 && message[len - 1] == '\n') 
    {
        message[len - 1] = '\0';
    }

    if(message[0] != '\0')
    {
        
        do
        {
            send(sock, message, BUFFER_SIZE, 0); //we send the message after we checked the while
            printf("Message: ");
            fgets(message, BUFFER_SIZE, stdin);
            int len = strlen(message);
            if (len > 0 && message[len - 1] == '\n') 
            {
                message[len - 1] = '\0';
            }

        }while(message[0] != '\0');
    }
    else
    {
        printf("Connection closed");
    }

    closesocket(sock);
    WSACleanup();
   
    return 0;
}