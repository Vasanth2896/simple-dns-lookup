#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define BUFF_SIZE 500

using AddressInfo_t = struct addrinfo;
using InternetAddress_t = struct in_addr;
using sockAddress_t = struct sockaddr_in;
using sockAddress6_t = struct sockaddr_in6;

const char *toCString(const std::string &str)
{
    return str.c_str();
}

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

void printIpAddress(AddressInfo_t *printResult,char* internetAddressString, int bufferSize)
{
    void *addr;
    std::string ipver;
    sockAddress_t *ipv4;
    sockAddress6_t *ipv6;
    // get the pointer to the address itself,
    // different fields in IPv4 and IPv6:
    if (printResult->ai_family == AF_INET)
    { // IPv4
        ipv4 = (sockAddress_t *)printResult->ai_addr;
        addr = &(ipv4->sin_addr);
        ipver = "IPv4";
    }
    else
    { // IPv6
        ipv6 = (sockAddress6_t *)printResult->ai_addr;
        addr = &(ipv6->sin6_addr);
        ipver = "IPv6";
    }
    // convert the IP to a string and print it:
    inet_ntop(printResult->ai_family, addr, internetAddressString, bufferSize);
    std::cout << ipver << ": " << internetAddressString << std::endl;
}

void lookupWithAddressInfoLibrary()
{
    int result;
    // int socketFileDescriptor;
    AddressInfo_t hints;
    AddressInfo_t *presult, *printResult;

    std::string node = "www.google.com";
    std::string service = "http";
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; /* Allow IPv4 or IPv6 */
    hints.ai_socktype = 0;       /* Any type of socket */
    hints.ai_flags = 0;
    hints.ai_protocol = 0; /* Any protocol */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    // hold the address in string format
    char internetAddressString[INET6_ADDRSTRLEN];

    result = getaddrinfo(toCString(node), toCString(service), &hints, &presult);
    if (result != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(result));
        exit(EXIT_FAILURE);
    }

    std::cout << "DNS Lookup for " << node << std::endl;
    for (printResult = presult; printResult != NULL; printResult = printResult->ai_next)
    {
        std::cout << "Desired Address type IPv4 or IPv6" << std::endl;
        switch (printResult->ai_family)
        {
        case AF_INET:
            std::cout << "Family: ipv4" << std::endl;
            break;
        case AF_INET6:
            std::cout << "Family: ipv6" << std::endl;
            break;
        default:
            std::cout << "No Idea of the address type" << std::endl;
            break;
        }

        switch (printResult->ai_socktype)
        {
        case SOCK_STREAM:
            std::cout << "SocketType: tcp/ip" << std::endl;
            break;
        case SOCK_DGRAM:
            std::cout << "SocketType: udp" << std::endl;
            break;
        default:
            std::cout << "No Idea of the socket type" << std::endl;
            break;
        }

        std::cout << "This is the protocol " << printResult->ai_protocol << std::endl;

        printIpAddress(printResult,internetAddressString,sizeof(internetAddressString));
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