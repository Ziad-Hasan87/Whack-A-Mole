#ifndef GAME_HPP
#define GAME_HPP
#include <SDL.h>
#include <iostream>
#include <SDL_image.h>

class Game{
    public:
        Game();
        ~Game();
        void init(const char *title, int xpos, int ypos);
        void handleEvents();
        void update();
        void render();
        void clean();
        bool running(){return isRunning;}

        static SDL_Renderer *renderer;
    private:
        bool isRunning;
        SDL_Window *window;
        int cnt;
};
#endif

