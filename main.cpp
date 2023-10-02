#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <Game.hpp>
#include <BackGroundObject.hpp>
#include <SDL_ttf.h>
#include <fstream>
using namespace std;
Game *game = nullptr;
SDL_Texture *AnyaLoop[21];
TTF_Font *ButtonFont = NULL;
ifstream fin;
ofstream fout;
double Ratio;
vector <pair <int, int>> HolePos;
vector <pair <int, int>> HitBox;
set <pair <int, string>> highscore;
pair <int, string> newscore;
enum Status {MainMenu=0, LeaderBoard=1, InGame=2, GameOver=3, NameInput=4};
Status GameStatus;
double precal(int x, int y);
int main(int argc, char *argv[])
{
    GameStatus = MainMenu;
    const int FPS = 60;
    const int frameDelay = 1000/FPS;
    Uint32 frameStart;
    int frameTime;
    game = new Game();
    game->init("My Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED);
    while(game->running()){
        frameStart = SDL_GetTicks();
        game->update();
        game->render();
        game->handleEvents();
        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }
    }
    cout << "Thank You for Playing!!!\n";
    return 0;
}

double precal(int x, int y){
    fin.open("Assets/LEADERBOARD.txt",fstream::in);
    while(!fin.eof()){
        fin >> newscore.first >> newscore.second;
        highscore.insert(newscore);
    }
    fin.close();
    HolePos.push_back({297, 317});HolePos.push_back({720, 287});
    HolePos.push_back({1093, 330});HolePos.push_back({97, 469});
    HolePos.push_back({642, 450});HolePos.push_back({1326, 454});
    HolePos.push_back({422, 614});HolePos.push_back({998, 573});
    HitBox.push_back({427, 507});HitBox.push_back({850, 477});
    HitBox.push_back({1223, 521});HitBox.push_back({227, 659});
    HitBox.push_back({772, 640});HitBox.push_back({1456, 644});
    HitBox.push_back({552, 804});HitBox.push_back({1128, 763});
    return x/1920.0;
}

void saveScore(){
    fout.open("Assets/LEADERBOARD.txt");
    auto it = highscore.begin();
    do{
        if(it != highscore.begin()) fout << endl;
        if((*it).first)fout << (*it).first <<" "<< (*it).second;
        it++;
    }
    while(it!=highscore.end());
    fout.close();
}
