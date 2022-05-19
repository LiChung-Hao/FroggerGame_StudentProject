//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnEvent(SDL_Event* Event) {

    switch(Event->type)
    {
		case SDL_QUIT:

            Running = false;
            break;

            //for developping needs, it's faster to check game status
        //case SDL_MOUSEMOTION:

        //    frog.position.x = Event->motion.x;						//Player.x location = mouse current x location 
        //    frog.position.y = Event->motion.y;						//Player.y location = mouse current y location 
        //    std::cout << "posX: " << frog.position.x << " POSY: " << frog.position.y;
        //    break;
        case SDL_KEYDOWN:

            switch(Event->key.keysym.sym)
            {

                // UP Arrow key
                case SDLK_UP:

                    frog.position.y -= 10;								// change the y location by -10
                    if (frog.position.y < 0)
                    {
                        frog.position.y = 0;
                    }
                    break;

                    // DOWN Arrow key
                case SDLK_DOWN:

                    frog.position.y += 10;								// change the y location by +10
                    if (frog.position.y >= (window_h - frog.position.h))
                    {
                        frog.position.y = (window_h - frog.position.h);
                    }
                    break;

                    // LEFT Arrow key
                case SDLK_LEFT:

                    frog.position.x -= 10;								// change the x location by -10
                    if (frog.position.x < 0)
                    {
                        frog.position.x = 0;
                    }
                    break;

                    // RIGHT Arrow key
                case SDLK_RIGHT:

                    frog.position.x += 10;								// change the x location by +10
                    if (frog.position.x >= (window_w - frog.position.w))
                    {
                        frog.position.x = (window_w - frog.position.w);
                    }
                    break;
                
			

				// When a is pressed speed of arrows falling down and scrolling background is increased by 1
                case SDLK_a:
					background.velocity.x+=1;
                    for(int i = 0; i < NUM_SPRITES ; ++i)
					{
                            car[i].velocity.y += 1;
                    }
                    break;

				// When z is pressed speed of arrows falling down and scrolling background is decreased by 1
				case SDLK_z:
					if (background.velocity.x > 0)
					{
						background.velocity.x--;	
					}

					for(int i = 0 ; i < NUM_SPRITES ; ++i)
					{
                            car[i].velocity.y -= 1;
                    }
                             break;
				// 'p' To play the Game again
                case SDLK_p:
					SDL_DestroyRenderer( renderer );
                    SDL_DestroyWindow( window );
                    window = NULL;
                    renderer = NULL;
                    SDL_QUIT;
                    gameOver = false;
                    gameWin = false;
                    OnInit();
                    break;
				
				// 'Esc' to exit 
                case SDLK_ESCAPE:

                    Running=false;
                    break;
                    }
    }
}

//==============================================================================
