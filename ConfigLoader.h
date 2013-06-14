#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H

#include <stdio.h>
#include <string>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <fstream>
#include <sstream>

using namespace std;

class ConfigData {
    public:
        ConfigData() {}
        ConfigData(char* host,int port,char* channel) {
            strcpy(this->host, host);
            this->port = port;
            strcpy(this->channel, channel);
        }

        char host[100];
        int port;
        char channel[100];
};
class ConfigLoader {
    public:
        ConfigLoader();
        ConfigLoader(char* host, int port, char* channel);
        ~ConfigLoader();

        ConfigData* configData;

        void SetConfigFile();
        void SetConfigFile(char* host, int port, char* channel);
};

#endif
