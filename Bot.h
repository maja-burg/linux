#include <sqlite3.h>
#include <vector>
#include <algorithm>
#include <sstream>
#include "Connection.h"

class Bot {
public:
    Bot(string nickname, string password);
    ~Bot();


private:
    Connection  *con;

    string      nickname;
    string      password;



};
