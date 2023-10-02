#include "Game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "ButtonObject.hpp"
#include "BackGroundObject.hpp"
#include "TextObject.hpp"
#include <SDL_ttf.h>
#include <string>
#include <SDL_keycode.h>
#include <bits/stdc++.h>
using namespace std;
int windowh, windoww, change = 5;
GameObject* HSsticker = nullptr;
BackGroundObject* background, *leaderboardBG, *gameBG, *Anya, *GameOverBG, *NameInputBG, *Hsticker,*Welcome;
SDL_Color ScoreWhite = {247,247,247}, ScoreBrown = {122,14,24},ScoreShade= {200,200,200};
ButtonObject* whack, *leaderboard, *quit;
TextObject* finalScore, *scoreCounter, *timeCounter, *LBscore[10];
SDL_Renderer* Game::renderer = nullptr;
TTF_Font* FinalScoreFont,*scoreCounterFont, *LBfont;
SDL_Rect NameSrect, NameDrect;
SDL_Surface *temp;
SDL_Texture *textImage;
string name;
char AnyaStat[]="Assets/Anya/AnyaU1.png", ScoreSTR[20], *dummy, *tdummy, ara[3] = {}, tara[3]={}, lara[3] = {};
extern void saveScore();
extern SDL_Texture *AnyaLoop[21];
extern pair<int, string> newscore;
extern set <pair<int,string>> highscore;
extern vector <pair <int, int>> HolePos;
extern vector <pair <int, int>> HitBox;
extern enum Status {MainMenu, LeaderBoard, InGame, GameOver, NameInput} GameStatus;
extern double Ratio;
extern double precal(int x, int y);
int FPS_Counter = 0, increase = 1, RandHole, Index, smack_count=0,seed, doubler, second;
int interval, score, startFrame, field;
bool smacked = false,hsc=false;

Game::Game()
{
    //ctor
}

Game::~Game()
{
    //dtor
}

