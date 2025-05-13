#ifndef DER_H_
#define DER_H_
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#define SCREEN_H = 400;
#define SCREEN_W = 900;
#define MAX_LIVES 5

typedef struct
{
    SDL_Surface *sprite;
    SDL_Surface *vies[MAX_LIVES]; 
    SDL_Surface *scoretxt;
    
    SDL_Rect posPerso;
    SDL_Rect posSprite;
    SDL_Rect posVie;
    SDL_Rect posScore;
    
    TTF_Font *police;
    int direction;
    int frame;
    int score;
    int vie;
    int maxVie;        
    
    
    Uint32 lastScoreTime; 
    int moveDistance;   
    int continuousMove; 
    float scoreMultiplier; 
    int lastDirection;      
    int speedScore;     
    int jump_height;
    int jump_V;
    int up;
    int speed;
    float acceleration;
    int isActive; 
} perso;

// Declaration Des Fonctions//
void initPerso(perso *p);
void afficherPerso(perso *p, SDL_Surface *screen);
void deplacerPerso(perso *p, Uint32 dt);
void animerPerso(perso *p);
void freePerso(perso *p);
void ajouterPerso(perso *p); 
void updateScore(perso *p, Uint32 currentTime); 
void updateLifeBar(perso *p); 

#endif
