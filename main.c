#include "person.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>


typedef struct {
    SDL_Rect pos;
    int active;
} Obstacle;

int checkCollision(SDL_Rect a, SDL_Rect b) {
    
    if (a.y + a.h <= b.y) return 0;
    if (a.y >= b.y + b.h) return 0;
    if (a.x + a.w <= b.x) return 0;
    if (a.x >= b.x + b.w) return 0;
    return 1; 
}

int main()
{
    
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1) {
        printf("Erreur d'initialisation de SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0) {
        printf("Erreur d'initialisation de SDL_image : %s\n", IMG_GetError());
        return EXIT_FAILURE;
    }
    
    if (TTF_Init() == -1) {
        printf("Erreur d'initialisation de SDL_ttf : %s\n", TTF_GetError());
        return EXIT_FAILURE;
    }
    
    SDL_Surface *screen = SDL_SetVideoMode(900, 400, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (!screen) {
        printf("Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    
    SDL_Surface *Background = IMG_Load("bg.jpg");
    if (!Background) {
        printf("Erreur lors du chargement de l'image de fond : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    
    SDL_Event event;
    
    SDL_Rect posBackground;
    posBackground.x = 0;
    posBackground.y = 0;
    
    int continuer = 1;
    int secondPlayerActive = 0;
    
    
    Obstacle obstacle;
    obstacle.pos.x = 400;
    obstacle.pos.y = 400 - 40; 
    obstacle.pos.w = 30;
    obstacle.pos.h = 40;
    obstacle.active = 1;
    
    Uint32 start, prev, dt, currentTime;
     int FPS = 15;
    
    
    perso p1;
    perso p2; 
    
    initPerso(&p1);
    
    
    while (continuer)
    {
        start = SDL_GetTicks();
        prev = start;
        currentTime = start;
        
       
        SDL_BlitSurface(Background, NULL, screen, &posBackground);
        
        
        if (obstacle.active) {
            SDL_Rect obstacleColor = {obstacle.pos.x, obstacle.pos.y, obstacle.pos.w, obstacle.pos.h};
            SDL_FillRect(screen, &obstacleColor, SDL_MapRGB(screen->format, 255, 0, 0));
        }
        
       
        updateScore(&p1, currentTime); 
        updateLifeBar(&p1);  
        afficherPerso(&p1, screen);
        
        
        dt = SDL_GetTicks() - prev;
        
        deplacerPerso(&p1, dt);
        animerPerso(&p1);
        
        
        if (obstacle.active && checkCollision(p1.posPerso, obstacle.pos)) {
            decreaseLife(&p1);
           
            if (p1.direction == 1) { 
                p1.posPerso.x = obstacle.pos.x - p1.posPerso.w - 5;
            } else { 
                p1.posPerso.x = obstacle.pos.x + obstacle.pos.w + 5;
            }
        
        
       
        if (p1.vie <= 0) {
            
            printf("Game Over - Player 1\n");
            
            
            SDL_Color gameOverColor = {255, 0, 0}; 
            SDL_Surface* gameOverText = TTF_RenderText_Blended(p1.police, "GAME OVER", gameOverColor);
            SDL_Rect gameOverPos;
            gameOverPos.x = (900 - gameOverText->w) / 2; 
            gameOverPos.y = 200; 
            SDL_BlitSurface(gameOverText, NULL, screen, &gameOverPos);
            
            
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r) {
                p1.vie = p1.maxVie;
                p1.score = 0; 
            }
        }

        
        if (secondPlayerActive) {
            updateScore(&p2, currentTime);
            updateLifeBar(&p2);  
            afficherPerso(&p2, screen);
            deplacerPerso(&p2, dt);
            animerPerso(&p2);
            
            
            if (obstacle.active && checkCollision(p2.posPerso, obstacle.pos)) {
                decreaseLife(&p2);
                
                if (p2.direction == 1) {
                    p2.posPerso.x = obstacle.pos.x - p2.posPerso.w - 5;
                } else {
                    p2.posPerso.x = obstacle.pos.x + obstacle.pos.w + 5;
                }
            }
            
            
            if (p2.vie <= 0) {
                printf("Game Over - Player 2\n");
                
                
                SDL_Color gameOverColor = {255, 0, 0}; 
                SDL_Surface* gameOverText = TTF_RenderText_Blended(p2.police, "GAME OVER P2", gameOverColor);
                SDL_Rect gameOverPos;
                gameOverPos.x = (900 - gameOverText->w) / 2; 
                gameOverPos.y = 230; 
                SDL_BlitSurface(gameOverText, NULL, screen, &gameOverPos);
                
                
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r) {
                    p2.vie = p2.maxVie;
                    p2.score = 0;
                }
            }
        }
        
        
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                continuer = 0;
                break;
                
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
               
                case SDLK_RIGHT:
                    p1.direction = 1;
                    break;
                case SDLK_LEFT:
                    p1.direction = 0;
                    break;
                case SDLK_UP:
                    p1.score += 10; 
                    break;
                
                case SDLK_SPACE:
                    if (p1.up == 0)
                    {
                        p1.jump_V = -p1.jump_height;
                        p1.up = 1;
                    }
                    break;
                    
                
                case SDLK_a:
                    if (!secondPlayerActive) {
                        
                        initPerso(&p2); 
                        ajouterPerso(&p2); 
                        secondPlayerActive = 1;
                    }
                    break;
                    
                
                case SDLK_d:
                    if (secondPlayerActive)
                        p2.direction = 1;
                    break;
                case SDLK_q:
                    if (secondPlayerActive)
                        p2.direction = 0;
                    break;
                case SDLK_z:
                    if (secondPlayerActive)
                        p2.score += 10; 
                    break;
                case SDLK_s:
                    if (secondPlayerActive)
                        decreaseLife(&p2); 
                    break;
                case SDLK_w: 
                    if (secondPlayerActive && p2.up == 0)
                    {
                        p2.jump_V = -p2.jump_height;
                        p2.up = 1;
                    }
                    break;
                    
                
                case SDLK_h:
                    if (p1.vie < p1.maxVie) {
                        p1.vie++;
                    }
                    break;
                }
                break;
                
            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                
                case SDLK_RIGHT:
                    p1.direction = -1;
                    break;
                case SDLK_LEFT:
                    p1.direction = -2;
                    break;
                    
                
                case SDLK_d:
                    if (secondPlayerActive)
                        p2.direction = -1;
                    break;
                case SDLK_q:
                    if (secondPlayerActive)
                        p2.direction = -2;
                    break;
                }
                break;
            }
        }
        
        SDL_Flip(screen);
        
       
        if (1000 / FPS > SDL_GetTicks() - start)
            SDL_Delay(1000 / FPS - (SDL_GetTicks() - start));
    }
    
   
    SDL_FreeSurface(screen);
    SDL_FreeSurface(Background);
    freePerso(&p1);
    if (secondPlayerActive)
        freePerso(&p2);
    
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    
    return 0;
}
