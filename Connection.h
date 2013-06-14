#ifndef CONNECTION_H
#define CONNECTION_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <time.h>
#include <stdio.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

using namespace std;

class Connection {
public:
    Connection(string host, int port, string channel);
    ~Connection();

private:
    string  host;
    int     port;
    string  channel;

    void    Connect();
    void    Disconnect();

    void    Send(string msg);
    bool    Receive(string &buf);

    void    Identify(string name, string pw, string channel);
    void    PingPong(string buffer);
    int     ParseIrc(string buffer);
    void    SetChannel(string channel);
    string  GetChannel();

};


#endif
