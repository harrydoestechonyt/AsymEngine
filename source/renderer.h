#pragma once
#include <citro2d.h>
#include <3ds.h>

#define SCREEN_TOP_WIDTH 400
#define SCREEN_TOP_HEIGHT 240
#define MAX_SPRITES 128

struct Sprite
{
    C2D_Sprite spr;
    bool active = false;
    int sheetIndex = 0;
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
        int loadBackground(const char* path);
        void setSpritePos(int id, float x, float y);
        void setSpriteFrame(int id, int frameIndex);
        void drawText(const char* txt, float x, float y);
        void setSpriteScale(int id, float sX, float sY);
    private:
        C3D_RenderTarget* topScreen;
        C2D_SpriteSheet sheet;
        Sprite sprites[MAX_SPRITES];
        C2D_TextBuf g_textbuf;
        C2D_SpriteSheet bgSheet = nullptr;
        C2D_Image bgImage;
        bool hasBg = false;
};
