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


void printIpAddress(AddressInfo_t *printResult, char *internetAddressString, int bufferSize)
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
    std::cout << std::endl;
}

void lookupWithAddressInfoLibrary(char *node)
{
    int result;
    // int socketFileDescriptor;
    AddressInfo_t hints;
    AddressInfo_t *presult, *printResult;

    char *service = nullptr;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; /* Allow IPv4 or IPv6 */
    hints.ai_socktype = 0;       /* Any type of socket */
    hints.ai_flags = 0;
    hints.ai_protocol = 0; /* Any protocol */
    hints.ai_canonname = nullptr;
    hints.ai_addr = nullptr;
    hints.ai_next = nullptr;

    // hold the address in string format
    char internetAddressString[INET6_ADDRSTRLEN];

    result = getaddrinfo(node, service, &hints, &presult);
    if (result != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(result));
        exit(EXIT_FAILURE);
    }

    std::cout << "DNS Lookup for " << node << std::endl;
    for (printResult = presult; printResult != NULL; printResult = printResult->ai_next)
    {
        switch (printResult->ai_family)
        {
        case AF_INET:
            std::cout << "Family: IPv4" << std::endl;
            break;
        case AF_INET6:
            std::cout << "Family: IPv6" << std::endl;
            break;
        }

        switch (printResult->ai_socktype)
        {
        case SOCK_STREAM:
            std::cout << "SocketType: TCP/IP" << std::endl;
            break;
        case SOCK_DGRAM:
            std::cout << "SocketType: UDP" << std::endl;
            break;
        }

        switch (printResult->ai_protocol)
        {
        case IPPROTO_TCP:
            std::cout << "Protocol: TCP" << std::endl;
            break;
        case IPPROTO_UDP:
            std::cout << "Protocol: UDP" << std::endl;
            break;
        case IPPROTO_IP:
            std::cout << "Protocol: IP" << std::endl;
            break;
        default:
            std::cout << "Protocol: Unknown (" << printResult->ai_protocol << ")" << std::endl;
            break;
        }

        printIpAddress(printResult, internetAddressString, sizeof(internetAddressString));
    }

    freeaddrinfo(presult);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "usage: dns <hostname>" << std::endl;
        return -1;
    }

    std::cout << "Performing DNS lookup for " << argv[1] << std::endl;

    lookupWithAddressInfoLibrary(argv[1]);

    return 0;
}