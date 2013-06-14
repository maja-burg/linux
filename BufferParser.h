#ifndef BUFFERPARSER_H
#define BUFFERPARSER_H

#include <stdio.h>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>

using namespace std;

namespace IRCLibrary {

    class BufferParser {
    public:
        BufferParser(string buffer);
        ~BufferParser();

        string sender;
        vector<string> message;

        int atPosition(string msgVar);
    };

}
#endif
