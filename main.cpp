#include<iostream>
#include<unistd.h>
#include<sys/socket.h>
using namespace std;

int socketCreation(){
    int serverSocket = socket(AF_INET,SOCK_STREAM,0);

    if(serverSocket == -1){
        perror("Error in creating socket");
        return 1;
    }

    return serverSocket;
}

int terminateSocket(int desiredSocket){
    int closeStatus = close(desiredSocket);


    if(closeStatus == -1){
        perror("Error in closing the socket");
        return 1;
    }
    cout << "Socket has been successfully closed" << endl;



    return 0;
}

int main(){
    int currentSocket = socketCreation();
    cout << "This is the socket " << currentSocket << endl;
    int closeSocket = terminateSocket(currentSocket);
    cout << "This is the socket status " << closeSocket << endl;
    
    return 0;
}