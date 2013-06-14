g++ -c ChatLogger.cpp -lsqlite3;
g++ -c IRCConnector.cpp;
g++ -c IRCBot.cpp;
g++ -lsqlite3 main.cpp -o main ChatLogger.o IRCConnector.o IRCBot.o;
