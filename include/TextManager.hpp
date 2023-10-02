#ifndef TEXTMANAGER_HPP
#define TEXTMANAGER_HPP
#include <SDL2/SDL.h>
#include <SDL_ttf.h>

class TextManager
{
    public:
        TextManager();
        static SDL_Texture * LoadText(const char* str,TTF_Font *font, SDL_Color *color, int *h, int *w);
        virtual ~TextManager();

    protected:

    private:
};

#endif // TEXTMANAGER_HPP
