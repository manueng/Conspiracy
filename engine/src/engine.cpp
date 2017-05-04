#include "engine.hpp"
#include "sprite.hpp"
#include "scene_manager.hpp"
#include "input_manager.hpp"
#include "game_object.hpp"
#include "animation.hpp"
#include <vector>
#include <iostream>

namespace engine{

    const std::string GAME_NAME = "Default";
    const std::pair <int, int> WINDOW_SIZE (800, 600);

    SceneManager* sceneManager;
    WindowManager* windowManager;
    SDLManager* sdlManager;
    double startTime;
    double stepTime;
    double timeElapsed;
    double frameTime;
    double frameRate = 60.0;

    void loadEngine(){
        sceneManager = new SceneManager();
        windowManager = new WindowManager();
        sdlManager = new SDLManager();
        startTime = SDL_GetTicks();
        stepTime = startTime;
        frameTime = 1000.0/frameRate;
    }

    void run(){
        bool isRunning = true;
        if(!sdlManager->initSDL()){
            ERROR("ERRO AO INICIAR SDL");
            exit(-1);
        }else if(!windowManager->createWindow(GAME_NAME, WINDOW_SIZE)){
            ERROR("ERRO AO CRIAR JANELA");
            exit(-1);
        }
///////////////////////////////////TODO switch to main //////////////////////////////////////////////////////////
        engine::Animation animation("assets/sprites/bomberman2.png", 4, 9, 1.0);
        animation.init();
        int x=0, y=0, actual = 1;;
        animation.update(0,0);
/////////////////////////////////////////////////////////////////////////////////////////////////
        SDL_Event event;

        while(isRunning){

            engine::InputManager::instance.update(event);
            SDL_RenderClear(WindowManager::getGameCanvas());

            if(engine::InputManager::instance.getQuitRequest()){
                isRunning = false;
                sdlManager->finalizeSDL();
                windowManager->destroyWindow();
            }
            ///////////////////////////////////TODO switch to main //////////////////////////////////////////////////////////
                if(engine::InputManager::instance.isKeyPressed(engine::InputManager::KeyPress::KEY_PRESS_RIGHT) && actual == 1){
                    x+=2;
                    animation.setInterval(27,35);
                }
                else if(engine::InputManager::instance.isKeyPressed(engine::InputManager::KeyPress::KEY_PRESS_LEFT) && actual == 1){
                    x-=2;
                    animation.setInterval(9,17);
                }

                else if(engine::InputManager::instance.isKeyPressed(engine::InputManager::KeyPress::KEY_PRESS_UP)  && actual == 1){
                    y-=2;
                    animation.setInterval(0,8);
                }

                else if(engine::InputManager::instance.isKeyPressed(engine::InputManager::KeyPress::KEY_PRESS_DOWN)  && actual == 1){
                    y+=2;
                    animation.setInterval(18,26);
                }
                else {
                    std::pair <int, int> interval = animation.getInterval();
                    animation.setInterval(interval.first,interval.first);
                }

            animation.update(x,y);
            animation.draw();
            ///////////////////////////////////////////////////////////////////////////
            SDL_RenderPresent(WindowManager::getGameCanvas());

            if(sceneManager->getCurrentScene() != NULL){
                sceneManager->getCurrentScene()->update(timeElapsed);
                sceneManager->getCurrentScene()->draw();
            }

            timeElapsed = SDL_GetTicks() - stepTime;
            if(frameTime > timeElapsed){
                SDL_Delay(frameTime - timeElapsed);
            }
            stepTime = SDL_GetTicks();
        }
    }
}
