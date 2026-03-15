#pragma once
#include <citro2d.h>
#include <3ds.h>

#define SCREEN_TOP_WIDTH 400
#define SCREEN_TOP_HEIGHT 400
#define MAX_SPRITES 128

struct Sprite
{
    C2D_Sprite spr;
    bool active = false;
};

class Renderer
{
    public:
        void init();
        void beginFrame();
        void drawSprites();
        void endFrame();
        void shutdown();

        int loadSprite(const char* path);
        void setSpritePos(int id, float x, float y);
    private:
        C3D_RenderTarget* topScreen;
        C2D_SpriteSheet sheet;
        Sprite sprites[MAX_SPRITES];
};
