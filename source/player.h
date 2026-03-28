#pragma once
#include <3ds.h>
#include "renderer.h"
#include "animation.h"

class Player {
    public:
        Player() {
            idleAnim.startFrame = 0;
            idleAnim.frameCount = 1;
            idleAnim.fps        = 4.0f;
            idleAnim.loop       = true;

            walkAnim.startFrame = 1;
            walkAnim.frameCount = 4;
            walkAnim.fps        = 8.0f;
            walkAnim.loop       = true;

            runAnim.startFrame = 4;
            runAnim.frameCount = 4;
            runAnim.fps = 8.0f;
            runAnim.loop = true;

            currentAnim.anim = idleAnim;
        }
        void init(Renderer& renderer);
        void update(float dt);
        void render(Renderer& renderer);
        bool isGrounded = false;
        bool alive = true;
        bool facingRight = true;
    private:
        float x = 200.0f, y = 120.0f;
        float speed = 2.0f;
        int spriteId = -1;
        float gravity = 0.2f;
        float vy = 0.0f;
        bool sprinting = false;

        AnimationState currentAnim;
        Animation idleAnim;
        Animation walkAnim;
        Animation runAnim;
};