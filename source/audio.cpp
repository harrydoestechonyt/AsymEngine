#include "audio.h"
#include <stdio.h>
#include <stdlib.h>

void Audio::init(){
    ndspSetOutputMode(NDSP_OUTPUT_STEREO);
    ndspChnSetInterp(AUDIO_CHANNEL, NDSP_INTERP_LINEAR);
    ndspChnSetRate(AUDIO_CHANNEL, 44100.0f);
    ndspChnSetFormat(AUDIO_CHANNEL, NDSP_FORMAT_STEREO_PCM16);
}

void Audio::playWAV(const char* path){
    FILE* f = fopen(path, "rb");
    if(!f) return;

    fseek(f, 44, SEEK_SET);
    fseek(f, 0, SEEK_END);
    long size = ftell(f) - 44;
    fseek(f, 44, SEEK_SET);

    u8* buf = (u8*)linearAlloc(size);
    if(!buf){ fclose(f); return; }
    fread(buf, 1, size, f);
    fclose(f);

    ndspWaveBuf waveBuf;
    std::memset(&waveBuf, 0, sizeof(waveBuf));
    waveBuf.data_vaddr = buf;
    waveBuf.nsamples = size / 4;
    waveBuf.looping = false;
    DSP_FlushDataCache(buf, size);

    ndspChnWaveBufAdd(AUDIO_CHANNEL, &waveBuf);
}

void Audio::shutdown(){
    // ndspExit(); - already called in Engine::shutdown :/
}