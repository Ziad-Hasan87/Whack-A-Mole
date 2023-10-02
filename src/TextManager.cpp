#include "TextManager.hpp"
#include "Game.hpp"
#include <SDL.h>
#include <SDL_ttf.h>
TextManager::TextManager()
{}

SDL_Texture* TextManager::LoadText(const char* str, TTF_Font *font,SDL_Color *FontColor, int *h, int *w){
    if(strlen(str)){
        SDL_Surface* tempSurface = TTF_RenderText_Solid(font,str, *FontColor);
        if(tempSurface == NULL) std:: cout <<"HUGE ERROR!!! " <<std::endl;
        *h = tempSurface->h;
        *w = tempSurface->w;
        SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
        SDL_FreeSurface(tempSurface);
        return tex;
    }
    else return nullptr;
}

TextManager::~TextManager()
{
}
