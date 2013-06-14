#include <sqlite3.h>
#include <vector>
#include <algorithm>
#include <sstream>
#include "Connection.h"
#include "DBConnect.h"

class Bot {
public:
    Bot(string nickname, string password);
    ~Bot();

    void     mainLoop();
private:
    Connection  *con;

    string      nickname;
    string      password;
    bool        log;

    void    Logging(bool log);
    void    ClearLog();
    string  GetLog();
    string  GetLastSeen(string nickname);

    void    Nick(string nickname);
    void    User(string username);
    void    Join(string channel);
    void    Leave(string channel);
    void    ChangeTopic(string topic);


};
