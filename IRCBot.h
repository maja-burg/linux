#ifndef IRCBOT_H
#define IRCBOT_H

#include "IRCConnector.h"
#include "ChatLogger.h"
#include "BufferParser.h"
#include "ConfigLoader.h"

namespace IRCLibrary {

    class IRCBot {
    public:
        IRCBot();
        IRCBot(string name, string password);
        ~IRCBot();

        void    Configure();
        void    Configure(string host, int port, string channel);
        int     ConnectToServer(string host, int port, string channel);
    private:
        string  name;
        string  password;

        bool logging;

        IRCConnector    *connector;
        ConfigLoader    *config;

        void    BotLoop();

        string  ParseName(string message);
        string  ParseMessage(string message);
        void    ParsePing(string message);
        bool    PerformAction(string message);

        // bot functions
        void    SetNickname(string nickname);
        void    SetUsername(string username);
        void    JoinChannel(string channel);
        void    LeaveChannel(string channel);
        void    ChangeTopic(string topic);

        // chat logging system
        void    SetLogging(bool logging);
        void    LogMessage(string name, string message);
        void    ClearChatLog();
        void    ShowChatLog();
        void    ShowLastSeen(string name);
    };

}
#endif
