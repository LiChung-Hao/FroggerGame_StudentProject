#include "CApp.h"

int CPlayer::loadPlayer(SDL_Renderer *renderer)
{
    SDL_Surface *temp;

    /* Load the sprite image */
    temp = SDL_LoadBMP(imagename);
    if (temp == NULL)
    {
        fprintf(stderr, "Couldn't load %s: %s", imagename, SDL_GetError());
        return (-1);
    }
    position.w = temp->w;
    position.h = temp->h;

    /* Set transparent pixel as the pixel at (0,0) */
    if (temp->format->palette)
    {
        SDL_SetColorKey(temp, SDL_TRUE, *(Uint8 *) temp->pixels);
    }
    else
    {
        switch (temp->format->BitsPerPixel)
        {
        case 15:
            SDL_SetColorKey(temp, SDL_TRUE,
                            (*(Uint16 *) temp->pixels) & 0x00007FFF);
            break;
        case 16:
            SDL_SetColorKey(temp, SDL_TRUE, *(Uint16 *) temp->pixels);
            break;
        case 24:
            SDL_SetColorKey(temp, SDL_TRUE,
                            (*(Uint32 *) temp->pixels) & 0x00FFFFFF);
            break;
        case 32:
            SDL_SetColorKey(temp, SDL_TRUE, *(Uint32 *) temp->pixels);
            break;
        }
    }

    /* Create textures from the image */
    texture = SDL_CreateTextureFromSurface(renderer, temp);
    if (!texture)
    {
        fprintf(stderr, "Couldn't create texture: %s\n", SDL_GetError());
        SDL_FreeSurface(temp);
        return (-1);
    }
    SDL_FreeSurface(temp);

    /* We're ready to roll. :) */
    return (0);
}

void CPlayer::display(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, texture, NULL, &position);
}

void CPlayer::moveLog1()
{
    //four lanes
    
    SDL_Rect* p;
    SDL_Rect* v;

    p = &position;
    v = &velocity;


    if (v->x <= 0)
    {
        v->x = -1;
    }

    p->x += v->x;

    if (p->x <= -170)
    {
        p->x = window_w + (rand() %30);
    }
}
void CPlayer::moveLog2()
{
    //four lanes
    int logs[] = { 5, 62, 121, 180 };
    SDL_Rect* p;
    SDL_Rect* v;

    p = &position;
    v = &velocity;


    if (v->x <= 0)
    {
        v->x = -2;
    }

    p->x += v->x;

    if (p->x <= -170)
    {
        p->x = window_w + (rand() % 30);
    }
}
void CPlayer::moveLog3()
{
    //four lanes
    int logs[] = { 5, 62, 121, 180 };
    SDL_Rect* p;
    SDL_Rect* v;

    p = &position;
    v = &velocity;


    if (v->x <= 0)
    {
        v->x = -1.5;
    }

    p->x += v->x;

    if (p->x <= -170)
    {
        p->x = window_w + (rand() % 30);
    }
}

void CPlayer::moveLog4()
{
    //four lanes
    int logs[] = { 5, 62, 121, 180 };
    SDL_Rect* p;
    SDL_Rect* v;

    p = &position;
    v = &velocity;


    if (v->x <= 0)
    {
        v->x = -2.2;
    }

    p->x += v->x;

    if (p->x <= -170)
    {
        p->x = window_w + (rand() % 30);
    }
}

void CPlayer::moveLlane1()
{
    SDL_Rect* p;
    SDL_Rect* v;

    p = &position;
    v = &velocity;


    if (v->x <= 0)
    {
        v->x = -4.8;
    }

    p->x += v->x;

    if (p->x <= -170)
    {
        p->x = window_w + (rand() % 10) ;
    }
}

void CPlayer::moveLlane2()
{
    SDL_Rect* p;
    SDL_Rect* v;

    p = &position;
    v = &velocity;


    if (v->x <= 0)
    {
        v->x = -2;
    }

    p->x += v->x;

    if (p->x <= -170)
    {
        p->x = window_w + (rand() % 10) ;
    }
}

void CPlayer::moveR()
{
    SDL_Rect* p;
    SDL_Rect* v;

    p = &position;
    v = &velocity;


    if (v->x <= 0)
    {
        v->x = 3.6;
    }

    p->x += v->x;

    if (p->x >= window_w+100)
    {
        p->y = 0.67 * (window_h);
        p->x = -150-(rand()%10);
    }
}

