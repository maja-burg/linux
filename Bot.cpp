#include "Bot.h"

// Konstruktor
Bot::Bot(string nickname, string password) {
    this->nickname = nickname;
    this->password = password;
    this->logging = false;
    this->sleeping = false;
    con = NULL;
    DBConnect::init("logdb.sqlite");
}

// Destruktor
Bot::~Bot() {
    delete con;
}

void Bot::mainLoop() {
    string message;
    for (;;) {
        if (!con->Receive(message))
            break;
        cout << message << endl;
        con->PingPong(message);
        if (!BotFunctions(message))
            break;
    }
}

void Bot::Logging(bool log)
{
    this->log = log;
}
void Bot::ClearLog()
{
    DBConnect::clearTable();
}
void Bot::AddLog(string name, string msg) {
    int t = time(0);
    //string name = ParseName(message);
    string msg = ParseMessage(message);
    stringstream date; date << t;
    ChatLogger::AddLog(date.str().c_str(), name.c_str(), connector->GetChannel().c_str(), msg.c_str());
}
void Bot::GetLog()
{
    string chatlog = DBConnect::getChatLog();
    if (!chatlog.empty())
        con->Send("PRIVMSG #" + con->GetChannel() + " :" + chatlog);
    else
        con->Send("PRIVMSG #" + con->GetChannel() + " :Kein Log vorhanden...");
}
void Bot::GetLastSeen(string nickname)
{
    string date = DBConnect::getLastSeen(name.c_str());
    if (!date.empty())
        con->Send("PRIVMSG #" + con->GetChannel() + " :" + date);
    else
        con->Send("PRIVMSG #" + con->GetChannel() " :" + name + " wurde noch nicht geloggt...");
}

int Bot::BotFunctions(string buffer)
{
    BufferParser data(buffer);
    int pos=0;

    if (logging) {
        stringstream msg;
        for(int i=0;i<(int)data.message.size();i++)
            msg << data.message[i] << " ";
        if (data.message.size() > 0)
            LogMessage(data.sender, msg.str());
    }


    if ((pos=data.atPosition("-log")) != -1 && (int)data.message.size() > pos+1 ) {
        if (data.message[pos+1] == "on" ) {
            logging = true;
            con->Send("PRIVMSG #" + con->GetChannel() + " :Logging enabled");
        } else if( data.message[pos+1] == "off" ) {
            logging = false;
            con->Send("PRIVMSG #" + con->GetChannel() + " :Logging disabled");
        }
    } else if( (pos=data.atPosition("-topic")) != -1 && (int)data.message.size() > pos+1 )
        ChangeTopic(data.message[pos+1]);
    else if( (pos=data.atPosition("-witz")) != -1) {
        con->Send("PRIVMSG #" + con->GetChannel() + "")
    else if( (pos=data.atPosition("-gute")) != -1 && (int)data.message.size() > pos+1) {
        if (data.message[pos+1] == "nacht" ) {
            sleeping = true;
            con->Send("PRIVMSG #" + con->GetChannel() + " :Gute Nacht!");
        con->Send("PRIVMSG #" + con->GetChannel() + "")
    else if( (pos=data.atPosition("-nick")) != -1 && (int)data.message.size() > pos+1 ) {
        SetNickname(data.message[pos+1]);
    } else if( (pos=data.atPosition("-join")) != -1 && (int)data.message.size() > pos+1 )
        JoinChannel( data.message[pos+1] );
    else if( (pos=data.atPosition("-leave")) != -1 && (int)data.message.size() > pos+1 )
        LeaveChannel( data.message[pos+1] );
    else if((pos=data.atPosition("-show_log")) != -1 )
        GetLog();
    else if ((pos=data.atPosition("-last_seen")) != -1 && data.message.size() > pos+1)
        ShowLastSeen(data.message[pos+1]);
    else if ((pos=data.atPosition("-exit")) != -1 ) {
        con->Send("PRIVMSG #" + con->GetChannel() + " :BYE BYE!");
        con->Send("QUIT bye");
        return false;
    } return true;
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

void Bot::InitBotWitze() {
    bot_witze.push_back("Chuck Norris weiß, wieso da überall Stroh liegt!");
    bot_witze.push_back("Chuck Norris kann Drehtüren zuschlagen!");
    bot_witze.push_back("Chuck Norris hat bis unendlich gezählt. Zweimal.");
    bot_witze.push_back("Chuck Norris isst keinen Honig, er kaut Bienen.");
    bot_witze.push_back("Chuck Norris kann Zwiebeln zum Weinen bringen.");
}
string Bot::GetRandomWitz() {
    int index = (int)(rand() % bot_witze.size());
    return bot_witze[index];
}
