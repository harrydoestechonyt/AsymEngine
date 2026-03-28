#pragma once
#include <3ds.h>
#include <cstring>

#define AUDIO_CHANNEL 0

class Audio
{
    public:
        void init();
        void playWAV(const char* path);
        void shutdown();
        void stopAll();
    private:
        ndspWaveBuf waveBuf;
        u8* buf = nullptr;
};