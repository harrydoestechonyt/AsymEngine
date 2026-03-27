#include "audio.h"
#include <stdio.h>
#include <stdlib.h>
#include "engine.h"

void Audio::init(){
    if(DEBUGMODE) printf("\n[Audio] Initialising...");
    ndspChnReset(AUDIO_CHANNEL);
    ndspSetOutputMode(NDSP_OUTPUT_STEREO);
    ndspChnSetInterp(AUDIO_CHANNEL, NDSP_INTERP_LINEAR);
    ndspChnSetRate(AUDIO_CHANNEL, 48000.0f);
    ndspChnSetFormat(AUDIO_CHANNEL, NDSP_FORMAT_STEREO_PCM16);
    if(DEBUGMODE) printf("\n[Audio] Init OK");
}

void Audio::playWAV(const char* path)
{
    if(DEBUGMODE) printf("\n[Audio] Opening %s", path);
    FILE* f = fopen(path, "rb");
    if (!f) { printf("\n[Audio] ERROR: Failed to open file!"); return; }
    if(DEBUGMODE) printf("\n[Audio] File opened OK");

    fseek(f, 0, SEEK_END);
    long totalSize = ftell(f);
    long size = totalSize - 44;
    fseek(f, 44, SEEK_SET);
    if(DEBUGMODE) printf("\n[Audio] File size: %ld bytes, audio data: %ld bytes", totalSize, size);

    if (size <= 0) { printf("\n[Audio] ERROR: Invalid file size!"); fclose(f); return; }

    if (buf) { if(DEBUGMODE) printf("\n[Audio] Freeing old buffer"); linearFree(buf); }
    buf = (u8*)linearAlloc(size);
    if (!buf) { printf("\n[Audio] ERROR: linearAlloc failed! (size=%ld)", size); fclose(f); return; }
    if(DEBUGMODE) printf("\n[Audio] Buffer allocated OK");

    size_t read = fread(buf, 1, size, f);
    fclose(f);
    if(DEBUGMODE) printf("\n[Audio] Read %zu bytes", read);

    memset(&waveBuf, 0, sizeof(waveBuf));
    waveBuf.data_vaddr = buf;
    waveBuf.nsamples   = size / 4;
    waveBuf.looping    = true;
    DSP_FlushDataCache(buf, size);
    if(DEBUGMODE) printf("\n[Audio] nsamples: %ld", size / 4);

    ndspChnWaveBufAdd(AUDIO_CHANNEL, &waveBuf);
    if(DEBUGMODE) printf("\n[Audio] WaveBuf submitted to NDSP");
}

void Audio::shutdown(){
    if(DEBUGMODE) printf("\n[Audio] Shutting down");
    if (buf) linearFree(buf);
}