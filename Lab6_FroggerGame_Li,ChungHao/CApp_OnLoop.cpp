//==============================================================================
#include "CApp.h"

using namespace std;

void
CApp::MoveSprites()
{
    int i;
    bool onWoodAlready = false; //so not repeatedly move the car while the frog touches multiple logs
    bool onWood = false; //is it on the log or in the river?
    
    //move cars on different lanes
    for (i = 0; i < NUM_SPRITES / 3; ++i) {
        car[i].moveLlane1();
    }
    for (i = NUM_SPRITES / 3; i < NUM_SPRITES * 2 / 3; ++i) {
        car[i].moveR();
    }
    for (i = NUM_SPRITES * 2 / 3; i < NUM_SPRITES; ++i) {
        car[i].moveLlane2();
    }

    //move logs on different lanes
    for (i = 0; i < 4; ++i) {
        log[i].moveLog1();
        
        //line[i].display(renderer); //developping needs
    }
    for (i = 4; i < 8; ++i) {
        log[i].moveLog2();
    }
    for (i = 8; i < 12; ++i) {
        log[i].moveLog3();
    }
    for (i = 12; i < 16; ++i) {
        log[i].moveLog4();
    }

    //draw cars/logs/frog and check collision
    for (i = 0; i < NUM_SPRITES; ++i)
    {              
        log[i].display(renderer);
        car[i].display(renderer);
        top.display(renderer);
        frog.display(renderer);
        
        if (check_collision(car[i].position, frog.position)== true)
        {
            loadMedia();
            Mix_PlayChannel( -1, gScratch, 0 );
            car[i].position.y = -200;							
            car[i].position.x = rand()% window_w; 	
            gameOver = true;//hit the car>> lose	
        }
        if (frog.position.y < 110) //Successfully cross the river but hit the green platform>> Lose
        {
            if ((gameOver == false && gameWin == false) &&((frog.position.x > 115 && frog.position.x < 300) ||
                (frog.position.x > 350 && frog.position.x < 535) ||
                (frog.position.x > 585 && frog.position.x < 770) ||
                (frog.position.x > 820 && frog.position.x < 1005) ||
                (frog.position.x > 0 && frog.position.x < 65)))
            {
                gameOver = true;
                gameWin = false;
                score = 0;
            }
            else if(gameOver==false&&gameWin==false) { //not hitting the green platform >> WIN!!
                gameWin = true;
                gameOver = false;
            }
        }
        
        if (check_collision(log[i].position, frog.position) == true)
        {
            onWood = true;

            if (!onWoodAlready)
            {

                if (i>=0 && i<4)
                {
                    frog.moveLog1();
                    onWoodAlready = true;
                }
                if (i >= 4 && i < 8)
                {
                    frog.moveLog2();
                    onWoodAlready = true;
                }
                if (i >= 8 && i < 12)
                {
                    frog.moveLog3();
                    onWoodAlready = true;
                }
                if (i >= 12 && i < 16)
                {
                    frog.moveLog4();
                    onWoodAlready = true;
                }
            }
        }

        //score system>> just like American football, once player pushes some yards forward
        // he/she gets points
        if (frog.position.y <= 0.16 * window_h)
        {
            score = 80;
        }
        else if (frog.position.y <= 0.2 * window_h)
        {
            score = 30;													
        }
        else if (frog.position.y <= 0.35 * window_h)
        {
            score = 25;													
        }
        else if (frog.position.y <= 0.5 * window_h)
        {
            score = 15;													
        }
        else if (frog.position.y <= 0.65 * window_h)
        {
            score = 10;													
        }
        else if (frog.position.y <= 0.75 * window_h)
        {
            score = 5;													
        }
        else if (frog.position.y <= 0.8 * window_h)
        {
            score = 3;
        }
        printf(" SCORE: %d     \r",  score);
    }
    if ((gameWin==false)&&(((frog.position.y < 345 && frog.position.y > 110)&& onWood == false)|| frog.position.x>=(window_w- frog.position.w)|| frog.position.x<=0))
    {
        //frogger misses a log and falls into the water;  hits any of the two sides (right or left)
        gameOver = true;
    }
}



//==============================================================================
void CApp::OnLoop()
{
    SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF); //black bg
    SDL_RenderClear(renderer);

    background.move();
    background.display(renderer);
    MoveSprites();
   
    displayGameStats(25, 25, "Score   : %3d", score);

    if (gameOver)
    {
        background.velocity.x=0;
        for (int i = 0; i < NUM_SPRITES; ++i)
        {
			car[i].velocity.y = 0;					// Set the velocity of the car sprites to zero
			car[i].position.y = -500;				// Set the position of the arrow sprites to -500 
            log[i].velocity.y = 0;					// Set the velocity of the arrow sprites to zero
            log[i].position.y = -500;				// so that it goes out of scope
        }  
                
        displayGameOver(window_w/2, window_h/2, "GAME OVER");
        displayGameStats(window_w/2, window_h/2 + 60, "Press 'P' to Play Again",NULL);
        displayGameStats(window_w/2, window_h/2 + 100, "Press 'ESC' to EXIT",NULL);
        Mix_FreeMusic( gMusic );
        gMusic = NULL;
    }
    if (gameWin) {
        background.velocity.x = 0;
        for (int i = 0; i < NUM_SPRITES; ++i)
        {
            // Set the velocity of all cars/logs to zero and move them out of the screen
            car[i].velocity.y = 0;
            car[i].position.y = -500;
            log[i].velocity.y = 0;
            log[i].position.y = -500;
        }
        //Load the winning sound effect
        loadMedia();
        Mix_PlayChannel(-1, gScratch1, 1);
        displayGameOver(window_w / 2, window_h / 2, "GAME WIN");
        displayGameStats(window_w / 2, window_h / 2 + 60, "Press 'P' to Play Again", NULL);
        displayGameStats(window_w / 2, window_h / 2 + 100, "Press 'ESC' to EXIT", NULL);
        Mix_FreeMusic(gMusic);
        gMusic = NULL;
    }
}


