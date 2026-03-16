#pragma once
#include <citro2d.h>

struct Animation
{
    int startFrame = 0;
    int frameCount = 0;
    float fps = 8.0f;
    bool loop = true;
};

struct AnimationState
{
    Animation anim;
    int currentFrame = 0;
    float timer = 0.0f;

    void update(float dt){
        timer += dt;
        if (timer >= 1.0f / anim.fps){
            timer = 0.0f;
            currentFrame++;
            if(currentFrame >= anim.frameCount)
                currentFrame = anim.loop ? 0 : anim.frameCount - 1;
        }
    }

    int getSheetIndex() { return anim.startFrame + currentFrame; }
};
