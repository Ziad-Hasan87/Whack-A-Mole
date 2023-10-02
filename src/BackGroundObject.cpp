#include "BackGroundObject.hpp"
#include "TextureManager.hpp"
extern double Ratio;
BackGroundObject::BackGroundObject()
{

}

BackGroundObject::BackGroundObject(const char* textureSheet, int x, int y, int h, int w)
{

    objTexture = TextureManager::LoadTexture(textureSheet);
    xpos = x;
    ypos = y;
    height = h;
    width = w;
    //ctor
}


void BackGroundObject::Update()
{
    srcRect.h = height;
    srcRect.w = width;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos*Ratio;
    destRect.y = ypos*Ratio;
    destRect.w = width*Ratio;
    destRect.h = height*Ratio;
}
void BackGroundObject::Update(SDL_Texture* Picture, int x, int y, int h, int w)
{
    height = h;
    width = w;
    objTexture = Picture;
    srcRect.h = h;
    srcRect.w = w;
    srcRect.x = 0;
    srcRect.y = 0;
    destRect.x = x*Ratio;
    destRect.y = y*Ratio;
    destRect.w = w*Ratio;
    destRect.h = h*Ratio;
}

void BackGroundObject::Render()
{
    SDL_RenderCopy(Game::renderer,objTexture, &srcRect, &destRect);

}


BackGroundObject::~BackGroundObject()
{
    //dtor
}
