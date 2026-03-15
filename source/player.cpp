#include "player.h"

void Player::init(Renderer& renderer){
    spriteId = renderer.loadSprite("romfs:/gfx/smiley.t3x");
}

void Player::update(){
    u32 kHeld = hidKeysHeld();
    u32 kDown = hidKeysDown();

    if (kHeld & KEY_LEFT)   x -= speed;
    if (kHeld & KEY_RIGHT)   x += speed;

    if (kDown & KEY_A && isGrounded)
        vy = -4.0f;

    vy += gravity;

    y += vy;

    if(y >= 200.0f){
        y = 200.0f;
        vy = 0.0f;
        isGrounded = true;
    }else
        isGrounded = false;
}

void Player::render(Renderer& renderer){
    renderer.setSpritePos(spriteId, x, y);
}