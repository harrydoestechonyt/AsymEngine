#include "renderer.h"

void Renderer::init(){
    topScreen = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    g_textbuf = C2D_TextBufNew(4096);
}

int Renderer::loadSprite(const char* path){
    sheet = C2D_SpriteSheetLoad(path);
    if(!sheet) return -1;

    for(int i = 0; i < MAX_SPRITES; i++){
        if(!sprites[i].active){
            C2D_SpriteFromSheet(&sprites[i].spr, sheet, 0);
            C2D_SpriteSetCenter(&sprites[i].spr, 0.5f, 0.5f);
            C2D_SpriteSetPos(&sprites[i].spr, 200.0f, 120.0f);
            sprites[i].active = true;
            return i;
        }
    }
    return -1;
}

void Renderer::setSpritePos(int id, float x, float y){
    if (id >= 0 && id < MAX_SPRITES && sprites[id].active)
        C2D_SpriteSetPos(&sprites[id].spr, x, y);
}

void Renderer::setSpriteFrame(int id, int frameIndex){
    if (id < 0 || id >= MAX_SPRITES || !sprites[id].active) return;
    C2D_SpriteFromSheet(&sprites[id].spr, sheet, frameIndex);
}

void Renderer::beginFrame(){
    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
    C2D_TargetClear(topScreen, C2D_Color32(0, 0, 0, 255));
    C2D_SceneBegin(topScreen);
    C2D_TextBufClear(g_textbuf);
}

void Renderer::drawSprites(){
    for (int i = 0; i < MAX_SPRITES; i++)
        if(sprites[i].active)
            C2D_DrawSprite(&sprites[i].spr);
}

void Renderer::endFrame(){
    C3D_FrameEnd(0);
}

void Renderer::shutdown(){
    C2D_SpriteSheetFree(sheet);
    C2D_TextBufDelete(g_textbuf);
}

void Renderer::drawText(const char* txt, float x, float y){
    C2D_Text g_text;

    C2D_TextParse(&g_text, g_textbuf, txt);

    C2D_DrawText(&g_text, C2D_WithColor, x, y, 0.0f, 1.0f, 1.0f, C2D_Color32(255, 255, 255, 255));
}