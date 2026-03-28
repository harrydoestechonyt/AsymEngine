#include "player.h"

void Player::init(Renderer& renderer){
    spriteId = renderer.loadSprite("romfs:/gfx/noob.t3x");
}

void Player::update(float dt){
    u32 kHeld = hidKeysHeld();
    bool moving = false;

    if (kHeld & KEY_LEFT)  { x -= speed; moving = true; facingRight = false; }
    if (kHeld & KEY_RIGHT) { x += speed; moving = true; facingRight = true;}
    if (kHeld & KEY_L) { speed = 4.0f; sprinting = true; } else {speed = 2.0f; sprinting = false; }

    if(moving)
        currentAnim.anim = !sprinting ? walkAnim : runAnim;
    else
        currentAnim.anim = idleAnim;


    currentAnim.update(dt);

    //vy += gravity;

    y += vy;

    if(y >= 200.0f){
        y = 200.0f;
        vy = 0.0f;
        isGrounded = true;
    }else
        isGrounded = false;
}

void Player::render(Renderer& renderer){
    renderer.setSpriteFrame(spriteId, currentAnim.getSheetIndex());
    renderer.setSpritePos(spriteId, x, y);
    renderer.setSpriteScale(spriteId, facingRight ? 1.0f : -1.0f, 1.0f);
}