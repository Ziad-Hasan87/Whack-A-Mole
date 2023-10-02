#ifndef ButtonObject_HPP
#define ButtonObject_HPP

#include <GameObject.hpp>


class ButtonObject : public GameObject
{
    public:
        ButtonObject(const char* textureSheet, const char* str,int x,int y, int h, int w);
        virtual ~ButtonObject();
        void Update();
        void Render();
        friend class Game;
    protected:
        SDL_Rect TextSRect, TextDRect;
        SDL_Texture *text;
        SDL_RendererFlip flip;
    private:
};

#endif // ButtonObject_HPP
