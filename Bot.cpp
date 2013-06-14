#include "Bot.h"

// Konstruktor
Bot::Bot(string nickname, string password) {
    this->nickname = nickname;
    this->password = password;
    con = NULL;
}

// Destruktor
Bot::~Bot() {
    delete con;
}


void Bot::Logging(bool log)
{
    this->log = log;
}
void Bot::ClearLog()
{

}
string Bot::GetLog()
{

}
string Bot::GetLastSeen(string nickname)
{

}

void Bot::Nick(string nickname)
{
    con->Send("NICK " + nickname + "\r\n");
}
void Bot::User(string username)
{
    con->Send("USER " + username + " 0 0  :" + username + "\r\n");
}
void Bot::Join(string channel)
{
    con->SetChannel(channel);
}
void Bot::Leave(string channel)
{
    con->Send("PART #" + channel + "\r\n");
}
void Bot::ChangeTopic(string topic)
{
    con->Send("TOPIC #" + con->GetChannel() + " " + topic + "\r\n");
}
