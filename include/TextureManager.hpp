#ifndef TEXTUREMANGER_HPP_INCLUDED
#define TEXTUREMANGER_HPP_INCLUDED



#pragma once
#include "Game.hpp"
class TextureManager{
public:
    static SDL_Texture* LoadTexture (const char* fileName);

};
#endif // TEXTUREMANGER_HPP_INCLUDED
