//
//  main.cpp
//
//  Copyright � 2018 Compiled Creations Limited. All rights reserved.
//

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined  (_WIN64)

#include <iostream>
//Definicio necesaria per poder incloure la llibreria i que trobi el main
#define SDL_MAIN_HANDLED
#include <windows.h>
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#include <conio.h>      /* getch */ 

#elif __APPLE__
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <SDL2/SDL.h>
#pragma clang diagnostic pop

#endif

#include "./Partida.h"
#include "./InfoJoc.h"
#pragma comment(lib, "Winmm.lib")




int main(int argc, const char* argv[])
{
    int opcio = 0, mode, sortir = 0;
    while (sortir == 0)
    {
        while (opcio == 0)
        {
            cout << "A quina partida vols jugar?" << endl;
            cout << "1. Mode normal" << endl;
            cout << "2. Mode test" << endl;
            cout << "3. Visualitzar llista de millors puntuacions" << endl;
            cout << "4. Sortir del programa" << endl;
            cin >> opcio;
            switch (opcio)
            {
            case 1:
                mode = 0;
                break;
            case 2:
                mode = 1;
                break;
            case 3:
                break;
            case 4:
                mode = 0;
                sortir = 1;
                break;
            }
        }

        //Instruccions necesaries per poder incloure la llibreria i que trobi el main
        if (sortir == 0)
        {
        SDL_SetMainReady();
        SDL_Init(SDL_INIT_VIDEO);

        //Inicialitza un objecte de la classe Screen que s'utilitza per gestionar la finestra grafica
        Screen pantalla(SCREEN_SIZE_X, SCREEN_SIZE_Y);
        //Mostrem la finestra grafica
        pantalla.show();

        Partida game;
        game.inicialitza(mode, "./data/Games/partida.txt", "./data/Games/fitxerFigures.txt", "./data/Games/fitxerMoviments.txt");


        Uint64 NOW = SDL_GetPerformanceCounter();
        Uint64 LAST = 0;
        double deltaTime = 0;
        mciSendString("open \".\\data\\Sounds\\music.mp3\" type mpegvideo alias music", NULL, 0, NULL);
        mciSendString("open \".\\data\\Sounds\\lose.mp3\" type mpegvideo alias lose", NULL, 0, NULL);
        mciSendString("play music repeat", NULL, 0, NULL);
        do
            {
                LAST = NOW;
                NOW = SDL_GetPerformanceCounter();
                deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());

                // Captura tots els events de ratolí i teclat de l'ultim cicle
                pantalla.processEvents();

                game.actualitza(deltaTime);

                // Actualitza la pantalla
                pantalla.update();
                if(game.getEstatPartida() == ACABADA)
                {
                    mciSendString("stop music", NULL, 0, NULL);
                    mciSendString("close music", NULL, 0, NULL);
                    mciSendString("play lose", NULL, 0, NULL);
                }

            } while ((!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE) || game.getEstatPartida() == ENJOC));
            // Sortim del bucle si pressionem ESC
        }
        Sleep(5);
        opcio = 0;
  
    }

    //Instruccio necesaria per alliberar els recursos de la llibreria 
    SDL_Quit();
    return 0;
}

