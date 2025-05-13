#include "person.h"
void initPerso(perso *p)
{
    
    p->sprite = IMG_Load("sprite sheet.png");
    if (!p->sprite) {
        printf("Erreur lors du chargement du sprite : %s\n", IMG_GetError());
        return;
    }
    
    
    char filename[20];
    for (int i = 0; i < MAX_LIVES; i++) {
        sprintf(filename, "hp_%d.png", i);
        p->vies[i] = IMG_Load(filename);
        if (!p->vies[i]) {  
            printf("Erreur lors du chargement de l'image de vie %s : %s\n", filename, IMG_GetError());
            return;
        }
    }
    
    /
    p->police = TTF_OpenFont("font.ttf", 40);
    if (!p->police) {
        printf("Erreur lors du chargement de la police : %s\n", TTF_GetError());
        return;
    }
    
    p->posPerso.x = 0;
    p->posPerso.y = 400 - 85;
    p->posPerso.w = 52;
    p->posPerso.h = 85;
    
   
    p->posVie.x = 10;
    p->posVie.y = 10;
    
    p->posSprite.x = 0;
    p->posSprite.y = 0;
    p->posSprite.w = 52;
    p->posSprite.h = 85;
    p->score = 0;
    p->posScore.x = 10;
    p->posScore.y = 50;
    p->frame = 0;
    p->direction = -1;
    p->jump_height = 30;
    p->jump_V = 0;
    p->up = 0;
    p->speed = 1;
    p->acceleration = 0;
    
    
    p->vie = MAX_LIVES - 1;     
    p->maxVie = MAX_LIVES - 1;  
   
    
    p->lastScoreTime = SDL_GetTicks();
    p->moveDistance = 0;
}

void afficherPerso(perso *p, SDL_Surface *screen)
{
    SDL_Color couleur = {0, 0, 255};
    char s[20];
    
    sprintf(s, "Score: %d", p->score);
    
    p->scoretxt = TTF_RenderText_Blended(p->police, s, couleur);
    
    
    SDL_BlitSurface(p->sprite, &p->posSprite, screen, &p->posPerso);
    
    
    SDL_BlitSurface(p->vies[p->vie], NULL, screen, &p->posVie);
    
    
    SDL_BlitSurface(p->scoretxt, NULL, screen, &p->posScore);
    
    
    p->frame++;
    if (p->frame == 7)
        p->frame = 0;
        
    

void deplacerPerso(perso *p, Uint32 dt)
{
    int oldX = p->posPerso.x;
    
    
    switch (p->direction)
    {
    case 1:
        p->posPerso.x += ((p->acceleration / 2) * (dt * dt) + (p->speed * dt));
        p->acceleration += 0.02;
        break;
    case 0:
        p->posPerso.x -= ((p->acceleration / 2) * (dt * dt) + (p->speed * dt));
        p->acceleration += 0.02;
        break;
    default:
        p->acceleration = 0;
        break;
    }
    
    
    if (p->direction != -1 && p->direction != -2) {
        p->moveDistance += abs(p->posPerso.x - oldX);
        
        
        if (p->moveDistance >= 50) {
            p->score += p->moveDistance / 50;
            p->moveDistance %= 50;
        }
    }
    
    
    if (p->up == 1)
    {
        p->jump_V += 3;
        p->posPerso.y += p->jump_V;
        if (p->posPerso.y > (400 - 85))
        {
            p->posPerso.y = 400 - 85;
            p->jump_V = 0;
            p->up = 0;
            
            
            p->score += 5;
        }
    }
    
    
    if (p->posPerso.x < 0) {
        p->posPerso.x = 0;
    } else if (p->posPerso.x > 900 - p->posPerso.w) {
        p->posPerso.x = 900 - p->posPerso.w;
    }
}

void animerPerso(perso *p)
{
    int i;

    int var = p->direction;
    if (var == -1)
        var = 1;
    if (var == -2)
        var = 0;
   
        p->posSprite.x = 52 * p->frame;
        p->posSprite.y = 85 * var;
        p->posSprite.w = 52;
        p->posSprite.h = 85;
}

void updateScore(perso *p, Uint32 currentTime)
{
    
    if (currentTime - p->lastScoreTime >= 1000) {
        p->score += 1;
        p->lastScoreTime = currentTime;
    }
}



void updateLifeBar(perso *p)
{
    
    if (p->vie < 0) {
        p->vie = 0;
    } else if (p->vie > p->maxVie) {
        p->vie = p->maxVie;
    }
}

void freePerso(perso *p)
{
    SDL_FreeSurface(p->sprite);
    SDL_FreeSurface(p->scoretxt);
    
    for (int i = 0; i < MAX_LIVES; i++) {
        if (p->vies[i]) {
            SDL_FreeSurface(p->vies[i]);
        }
    }
    TTF_CloseFont(p->police);
}

void ajouterPerso(perso *p)
{
    e
    p->sprite = IMG_Load("sprite sheet.png");
    
    
    char filename[20];
    for (int i = 0; i < MAX_LIVES; i++) {
        sprintf(filename, "hp_%d.png", i);
        p->vies[i] = IMG_Load(filename);
        if (!p->vies[i]) {
            printf("Erreur lors du chargement de l'image de vie %s : %s\n", filename, IMG_GetError());
            return;
        }
    }
    
   
    p->posPerso.x = 200; 
    p->posPerso.y = 400 - 85;
    p->posPerso.w = 52;
    p->posPerso.h = 85;
    
    
    p->posVie.x = 300; 
    p->posVie.y = 10;
    
   
    p->posSprite.x = 0;
    p->posSprite.y = 0;
    p->posSprite.w = 52;
    p->posSprite.h = 85;
    
    
    p->score = 0;
    p->posScore.x = 300; 
    p->posScore.y = 50;
    
 
    p->frame = 0;
    p->direction = -1;
    p->jump_height = 30;
    p->jump_V = 0;
    p->up = 0;
    p->speed = 1;
    p->acceleration = 0;
    p->isActive = 1;
    
  
    p->vie = MAX_LIVES - 1;     
    p->maxVie = MAX_LIVES - 1; 
    p->heartWidth = p->vies[0]->w; 
    p->invincibleTime = 0;
    p->lastScoreTime = SDL_GetTicks();
    p->moveDistance = 0;
}
