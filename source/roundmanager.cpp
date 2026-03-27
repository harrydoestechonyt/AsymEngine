#include <3ds.h>
#include "roundmanager.h"
#include "engine.h"

// just a stub for now

void RoundManager::init(){
    timer = 0;
}

void RoundManager::beginRound(){
    timerState = "Round begins in: ";
    timer = 45;

    while(timer > 0); // should wait i think i hope i pray

    timerPause = true;
    timerState = "Round ends in: ";
    timer = 180;

    while(timer > 0);

    beginRound();
}

void RoundManager::update(float dT, Renderer& rend){
    if(DEBUGMODE) printf("dt: %.4f timer: %.2f\n", dT, timer);
    if(!timerPause) timer -= dT;

    if(timer < 0) timer = 0;

    char buffer[64];
    sprintf(buffer, "%s %d", timerState, (int)timer);

    rend.drawText(buffer, 10, 10);
}