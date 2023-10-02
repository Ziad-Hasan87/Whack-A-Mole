#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#pragma once
#include "Game.hpp"

class GameObject
{
    public:
        GameObject();
        ~GameObject();
        virtual void Update() = 0;
        virtual void Render() = 0;
    protected:
        int xpos;
        int ypos;
        int height;
        int width;
        SDL_Texture *objTexture;
        SDL_Rect srcRect, destRect;
};

#endif // GAMEOBJECT_HPP
