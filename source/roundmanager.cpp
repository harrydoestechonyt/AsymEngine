#include <3ds.h>
#include "roundmanager.h"
#include "engine.h"

// just a stub for now

void RoundManager::init(Audio& audio, Renderer& rend){
    rend.loadBackground("romfs:/gfx/lobby.t3x");
    timer = 0;
    audioSource = audio;
}

void RoundManager::beginRound(Audio& audio){
    audio.stopAll();
    state = RoundState::PREROUND;
    timerState = "Round begins in: ";
    timer = 45;
    audio.playWAV("romfs:/audio/lobby.wav");
}

void RoundManager::update(float dT, Renderer& rend, Player& plr){
    if(DEBUGMODE) printf("dt: %.4f timer: %.2f\n", dT, timer);
    if(!timerPause) timer -= dT;

    if(timer < 0) timer = 0;

    if(timer <= 0 ){
        switch (state)
        {
        case RoundState::PREROUND :
            timer = 180;
            state = RoundState::INROUND;
            timerState = "Round ends in: ";
            audioSource.stopAll();
            break;
        case RoundState::INROUND:
            rend.loadBackground("romfs:/gfx/lobby.t3x");
            beginRound(audioSource);
            break;
        case RoundState::LMS:
            if(plr.alive) printf("%s won!", miiname);
            beginRound(audioSource);
            break;
        default:
            break;
        }
    }

    if(plr.alive && state != RoundState::LMS && state != RoundState::PREROUND){
        int alive = 0;
        for(int i = 0; i < (sizeof(npcs) / sizeof(npcs[0])); i++){
            if(npcs[i].alive){
                alive++;
            }
        }

        if(alive == 0){
            state = RoundState::LMS;
            timerPause = true;
            timer = 70.426;
            timerPause = false;
            audioSource.playWAV("romfs:/audio/lms.wav");
        }
    }

    char buffer[64];
    sprintf(buffer, "%s %d", timerState, (int)timer);

    rend.drawText(buffer, 10, 10);
}