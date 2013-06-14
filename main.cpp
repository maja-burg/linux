#include "IRCBot.h"

using namespace IRCLibrary;

int main(int argc, char **argv) {
    IRCBot *ircBot = new IRCBot("XtremeBot", "halloaffe123");

    switch (argc) {
    case 1:
        ircBot->Configure();
        break;
    case 4:
        ircBot->Configure(argv[1], atoi(argv[2]), argv[3]);
        break;
    default:
        perror("Unzulaessige Anzahl an Parameter");
        exit(1);
        break;
    };
    delete ircBot;
    return 0;
}
