#include "IRCBot.h"

namespace IRCLibrary {
    IRCBot::IRCBot() {
        ChatLogger::InitChatLogger("chatlog.sqlite");
        logging = false;
        IRCBot("XtremeBot", "halloaffe123");
    }
    IRCBot::IRCBot(string name, string password) {
        ChatLogger::InitChatLogger("chatlog.sqlite");
        logging = false;
        this->name = name;
        this->password = password;
        connector = NULL;
    }
    IRCBot::~IRCBot() {
        delete connector;
    }
    void IRCBot::Configure() {
        config = new ConfigLoader();
        cout << string(config->configData->host) << ":" << config->configData->port << ":" << string(config->configData->channel) << endl;
        ConnectToServer(string(config->configData->host), config->configData->port, string(config->configData->channel));
    }
    void IRCBot::Configure(string host, int port, string channel) {
        config = new ConfigLoader((char*)host.c_str(), port, (char*)channel.c_str());
        ConnectToServer(host, port, channel);
    }

    int IRCBot::ConnectToServer(string host, int port, string channel) {
        connector = new IRCConnector(host, port);
        if (!connector->Connect())
            return -1;
        connector->Login(name, name, password, channel);
        BotLoop();
        connector->Disconnect();
        return 0;
    }

    void IRCBot::BotLoop() {
        string message;
        while (true) {
            if (!connector->Receive(message))
                break;
            cout << message << endl;
            ParsePing(message);
            if (!PerformAction(message))
                break;
        }
    }

    string IRCBot::ParseName(string message) {
        size_t start    = message.find_first_of(":");
        size_t end      = message.find_first_of("!");
        return message.substr(start+1, end - start - 1);
    }
    string IRCBot::ParseMessage(string message) {
        return "TestMessage";
    }

    void IRCBot::ParsePing(string message) {
        size_t pos = message.find("PING");
        if (pos != string::npos) {
            string pong("PONG" + message.substr(pos + 4));
            cout << pong << endl;
            connector->Send(pong);
        }
    }
    /*
    bool IRCBot::PerformAction(string message) {

        if (logging) {
            LogMessage(message);
        }

        if (message.find("hallo") != string::npos) {
            connector->SendMessage("Hallo!");
        } if (message.find("-nick") != string::npos) {
            connector->SendMessage("HALLOOOO!!");
        } if (message.find("-join") != string::npos) {
            connector->SendMessage("HALLOOOO!!");
        } if (message.find("-part") != string::npos) {
            connector->SendMessage("HALLOOOO!!");
        } if (message.find("-topic") != string::npos) {
            connector->SendMessage("HALLOOOO!!");
        } if (message.find("-log") != string::npos) {
            connector->SendMessage("logged");
        } if (message.find("-show_log") != string::npos) {
            ShowChatLog();
        } if (message.find("-last_seen") != string::npos) {
            ShowLastSeen("TestUser");
        } if (message.find("-clear_log") != string::npos) {
            ClearChatLog();
            connector->SendMessage("Log cleared");
        } if (message.find("-logging_on") != string::npos) {
            SetLogging(true);
            connector->SendMessage("Logging on");
        } if (message.find("-logging_off") != string::npos) {
            SetLogging(false);
            connector->SendMessage("Logging off");
        } if (message.find("exit") != string::npos) {
            connector->SendMessage("CIAO!!!");
            return false;
        } return true;
    }
    */

    bool IRCBot::PerformAction(string buffer) {
        BufferParser data(buffer);
        //if(data.sender=="") return 0;
        int pos=0;

        if (logging) {
            stringstream msg;
            for(int i=0;i<(int)data.message.size();i++)
                msg << data.message[i] << " ";
            if (data.message.size() > 0)
                LogMessage(data.sender, msg.str());
        }

        if ((pos=data.atPosition("-o")) != -1 ) {
            //this->options();
            cout << "opt" << endl;
        } else if ((pos=data.atPosition("-log")) != -1 && (int)data.message.size() > pos+1 ) {
            if (data.message[pos+1] == "on" ) {
                logging = true;
                connector->SendMessage("Loggin enabled");
            } else if( data.message[pos+1] == "off" ) {
                logging = false;
                connector->SendMessage("Loggin disabled");
            }
        } else if((pos=data.atPosition("-showlog")) != -1 )
            ShowChatLog();
        else if ((pos=data.atPosition("-lastseen")) != -1 && data.message.size() > pos+1)
            ShowLastSeen(data.message[pos+1]);
        else if ((pos=data.atPosition("-exit")) != -1 ) {
            connector->SendMessage("PRIVMSG #" + connector->GetChannel() + " :CIAO!");
            connector->Send("QUIT Ciao...");
            return false;
        } else if( (pos=data.atPosition("-topic")) != -1 && (int)data.message.size() > pos+1 )
            ChangeTopic(data.message[pos+1]);
        else if( (pos=data.atPosition("-nick")) != -1 && (int)data.message.size() > pos+1 ) {
            SetNickname(data.message[pos+1]);
        } else if( (pos=data.atPosition("-join")) != -1 && (int)data.message.size() > pos+1 )
            JoinChannel( data.message[pos+1] );
        else if( (pos=data.atPosition("-leave")) != -1 && (int)data.message.size() > pos+1 )
            LeaveChannel( data.message[pos+1] );
        return true;
    }

    void IRCBot::SetNickname(string nickname) {
        connector->Send("NICK " + nickname);
    }
    void IRCBot::SetUsername(string username) {
        connector->Send("USER " + username + " 0 0  :" + username);
    }
    void IRCBot::JoinChannel(string channel) {
        connector->SetChannel(channel);
    }
    void IRCBot::LeaveChannel(string channel) {
        connector->Send("PART #" + channel);
    }
    void IRCBot::ChangeTopic(string topic) {
        connector->Send("TOPIC #" + connector->GetChannel() + " " + topic);
    }

    void IRCBot::SetLogging(bool logging) {
        this->logging = logging;
    }
    void IRCBot::LogMessage(string name, string message) {
        int t = time(0);
        //string name = ParseName(message);
        string msg = ParseMessage(message);
        stringstream date; date << t;
        ChatLogger::AddLog(date.str().c_str(), name.c_str(), connector->GetChannel().c_str(), msg.c_str());
    }
    void IRCBot::ClearChatLog() {
        ChatLogger::ClearLogTable();
    }
    void IRCBot::ShowChatLog() {
        string chatlog = ChatLogger::GetLog();
        if (!chatlog.empty())
            connector->SendMessage(chatlog);
        else
            connector->SendMessage("Empty Log...");
    }
    void IRCBot::ShowLastSeen(string name) {
        string date = ChatLogger::LastSeen(name.c_str());
        if (!date.empty())
            connector->SendMessage(date);
        else
            connector->SendMessage("sorry, never logged " + name);
    }
}
