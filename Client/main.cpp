#include <QCoreApplication>
#include "client.h"
#include <iostream>
#include <QtConcurrent/QtConcurrent>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Client client;                                                    //create client for establish connections
    char _host[30];                                                 //domen that we want to connect (or ip adress)
    int _port;                                                      //port that open on server that we want to connect

    std::cout<<"Input host and port that you want to connect:"<<std::endl<<"host:";
    std::cin>>_host;                                                     //input host
    std::cout<<"port:";
    std::cin>>_port;                                                      //input port

    if(client.ConnectToServer(_host,_port))                         //create socket and connect to server
    std::cout<<"Connections with host established success! "<<std::endl;
    else
    {
        std::cout<<"\nConnection failed... Try another host or port"<<std::endl;
        client.~Client();                                               //call destructor
         return a.exec();                                               //the same return 0
    }
 QtConcurrent::run(&client, &Client::ReceiveData);                      //create new thread for ReceiveData (multithreading)
    client.SendData();                                                  //run loop for SendData on socket (server)
    client.~Client();                                                   //call destructor to delete pointer on socket
    return a.exec();
}
