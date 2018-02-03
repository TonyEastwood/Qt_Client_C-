#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <iostream>

class Client : public QObject
{
    Q_OBJECT
private:
    QTcpSocket *socket;                                  //socket for establish connections
public:
    explicit Client(QObject *parent = nullptr);         //non convertible constructor
    bool ConnectToServer(QString host, int port);       //establish connection with server socket = host:port
    void SendData();                                    //data, that we send on server
    bool IfConnectedToServ();                           //check if connection establish now
    void DisconnectFromServer();                        //close connection
    void ReceiveData();                              //receive data from server
     ~Client();                                         //destructor
signals:


public slots:


};


#endif // CLIENT_H
