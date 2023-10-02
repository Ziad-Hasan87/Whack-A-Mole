#ifndef BackGroundObject_HPP
#define BackGroundObject_HPP
#pragma once
#include "GameObject.hpp"

class BackGroundObject: public GameObject
{
    public:
        BackGroundObject();
        BackGroundObject(const char* textureSheet, int x, int y, int h, int w);
        ~BackGroundObject();
        void Update();
        void Render();
        void Update(SDL_Texture *Picture,int x, int y, int h, int w);
        friend class Game;
        template <class T>
        friend void operator+(BackGroundObject&a,T t);

    protected:

    private:
};
template <class T>
void operator+(BackGroundObject&a,T t)
{
    a.ypos+=t;
}

#endif //BackGroundObject_HPP
