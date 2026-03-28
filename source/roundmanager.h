#pragma once
#include <3ds.h>
#include "renderer.h"
#include "audio.h"
#include "player.h"

struct aiPlayers {
    char* name;
    bool alive = false;
    char* characterName;
};

enum RoundState{
    PREROUND,
    INROUND,
    LMS
};

class RoundManager
{
    public:
        void init(Audio& audio, Renderer& rend);
        void beginRound(Audio& audio);
        void update(float dT, Renderer& rend, Player& plr);
        float timer = 0;
        bool timerPause = false;
        aiPlayers npcs[7];
        const char* timerState = "Round begins in: ";
        RoundState state;
        Audio audioSource;
    private:


};