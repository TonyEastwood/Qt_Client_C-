#include "client.h"

void EndTheMessage(char * message)
{
    for(int i=0;;i++)
    {
        if (message[i]=='\0')
        {
            message[i]='\r';
            message[i+1]='\n';
            message[i+2]='\0';
            break;
        }

    }
}


Client::Client(QObject *parent) : QObject(parent)
{

}


bool Client::ConnectToServer(QString host, int port)
{
    socket=new QTcpSocket();                        //initialize socket as tcp socket
    socket->connectToHost(host,port);                 //try connect to server host:port
    if(socket->waitForConnected(30000))              //wait 30000ms for connection
        return true;                                //if connection establish success, return true
    else return false;                              //else return false
}

void Client::SendData()                              //send data on server
{
    char data[1024]="wefwefwe";                                 //buff for send data

       while(IfConnectedToServ())                   //till connection establish, send data from istream
       {
      std::cin.getline (data,1024);                  //input data for send on socket
        EndTheMessage(data);                        //add \r \n \0 in the and of message, that mean message end and server don't will wait for new data


        socket->write(data);                        //write data to socket
        socket->flush();                            //write all data from buffer
        socket->waitForBytesWritten(30000);          //wait till at least one byte has been written on the socket
        }
}
void Client::ReceiveData()                          //function read data from socket
{
     while(IfConnectedToServ())                     //till connection establish, send data from istream
    {
        std::cout<<socket->readAll().data();        //read all data from socket
       socket->waitForReadyRead(30000);             //wait till all data will be read
        socket->waitForBytesWritten(30000);          //wait till at least one byte has been written on the socket
    }
}

bool Client::IfConnectedToServ()                //check if connection establish now
{
    return socket->state()==QTcpSocket::ConnectedState;         //return connection state
}

void Client::DisconnectFromServer()
{
   socket->close();                                 //close socket, disconect
}


Client::~Client()
{
    if(IfConnectedToServ())
    DisconnectFromServer();                          //close socket before delete that
    delete socket;                              //delete pointer on socket
}


