#include "ButtonObject.hpp"
#include "TextureManager.hpp"
#include "TextManager.hpp"
extern double Ratio;
ButtonObject::ButtonObject(const char* textureSheet,const char* str,int x, int y, int h, int w)
{
    objTexture = TextureManager::LoadTexture(textureSheet);
    text = TextureManager::LoadTexture(str);
    xpos = x*Ratio;
    ypos = y*Ratio;
    height = h;
    width = w;
    flip = SDL_FLIP_NONE;
}
void ButtonObject::Update(){

    srcRect.h = height;
    srcRect.w = width;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos; //740
    destRect.y = ypos; //850
    destRect.w = 440 * Ratio;
    destRect.h = 117 * Ratio;

    TextSRect.x = 0;
    TextSRect.y = 0;
    TextSRect.h = height; //195
    TextSRect.w = width; //732

    TextDRect = destRect;
}

void ButtonObject::Render()
{
    SDL_RenderCopyEx(Game::renderer, objTexture, &TextSRect, &TextDRect, 0 , nullptr, flip);
    SDL_RenderCopy(Game::renderer, text, &srcRect, &destRect);
}

ButtonObject::~ButtonObject()
{
    //dtor
}
