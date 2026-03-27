#pragma once
#include <3ds.h>
#include "renderer.h"

struct aiPlayers {
    char* name;
    bool alive = true;
    char* characterName;
};

class RoundManager
{
    public:
        void init();
        void beginRound();
        void update(float dT, Renderer& rend);
        float timer = 0;
        bool timerPause = false;
        aiPlayers npcs[7];
        char* timerState = "Round begins in: ";
    private:

};