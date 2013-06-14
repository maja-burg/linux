#include "ConfigLoader.h"

ConfigLoader::ConfigLoader() {
    SetConfigFile();
}
ConfigLoader::ConfigLoader(char* host, int port, char* channel) {
    SetConfigFile(host, port, channel);
}
ConfigLoader::~ConfigLoader() {
    delete configData;
}
void ConfigLoader::SetConfigFile() {
    const char* FILENAME = "config.cfg";

    FILE* file = fopen(FILENAME, "r");
    if (file == NULL)
        return;
    // get file length
    fseek(file, 0, SEEK_END);
    unsigned long length = ftell(file);
    rewind(file);
    // allocate memorys
    char* buffer = (char*) malloc (sizeof(char)*length);
    if (buffer == NULL) {
        fclose(file);
        return;
    }
    // load file into memory
    unsigned long result = fread(buffer, 1, length, file);
    string configFile = string(buffer, 0, result);
    fclose(file);
    free(buffer);

    // Falls Config nicht vorhanden, erstelle Config:
    if (configFile.find("host") == string::npos ||
        configFile.find("port") == string::npos ||
        configFile.find("channel") == string::npos) {
        stringstream sstr;
        sstr << "host:irc.freenode.net\nport:6667\nchannel:XtremeChannel\n";
        file = fopen(FILENAME, "w");
        if (file == NULL)
            return;
        fputs(sstr.str().c_str(), file);
        fclose(file);
        strcpy(configData->host, "irc.freenode.net");
        configData->port = 6667;
        strcpy(configData->channel, "XtremeChannel");

    } else {
        size_t pos1 = configFile.find("host:")+5;
        size_t pos2 = configFile.find("\n")+1;
        string sHost = configFile.substr(pos1, pos2-pos1-1);
        pos1 = configFile.find("port:")+5;
        pos2 = configFile.find("\n", pos1);
        int sPort = atoi(configFile.substr(pos1, pos2-pos1).c_str());
        pos1 = configFile.find("channel:")+8;
        pos2 = configFile.find("\n", pos1);
        string sChannel = configFile.substr(pos1, pos2-pos1);
        strcpy(configData->host, sHost.c_str());
        configData->port = sPort;
        strcpy(configData->channel, sChannel.c_str());
    } cout << "CONFIGURE()" << configData->host << ":" << configData->port << ":" << configData->channel<< endl;
}
void ConfigLoader::SetConfigFile(char* host, int port, char* channel) {
        const char* FILENAME = "config.cfg";
        FILE *file = fopen(FILENAME, "w");
        if (file == NULL)
            return;
        stringstream sstr;
        if (port != 0)
            sstr << "host:" << host << "\n" << "port:" << port << "\n" << "channel:" << channel << "\n";
        fputs(sstr.str().c_str(), file);
        fclose(file);
        cout << "CONFIGURE(shit)" << endl;
}
