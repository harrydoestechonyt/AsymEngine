#include "engine.h"

void Engine::init(){
    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();
    ndspInit();

    consoleInit(GFX_BOTTOM, nullptr);

    if (romfsInit() != 0)
        crash("romfsInit FAILED");
    else
        printf("romfsInit OK");


    renderer.init();
    audio.init();
    player.init(renderer);
}

void Engine::run(){
    while(aptMainLoop()){
        hidScanInput();
        u32 kDown = hidKeysDown();

        if(kDown & KEY_START) break;

        player.update();
        player.render(renderer);

        renderer.beginFrame();
        renderer.drawSprites();
        renderer.endFrame();
    }
}

void Engine::shutdown(){
    audio.shutdown();
    renderer.shutdown();

    ndspExit();
    C2D_Fini();
    C3D_Fini();
    gfxExit();
    romfsExit();
}

void Engine::crash(const char* reason){
    renderer.shutdown();
    audio.shutdown();

    gfxInitDefault();
    consoleInit(GFX_TOP, nullptr);

    printf("\x1b[44m");
    printf("\x1b[0;0H");

    for (int i = 0; i < 30; i++)
        printf("                                                  ");
    
    printf("\x1b[2;1HBOOTROM 8046");
    printf("\x1b[4;1HERRCODE: %s", reason);
    printf("\x1b[4;1HDon't worry, your 3DS is fine\nI thought it'd be funny to do this xD\n\nPress Any button to exit");

    while(aptMainLoop()){
        hidScanInput();
        u32 kDown = hidKeysDown()
        if(kDown) break;
        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }

    gfxExit();
    exit(1);
}