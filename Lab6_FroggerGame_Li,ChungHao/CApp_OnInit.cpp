//==============================================================================
#include "CApp.h"

//==============================================================================
bool CApp::OnInit()
{

    int i;

    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK)<0)
    {
        return false;
    }

	//TTF Initialization
    TTF_Init( );	

    //Loads font with font size
    font = TTF_OpenFont("Rush.ttf", 10);
    color = {255,255,255};

    font1 = TTF_OpenFont("three.ttf", 50);
    color1 = {255,245,209};

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        Running = false;
    }

    //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        Running = false;
    }

    //Plays Music in Background while GAMEPLAY
    loadMedia();
    Mix_PlayMusic( gMusic, -1 );

    window = SDL_CreateWindow("Go! Go! Frogger!! Make your way to the pond!",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              WINDOW_WIDTH, WINDOW_HEIGHT,
                              SDL_WINDOW_SHOWN);
    if (!window)
        return false;
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
        return false;

    srand(time(NULL));

    //vehichles
    //car lane1 toward left
    int locations1[] = { 15,135,199,580,920 };
    for (i = 0; i < 5; ++i) {
        strncpy_s(car[i].imagename,"vehicle_1.bmp",255);
        car[i].loadPlayer(renderer);
        
        car[i].position.x = locations1[i] + rand() % 25;
        car[i].position.y = 0.59 * (window_h);
        car[i].velocity.x = -3.5;
        car[i].velocity.y = 0;//rand() % 1 + 1;
    }
    //car lane1 toward right
    int locations2[] = { 20,100,210,399,500,810 };
    for (i = 5; i < 11; ++i) {
        strncpy_s(car[i].imagename, "vehicle_2.bmp", 255);
        car[i].loadPlayer(renderer);
        car[i].position.x = locations2[i-5] +rand()%10 ;
        car[i].position.y = 0.67 * (window_h);;
        car[i].velocity.x = 3;
        car[i].velocity.y = 0;
    }
    //car lane3 toward left
    int locations3[] = { 50,200,445,580,690,870 };
    for (i =11; i < 16 ; ++i) {
        strncpy_s(car[i].imagename, "vehicle_3.bmp", 255);
        car[i].loadPlayer(renderer);
        car[i].position.x = locations3[i-11] + rand() % 10;
        car[i].position.y = 0.79 * (window_h);;
        car[i].velocity.x = -1;
        car[i].velocity.y = 0;
    }
    
    //logs
    for (i = 12; i < 16; ++i) {
        strncpy_s(log[i].imagename, "log.bmp", 255);
        log[i].loadPlayer(renderer);
        log[i].position.x = rand() % (window_w);
        log[i].position.y = 0.155 * window_h + 5;
        log[i].velocity.x = -(rand() % 1 + 1);
        log[i].velocity.y = 0;
    }
    for (i = 8; i < 12; ++i) {
        strncpy_s(log[i].imagename, "log.bmp", 255);
        log[i].loadPlayer(renderer);
        log[i].position.x = rand() % (window_w);
        log[i].position.y = 0.155 * window_h + 62;
        log[i].velocity.x = -(rand() % 1 + 1);
        log[i].velocity.y = 0;
    }
    for (i = 4; i < 8; ++i) {
        strncpy_s(log[i].imagename, "log.bmp", 255);
        log[i].loadPlayer(renderer);
        log[i].position.x = rand() % (window_w);
        log[i].position.y = 0.155 * window_h + 121;
        log[i].velocity.x = -(rand() % 1 + 1);
        log[i].velocity.y = 0;
    }
    for (i = 0; i < 4; ++i) {
        strncpy_s(log[i].imagename, "log.bmp", 255);
        log[i].loadPlayer(renderer);
        log[i].position.x =rand()%(window_w);
        int logs[] = {55, 117, 175, 235 };
        log[i].position.y = 0.155 * window_h + 180;
        log[i].velocity.x = -(rand() % 1 + 1);
        log[i].velocity.y = 0;
        strncpy_s(line[i].imagename, "line.bmp", 255);

        //developping needs, to mark the lines
        //line[i].loadPlayer(renderer);
        //line[i].position.y = logs[i]+110;
        //line[i].velocity.x = window_w/2;
    }
    

    frog.position.x = (WINDOW_WIDTH / 2) - frog.position.w / 2; //put the frog in the middle
    frog.position.y = 0.85 * window_h;
    
    strncpy_s(frog.imagename, "frog.bmp", 255);
    frog.loadPlayer(renderer);
    // Press 'p' to reset lives and score value to default.
    live = 0010;
    score = 0000;

    top.position.x = -5 ; //put the frog in the middle
    top.position.y = -2;
    strncpy_s(top.imagename, "top.bmp", 255); //top green platform part
    top.loadPlayer(renderer);
    //Background IMAGE DECLARATION
    strncpy_s(background.imagename,"background.bmp",255);
    background.loadPlayer(renderer);
    background.set_scroll_loc(0,0,window_w,CONSOLE_START_Y);
    background.move();
    return true;

}

//==============================================================================