void Game::init(const char *title, int xpos, int ypos){
    TTF_Init();
    SDL_Init(SDL_INIT_EVERYTHING);
    cout << "All systems Initialized\n";
    window = SDL_CreateWindow("Whack-A-Mole", xpos, ypos, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
    cout << "Window Created\n";
    SDL_GetWindowSize(window, &windoww, &windowh);
    Ratio = precal(windoww,windowh);
    renderer = SDL_CreateRenderer(window, -1, 0);
    isRunning = true;
    doubler = 0;
    interval  = 30;
    srand(time(0));
    dummy = ara;
    tdummy = tara;
    RandHole = rand() % 8;
    Hsticker= (new BackGroundObject("Assets/NewHighScore.png",1080,500, 246,246));
    HSsticker=dynamic_cast<GameObject*> (Hsticker);
    FinalScoreFont = TTF_OpenFont("Assets/BRLNSDB.TTF",150);
    LBfont = TTF_OpenFont("Assets/BRLNSDB.TTF",50);
    scoreCounterFont = TTF_OpenFont("Assets/BRLNSDB.TTF",100);
    whack = new ButtonObject("Assets/Template.png", "Assets/Whack.png", 740, 475, 195, 732);
    leaderboard = new ButtonObject("Assets/Template.png", "Assets/Leaderboards.png",740, 625, 195, 732);
    quit = new ButtonObject("Assets/Template.png", "Assets/Quit.png", 740, 775, 195, 732);
    background = new BackGroundObject("Assets/BG.png",0,0, 1080,1920);
    leaderboardBG = new BackGroundObject("Assets/LeaderboardBG.png",0,0, 1080,1920);
    gameBG = new BackGroundObject("Assets/Field.png",0,0, 1080,1920);
    GameOverBG = new BackGroundObject("Assets/GameOver.png",0,0, 1080,1920);
    Welcome = new BackGroundObject("Assets/Welcome2.png",835,-250, 250,250);
    HSsticker->Update();
    NameInputBG = new BackGroundObject("Assets/NameBG.png",0,0, 1080,1920);
    Anya = new BackGroundObject("Assets/BG.png",0,0, 1080,1920);
    for(int i = 0 ; i < 9; i++){
        AnyaLoop[i]= TextureManager::LoadTexture(AnyaStat);
        AnyaStat[17]++;
    }
    AnyaStat[16] = 'S';
    AnyaStat[17] = '1';
    for(int i = 9 ; i < 12; i++){
        AnyaLoop[i]= TextureManager::LoadTexture(AnyaStat);
        AnyaStat[17]++;
    }
    AnyaStat[16] = 'D';
    AnyaStat[17] = '1';
    for(int i  = 12; i < 21; i++){
        AnyaLoop[i]= TextureManager::LoadTexture(AnyaStat);
        AnyaStat[17]++;
    }
    cout << "Game Launched\n";
}
void Game::handleEvents(){
    SDL_Event event;
    int x,y;
    SDL_PollEvent(&event);
    SDL_GetMouseState(&x,&y);
    if(GameStatus == NameInput){
        if(event.type == SDL_KEYDOWN){
            if(name.size() > 0 && event.key.keysym.sym == SDLK_BACKSPACE){
                name.pop_back();
                if(textImage) {
                    SDL_DestroyTexture(textImage);
                    textImage = NULL;
                }
                if(name.size() > 0){
                    if(name.size()) temp = TTF_RenderText_Solid(scoreCounterFont,name.c_str(), ScoreBrown);
                    if(temp) textImage = SDL_CreateTextureFromSurface(renderer, temp);
                    NameSrect.h = temp->h;
                    NameSrect.w = temp->w;
                    NameSrect.x = 0;
                    NameSrect.y = 0;
                    NameDrect = NameSrect;
                    NameDrect.x = ((windoww - NameSrect.w)/2)*Ratio;
                    NameDrect.y = 540*Ratio;
                }
                if(temp){
                    SDL_FreeSurface(temp);
                    temp = NULL;
                }
            }
            else if(event.key.keysym.sym == SDLK_RETURN && name.size() > 0){
                SDL_DestroyTexture(textImage);
                textImage = NULL;
                SDL_FreeSurface(temp);
                temp = NULL;
                GameStatus = InGame;
                score = 0;second = 60;
                scoreCounter = new TextObject("0",scoreCounterFont, &ScoreWhite, 1770, 10);
                startFrame = FPS_Counter;
            }
        }
        else if(event.type == SDL_TEXTINPUT && name.size() <= 10){
            name += event.text.text;
            if(textImage) {
                SDL_DestroyTexture(textImage);
                textImage = NULL;
            }
            if(name.size() > 0){
                if(name.size())temp = TTF_RenderText_Solid(scoreCounterFont,name.c_str(), ScoreBrown);
                if(temp) textImage = SDL_CreateTextureFromSurface(renderer, temp);
                NameSrect.h = temp->h;
                NameSrect.w = temp->w;
                NameSrect.x = 0;
                NameSrect.y = 0;
                NameDrect = NameSrect;
                NameDrect.x = ((windoww - NameSrect.w)/2)*Ratio;
                NameDrect.y = (540)*Ratio;
            }
            if(temp){
                SDL_FreeSurface(temp);
                temp = NULL;
            }
        }
    }
    if(event.type == SDL_KEYDOWN){
        if(event.key.keysym.sym == SDLK_ESCAPE){
            if(GameStatus == MainMenu) {
                isRunning = false;
            }
            if(GameStatus == LeaderBoard){
                for(int i = 0; i < highscore.size(); i++){
                    if(LBscore[i]){
                        delete LBscore[i];
                        LBscore[i] = NULL;
                    }
                    if(LBscore[i+5]){
                        delete LBscore[i+5];
                        LBscore[i+5] = NULL;
                    }
                }
                GameStatus = MainMenu;
            }
            else{
                if(GameStatus == NameInput) name.clear();
                dummy[0] = '\0';
                GameStatus = MainMenu;
                score = 0;
                FPS_Counter = 0;
            }
        }
    }
    switch(event.type){
    case (SDL_MOUSEBUTTONUP):
        SDL_GetMouseState(&x,&y);
        (seed *= (x*y)%10007) %= 10007;
        if(GameStatus == MainMenu){
            // QUITif(textImage) {
            if(textImage){
                SDL_DestroyTexture(textImage);
                textImage = NULL;
            }
            if(temp){
                SDL_FreeSurface(temp);
                temp = NULL;
            }
            name.clear();
            if((x > quit->xpos && x < (quit->xpos + 440*Ratio)) && (y > quit->ypos && y < (quit->ypos +117*Ratio))){
                isRunning = false;
            }
            //LEADERBOARD
            else if((x > leaderboard->xpos && x < (leaderboard->xpos + 440*Ratio)) && (y > leaderboard->ypos && y < (leaderboard->ypos +117*Ratio))){
                leaderboard->flip = SDL_FLIP_NONE;
                GameStatus = LeaderBoard;
                if(GameStatus == LeaderBoard){
                    auto it = highscore.begin();
                    for(int i = highscore.size()-1 ; i >= 0; i--){
                        sprintf(ScoreSTR,"%s", ((*it).second).c_str());
                        LBscore[i] = new TextObject(ScoreSTR, LBfont, &ScoreBrown,800,(347 + 55*i));
                        if((*it).first > 9) {
                            lara[0] = (*it).first/10 + '0';
                            lara[1] = (*it).first%10+ '0';
                            lara[3] = '\0';
                        }
                        else{
                            lara[0] = (*it).first%10 +'0';
                            lara[1] = '\0';
                        }
                        if(LBscore[i]->objTexture)LBscore[i+5] = new TextObject(lara, LBfont, &ScoreBrown,1160,(347 + 55*i));
                        it++;
                    }
                }
            }
            //WHACK
            else if((x > whack->xpos && x < (whack->xpos + 440*Ratio)) && (y > whack->ypos && y < (whack->ypos +117*Ratio))){
                GameStatus = NameInput;
                whack->flip = SDL_FLIP_NONE;
                score = 0;
            }
            break;
        }
        else if(GameStatus == GameOver){
            doubler++;
            if(doubler % 2 == 0) {
                    GameStatus = MainMenu;
                    dummy[0] = '\0';
                    delete finalScore;
            }
        }
    case (SDL_MOUSEBUTTONDOWN):
        SDL_GetMouseState(&x,&y);
        if(GameStatus == MainMenu){
            //QUIT
            if((x > quit->xpos && x < (quit->xpos + 440*Ratio)) && (y > quit->ypos && y < (quit->ypos +117*Ratio))){
                quit->flip = SDL_FLIP_VERTICAL;
            }
            //LEADERBOARD
            else if((x > leaderboard->xpos && x < (leaderboard->xpos + 440*Ratio)) && (y > leaderboard->ypos && y < (leaderboard->ypos +117*Ratio))){
                leaderboard->flip = SDL_FLIP_VERTICAL;
            }
            //WHACK
            else if((x > whack->xpos && x < (whack->xpos + 440*Ratio)) && (y > whack->ypos && y < (whack->ypos +117*Ratio))){
                whack->flip = SDL_FLIP_VERTICAL;
            }
        }
        else if(GameStatus == InGame){
            if( ( x > HitBox[RandHole].first*Ratio && (x < HitBox[RandHole].first+155*Ratio) ) && ( y > HitBox[RandHole].second*Ratio && y < (HitBox[RandHole].second+155)*Ratio)){
                if((Index < 2 && increase<0) || Index == 0) {}
                else {
                    smacked = true;
                }
                break;
            }
        }
        break;
    case (SDL_QUIT):
        isRunning = false;
        break;
    default:
        break;
    }
}
void Game::update(){
    whack->Update();
    Welcome->Update();
    leaderboard->Update();
    quit->Update();
    NameInputBG->Update();
    background->Update();
    if(scoreCounter)delete scoreCounter;
    if(timeCounter)delete timeCounter;
    timeCounter = NULL;
    scoreCounter = NULL;
    if(GameStatus == InGame){
        second = 60 - (FPS_Counter - startFrame)/60;
        if(second/10 == 0){
            tara[1] = '\0';
            tara[0] = (char) ((second%10)+'0');
        }
        else{
            tara[1] =(char) ((second%10)+'0');
            tara[0] =(char) ((second/10)+'0');
        }
    }
    if(scoreCounter) delete scoreCounter;
    if(timeCounter) delete timeCounter;
    if(dummy[0] == '\0') scoreCounter = new TextObject("0", scoreCounterFont, &ScoreWhite, 1770, 10);
    else scoreCounter = new TextObject(dummy, scoreCounterFont, &ScoreWhite, 1770, 10);
    if(tdummy[0] == '\0') timeCounter = new TextObject("0", scoreCounterFont, &ScoreWhite, 260, 10);
    else timeCounter = new TextObject(tdummy, scoreCounterFont, &ScoreWhite, 260, 10);
    leaderboardBG->Update();
    gameBG->Update();
    GameOverBG->Update();
    if(GameStatus == InGame){
        if(FPS_Counter - startFrame >= 3600){
            GameStatus = GameOver;
            newscore.second = name;
            newscore.first = score;
            newscore.first = score;
            name.clear();
            highscore.insert(newscore);
            if(highscore.size() > 5) highscore.erase(highscore.begin());
            saveScore();
            itoa(score,dummy,10);
            if(finalScore) delete finalScore;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            finalScore = new TextObject(dummy,FinalScoreFont, &ScoreBrown, 900, 535);
        }
    }
    if(GameStatus == InGame){
        if(smacked == true){
            if(smack_count == 0){
                Index = 9;
                score++;
                itoa(score,dummy,10);
                scoreCounter->line[0] = dummy[0];
                scoreCounter->line[1] = dummy[1];
                increase = 1;
                smack_count = 1;
            }
            if(Index == 21){
                interval--;
                increase = 0;
                if(interval < 0){
                    smacked = false;
                    Index = 0;
                    increase = 1;
                    smack_count = 0;
                    seed = RandHole;
                    srand(clock()*FPS_Counter);
                    RandHole = rand() % 8;
                    if(RandHole == seed){
                        RandHole = (3 + RandHole)%8;
                    }
                    interval = (rand()%25) + 5;
                }
            }
        }
        else{
            if(Index==9){
                Index = 8;
                increase = -1;
            }
            if(Index == 0){
                interval--;
                increase = 0;
                if(interval < 0){
                    smack_count = 0;
                    increase = 1;
                    seed = RandHole;
                    srand(FPS_Counter*clock());
                    RandHole = rand() % 8;
                    if(RandHole == seed){
                        RandHole = (RandHole + 3)%8;
                    }
                    interval = (rand()%25) + 5;
                }
            }
        }
        Anya->Update(AnyaLoop[Index],HolePos[RandHole].first, HolePos[RandHole].second, 461,427);
    }
}
void Game::render(){
    SDL_RenderClear(renderer);
    if(GameStatus == MainMenu){
        background->Render();
        whack->Render();
        leaderboard->Render();
        quit->Render();
        Welcome->Render();
        (*Welcome) + change;
        if(Welcome->ypos >= -1) change = 0;
    }
    else if(GameStatus == LeaderBoard){
        leaderboardBG->Render();
        for(int i = 0; i < highscore.size();i++){
            if(LBscore[i])LBscore[i]->Render();
            if(LBscore[i+5])LBscore[i+5]->Render();
        }
    }
    else if(GameStatus == InGame){
        gameBG->Render();
        Anya->Render();
        scoreCounter->Render();
        timeCounter->Render();
        if(FPS_Counter % 2 == 0){
           Index+=increase;
        }
        FPS_Counter++;
    }
    else if(GameStatus == GameOver){
        GameOverBG->Render();
        finalScore->Render();
        if(score ==(* highscore.rbegin()).first) HSsticker->Render();
    }
    else if(GameStatus == NameInput){
        NameInputBG->Render();
        if(textImage != NULL) SDL_RenderCopy(renderer, textImage, &NameSrect,&NameDrect);
    }
    SDL_RenderPresent(renderer);
}
void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    isRunning = false;
    cout << "Window Cleaned" << endl;
}
