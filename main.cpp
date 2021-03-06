#include <iostream> // cout
#include <memory> // Smart Pointers
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "sprite.hpp"
#include "spriteManager.hpp"
#include "header/fonction.hpp"
#include "header/class.hpp"
#include "Moks/header/Moks.hpp"


using namespace std;

int main(int argc, char *argv[])
{
    // Initialisation de la SDL2
    cout << "Start\n";
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        cout << "Failed to initialise SDL\n";
        return -1;
    }

    // Creation de la fenêtre principale
    SDL_Window *window = SDL_CreateWindow("Editeur 0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    1440, 800, SDL_WINDOW_SHOWN);

    if (window == nullptr)
    {
        SDL_Log("Could not create a window: %s", SDL_GetError());
        return -1;
    }

    // Creation du renderer correspondant à la fenêtre principale (1 renderer par fenêtre)
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        SDL_Log("Could not create a renderer: %s", SDL_GetError());
        return -1;
    }

    // Creation du manager de sprite
    spriteManager mySpriteManager;

    // Chemin des images
    string path1 = "background.png";
    string path2 = "Brick2.png";

    // Creation et ajout des sprites dans le Manager
    mySpriteManager.addSprite("Background", 0, 0, 1, 1, path1);
    //mySpriteManager.addSprite("Brique", 0, 0, 0.2, 0.2, path2);

    
    int posY=0;

    for (int i2=0; i2 < 19; i2++)
    {
        int posX=0;
        for (int i=0; i < 19; i++)
        {
            mySpriteManager.addSprite("Brique", posX, posY, 0.2, 0.2, path2);

            posX = posX + 76;
        }

        posY = posY + 25;
    }

    
    // Chargement des textures de tous les sprites
    mySpriteManager.loadAllTexture(renderer);
  
    // Boucle globale tant que la fenetre est ouverte
    while (true)
    {
        SDL_Event event;
        
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                break;
            }
        }

        // Affichage de tous les sprites par ordre d'ajout dans le vecteur des sprites
        mySpriteManager.update(renderer);

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
