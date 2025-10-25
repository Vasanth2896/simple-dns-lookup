#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

#define BUFF_SIZE 500

typedef struct addrinfo AddressInfo;

int socketCreation()
{
    int serverSocket = socket(AF_INET, SOCK_DGRAM, 0);

    if (serverSocket == -1)
    {
        perror("Error in creating socket");
        return 1;
    }

    return serverSocket;
}

int terminateSocket(int desiredSocket)
{
    int closeStatus = close(desiredSocket);

    if (closeStatus == -1)
    {
        perror("Error in closing the socket");
        return 1;
    }
    std::cout << "Socket has been successfully closed" << std::endl;

    return 0;
}

void lookupWithAddressInfoLibrary()
{
    int result, socketFileDescriptor;
    AddressInfo hints;
    AddressInfo *presult, *printResult;

    const char *node = "www.google.com";
    const char *service = "http";
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; /* Allow IPv4 or IPv6 */
    hints.ai_socktype = 0;       /* Any type of socket */
    hints.ai_flags = 0;
    hints.ai_protocol = 0; /* Any protocol */

    result = getaddrinfo(node, service, &hints, &presult);
    if (result != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(result));
        exit(EXIT_FAILURE);
    }

    std::cout << "DNS Lookup for " << *node << std::endl;
    for (printResult = presult; printResult != NULL; printResult = printResult->ai_next)
    {
        std::cout << "Desired Address type IPv4 or IPv6" << std::endl;
        switch (printResult->ai_family)
        {
        case AF_INET:
            std::cout << "This is ipv4" << std::endl;
            break;
        case AF_INET6:
            std::cout << "This is ipv6" << std::endl;
            break;
        default:
            std::cout << "No Idea of the address type" << std::endl;
            break;
        }
        std::cout << printResult->ai_socktype << std::endl;
        std::cout << printResult->ai_protocol << std::endl;
    }

    freeaddrinfo(presult);
}

int main()
{

    std::cout << "Performing DNS lookup" << std::endl;
    int currentSocket = socketCreation();
    std::cout << "This is the socket " << currentSocket << std::endl;

    lookupWithAddressInfoLibrary();

    int closeSocket = terminateSocket(currentSocket);
    std::cout << "This is the socket status " << closeSocket << std::endl;

    return 0;
}