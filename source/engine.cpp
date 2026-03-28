#include "engine.h"

bool accountSelected = false;
char miiname[36];

void miiSelect(void){
    static MiiSelectorConf msConf;
    static MiiSelectorReturn msRet;

    miiSelectorInit(&msConf);
    miiSelectorSetTitle(&msConf, "Select an account");
    miiSelectorSetOptions(&msConf, MIISELECTOR_GUESTS|MIISELECTOR_TOP|MIISELECTOR_GUESTSTART);
    miiSelectorBlacklistUserMii(&msConf, 0);
	miiSelectorLaunch(&msConf, &msRet);

    if(miiSelectorChecksumIsValid(&msRet)){
        if(!msRet.no_mii_selected){
            accountSelected = true;
            miiSelectorReturnGetName(&msRet, miiname, sizeof(miiname));
        }
    }
}

void Engine::init(){
    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();
    

    if(ndspInit() != 0)
        crash("nsdpInit failed! - no dsp firmware?");
    else
        if(DEBUGMODE) printf("nsdpInit - OK");

    consoleInit(GFX_BOTTOM, nullptr);

    if (romfsInit() != 0)
        crash("romfsInit FAILED");
    else
        if(DEBUGMODE) printf("romfsInit OK");


    renderer.init();
    audio.init();
    player.init(renderer);
}

void Engine::run(){
    u64 lastTime = osGetTime();

    //audio.playWAV("romfs:/audio/lms.wav");
    //if(DEBUGMODE) printf("\nPlaying Eternal Hope, Eternal Fight");
    // yeah fuck you i dont need you anymore

    audio.playWAV("romfs:/audio/menu.wav");

    bool inGame = false;

    while(!accountSelected){
        miiSelect();
    }

    printf("\nWelcome, %s", miiname);
    printf("\nMENU\n");
    printf("X - Start\n");
    printf("Y - Settings\n");
    printf("A - Change account\n");

    while(aptMainLoop()){
        hidScanInput();
        u32 kDown = hidKeysDown();
        if(inGame){
            u64 now = osGetTime();
            float dt = (now - lastTime) / 1000.0f;
            lastTime = now;

            if(kDown & KEY_START) break;

            player.update(dt);
            
            renderer.beginFrame();
            player.render(renderer);
            renderer.drawSprites();
            round.update(dt, renderer, player);
            renderer.endFrame();
        }else{
            if(kDown & KEY_X){
                audio.stopAll();
                inGame = true;
                lastTime = osGetTime();
                consoleClear();
                round.init(audio, renderer);
                round.beginRound(audio);
            }

            //i dont fucking know what to do for the other options
        }
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
    printf("\x1b[6;1HDon't worry, your 3DS is fine\nI thought it'd be funny to do this xD\n\nPress Any button to exit");

    while(aptMainLoop()){
        hidScanInput();
        u32 kDown = hidKeysDown();
        if(kDown) break;
        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }

    romfsExit();
    gfxExit();
    exit(1);
}