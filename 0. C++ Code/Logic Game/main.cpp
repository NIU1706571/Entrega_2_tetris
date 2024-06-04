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

void configuracio(bool& musicaMute, string fitxer, bool &esborrarClas)
{
   
    cout <<  endl << "-- TETRIS --" << endl;
    cout << "== CONFIGURACIO ==" << endl;
    cout << "1. Mutejar / desmutejar musica" << endl;
    cout << "2. Reiniciar classificacio" << endl;
    cout << "3. Tornar enrere" << endl;


    int opcio;

    cin >> opcio;
    switch (opcio)
    {
    case 1:
        if (musicaMute == 1)
        {
            musicaMute = 0;
            cout << "Exit! Ara ja s'escoltara el so del joc." << endl;
        }
        else
        {
            musicaMute = 1;
            cout << "Exit! Ara ja no s'escoltara el so del joc." << endl;

        }
        break;

    case 2:
        cout << "Segur que vols reiniciar la classificacio?  (1 = Si, 2 = No)" << endl;
        int confirm;
        cin >> confirm;

        if (confirm == 1)
        {
            esborrarClas = 1;
            cout << "Exit! Classificacio borrada correctament." << endl;
        }
        else if (confirm == 2)
        {
            esborrarClas = 0;
            cout << "Clasificacio no borrada." << endl;
        }
        else
        {
            cout << "Error, no s'ha confirmat." << endl;
        }
    default:
        break;
    }

    cout << endl;

}

void menu(int &opcio, int &mode, int &sortir, string &fitxerFigures, string &fitxerMoviment,string &fitxerPartida, bool &musicaMute, bool &esborrarClas)
{
    cout << "-- TETRIS --" << endl;
    cout << "== MENU PRINCIPAL ==" << endl;
    cout << "1. Mode normal" << endl;
    cout << "2. Mode test" << endl;
    cout << "3. Visualitzar llista de millors puntuacions" << endl;
    cout << "4. Configuracio" << endl;
    cout << "5. Sortir del programa" << endl;

    while (opcio == 0)
    {
        cin >> opcio;
        switch (opcio)
        {
        case 1:
            mode = 0;
            break;
        case 2:
            mode = 1;
            cout << "Nom del fitxer amb l'estat inicial del tauler: ";
            cin >> fitxerPartida;
            cout << endl << "Nom del fitxer amb la sequencia de figures: ";
            cin >> fitxerFigures;
            cout << endl << "Nom del fitxer amb la sequencia de moviments: ";
            cin >> fitxerMoviment;
            cout << endl;

            break;
        case 3:
            break;

        case 4:
            configuracio(musicaMute, "./data/Games/fitxerClassificacio.txt", esborrarClas);
            break;


        case 5:
            mode = 0;
            sortir = 1;
            break;
        }
    }

    cout << endl;
}


int main(int argc, const char* argv[])
{
    int opcio = 0, mode, sortir = 0;
    string fitxerPartida, fitxerFigures, fitxerMoviments;
    bool musicaMute = 0, esborrarClas = 0;
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);
    //Inicialitza un objecte de la classe Screen que s'utilitza per gestionar la finestra grafica
     //Mostrem la finestra grafica
    Screen pantalla(SCREEN_SIZE_X, SCREEN_SIZE_Y);

    while (sortir == 0)
    {

        menu(opcio, mode, sortir, fitxerFigures, fitxerMoviments, fitxerPartida, musicaMute, esborrarClas);

        //Instruccions necesaries per poder incloure la llibreria i que trobi el main

        if (sortir == 0)
        {
        Partida game;
        //game.inicialitza(mode, "./data/Games/partida.txt", "./data/Games/fitxerFigures.txt", "./data/Games/fitxerMoviments.txt", "./data/Games/fitxerClassificacio.txt", opcio);
        game.inicialitza(mode, fitxerPartida, fitxerFigures, fitxerMoviments, "./data/Games/fitxerClassificacio.txt", opcio);

        if (opcio == 3)
        {
            game.mostraClassificacio();
        }
        else if (opcio == 4 && esborrarClas == 1)
        {
            game.esborrarClassificacio();
            esborrarClas = 0;
        }
        else if (opcio == 2 || opcio == 1)
        {
            pantalla.show();
            Uint64 NOW = SDL_GetPerformanceCounter();
            Uint64 LAST = 0;
            double deltaTime = 0;
            if (musicaMute == 0)
            {
                mciSendString("open \".\\data\\Sounds\\music.mp3\" type mpegvideo alias music", NULL, 0, NULL);
                mciSendString("open \".\\data\\Sounds\\lose.mp3\" type mpegvideo alias lose", NULL, 0, NULL);
                mciSendString("play music repeat", NULL, 0, NULL);
            }
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

                if (game.getEstatPartida() == ACABADA)
                {
                    if (musicaMute == 0)
                    {
                        mciSendString("stop music", NULL, 0, NULL);
                        mciSendString("close music", NULL, 0, NULL);
                        mciSendString("play lose", NULL, 0, NULL);
                    }

                    if (game.getMode() == 0) //mode normal
                    {
                        game.afegeixClassificacio();
                        game.guardarClassificacio("./data/Games/fitxerClassificacio.txt");
                    }
                }

            } while ((!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE) && game.getEstatPartida() == ENJOC));
            // Sortim del bucle si pressionem ESC
        }
        }
        opcio = 0;
 
        
  
    }

    //Instruccio necesaria per alliberar els recursos de la llibreria 
    SDL_Quit();
    return 0;
}

