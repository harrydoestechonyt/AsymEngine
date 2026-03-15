#pragma once
#include <3ds.h>
#include "renderer.h"

class Player {
    public:
        void init(Renderer& renderer);
        void update();
        void render(Renderer& renderer);
        bool isGrounded = false;
    private:
        float x = 200.0f;
        float y = 200.0f;
        float speed = 2.0f;
        int spriteId = -1;
        float gravity = 0.2f;
        float vy = 0.0f;
};