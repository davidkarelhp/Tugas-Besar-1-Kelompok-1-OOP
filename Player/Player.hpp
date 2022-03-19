#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <string>
using namespace std;

class Player {
    private:
    string config;
    bool isConfigSet = false;
    void runConfig();
    public:
    Player();
    Player(string configPath);
    void setConfig(string configPath);
    const string getConfig();
    void play();
};

#endif