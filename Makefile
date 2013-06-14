all:
	g++ -c ChatLogger.cpp;
	g++ -c IRCConnector.cpp;
	g++ -c BufferParser.cpp;	
	g++ -c ConfigLoader.cpp;
	g++ -c IRCBot.cpp;
	g++ main.cpp -o main ChatLogger.o IRCConnector.o BufferParser.o ConfigLoader.o IRCBot.o -lsqlite3;
