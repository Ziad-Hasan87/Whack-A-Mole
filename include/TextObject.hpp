#ifndef TEXTOBJECT_HPP
#define TEXTOBJECT_HPP
#include <SDL_ttf.h>
#include <GameObject.hpp>
using namespace std;

class TextObject : public GameObject
{
    public:
        friend class Game;
        TextObject();
        TextObject(char line[],TTF_Font *font,SDL_Color *color, int x, int y);
        void Update();
        void Render();
        virtual ~TextObject();
    protected:

    private:
        char line[2];
        char lombaline[20];
        SDL_Color *FontColor;
        SDL_Color *FontShade;
        TTF_Font *font;
};

#endif // TEXTOBJECT_HPP
