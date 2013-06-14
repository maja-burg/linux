#include "Connection.h"

// Konstruktor
Connection::Connection(string host, int port, string channel)
{
    this->host = host;
    this->port = port;
    this->channel = channel;
}

// Destruktor
Connection::~Connection()
{
}

void Connection::Connect() {
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Failed to create socket...");
        Disconnect();
        return false;
    }
    hostent *hp = gethostbyname(host.c_str());
    if (!hp)
    {
        perror("Failed to get hostname...");
        Disconnect();
        return false;
    }

    sockaddr_in sin;
    memset((char*)&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    memcpy((char*)&sin.sin_addr, hp->h_addr, hp->h_length);
    sin.sin_port = htons(port);
    memset(&(sin.sin_zero), 0, 8*sizeof(char));

    if (connect(sock, (sockaddr*) &sin, sizeof(sin)) == -1)
    {
        perror("Failed to connect socket...");
        Disconnect();
        return false;
    } return true;

}
void Connection::Disconnect()
{
    close(sock);
}
void Connection::Identify(string name, string pw, string channel)
{
    Send("NICK " + name + "\r\n");
    Send("USER " + name + " 0 0  :" + name + "\r\n");
    Send("PRIVMSG NickServ IDENTIFY " + pw + "\r\n");
    Send("JOIN #" + channel + "\r\n");
    Send("PRIVMSG #" + channel + ":Hallo!\r\n");
}
void Connection::PingPong(string buffer)
{

}
int Connection::ParseIrc(string buffer)
{

}
int Connection::BotFunctions(string buffer)
{

}
void Connection::SetChannel(string channel)
{
    Send("JOIN #" + channel + "\r\n");
    this->channel = channel;
}
string Connection::GetChannel()
{
    return channel;
}
