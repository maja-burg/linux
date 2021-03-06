#ifndef CHATLOGGER_H
#define CHATLOGGER_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <sstream>
#include <time.h>

#include <sqlite3.h>

using namespace std;

class ChatLogger {
public:
    static sqlite3      *database;
    static const char   *path;

    static void     InitChatLogger(const char *path);

    static void     OpenLog();
    static void     CloseLog();
    static void     CreateLogTable();
    static void     DropLogTable();
    static void     ClearLogTable();

    static void         AddLog(const char *date, const char *name, const char *channel, const char *log);
    static string       LastSeen(const char *name);
    static string       GetLog();

private:

};

#endif
