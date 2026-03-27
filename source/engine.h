#pragma once
#include <3ds.h>
#include <citro2d.h>
#include "renderer.h"
#include "audio.h"
#include <stdio.h>
#include <stdlib.h>
#include "player.h"

#define DEBUGMODE false

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
    private:
        // placeholder

};