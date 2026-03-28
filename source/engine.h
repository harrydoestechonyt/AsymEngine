#pragma once
#include <3ds.h>
#include <citro2d.h>
#include "renderer.h"
#include "audio.h"
#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "roundmanager.h"

#define DEBUGMODE false

extern char miiname[36];

class Engine
{
    public: 
        void init();
        void run();
        void shutdown();
        void crash(const char* reason);
        Renderer renderer;
        Audio audio;
        Player player;
        RoundManager round;
    private:
        // placeholder

};