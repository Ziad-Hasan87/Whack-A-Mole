#include "TextObject.hpp"
#include "TextManager.hpp"
#include <string>
#include <SDL_ttf.h>
#include <SDL.h>
#include <bits/stdc++.h>
extern double Ratio;
using namespace std;
TextObject::TextObject()
{
    //ctor
}
TextObject::TextObject(char line[],TTF_Font *font, SDL_Color *color, int x, int y)
{
    int h, w;
    FontColor = color;
    objTexture = TextManager::LoadText(line,font, FontColor, &h, &w);
    this->font = font;
    height = h;
    width = w;
    xpos = x*Ratio;
    ypos = y*Ratio;
    FontColor = color;
    srcRect.h = height;
    srcRect.w = width;
    srcRect.x = 0;
    srcRect.y = 0;
    destRect.x = x*Ratio;
    destRect.y = y*Ratio;
    destRect.w = width*Ratio;
    destRect.h = height*Ratio;
}
void TextObject::Update(){
    SDL_DestroyTexture(objTexture);
    objTexture = TextManager::LoadText(line, font, FontColor, &height, &width);
}

void TextObject::Render(){
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}
TextObject::~TextObject()
{
    SDL_DestroyTexture(objTexture);
}
