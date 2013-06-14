#include "Bot.h"

// Konstruktor
Bot::Bot(string nickname, string password) {
    this->nickname = nickname;
    this->password = password;
    con = NULL;
}

// Destruktor
Bot::~Bot() {
    delete con;
}
