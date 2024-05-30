#include "Partida.h"
#include "InfoJoc.h"
#include "GraphicManager.h"
#include <windows.h>
#include <fstream>

Partida::Partida()
{
    m_partidaIniciada = 0;
    m_movimentFinal = 0;
    /*
    m_temps = 0;
    for (int i = 0; i < MIDA; i++)
        for (int j = 0; j < MIDA; j++)
            m_forma[i][j] = NO_COLOR;
    m_forma[0][0] = COLOR_BLAUFOSC;
    m_forma[1][0] = COLOR_BLAUFOSC;
    m_forma[1][1] = COLOR_BLAUFOSC;
    m_forma[1][2] = COLOR_BLAUFOSC;
    m_fila = 1;
    m_columna = 5;
    */
}

void Partida::esborrarClassificacio()
{
    m_classificacio.clear();
    guardarClassificacio("./data/Games/fitxerClassificacio.txt");

}

void Partida::inicialitza(int mode, const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments, const string& fitxerClassificacio, int opcio)
{
    m_modeJoc = mode;
    m_nivell = 1;
    m_puntuacioActual = 1;
    m_temps = 0;
    m_contadorActual = 1;
    m_estatPartida = ENJOC;

    if (opcio == 1 || opcio == 2)
    {
        m_joc.inicialitza(fitxerInicial, fitxerFigures, fitxerMoviments, mode);
    }
    m_endFigures = 0;
    recuperaClassificacio(fitxerClassificacio);

}

void Partida::actualitza(double deltaTime)
{
    if (m_estatPartida == ENJOC)
    {
        if (m_modeJoc == 0) // mode normal
        {
            m_temps += deltaTime * pow(1.1, m_nivell);
            if (Keyboard_GetKeyTrg(KEYBOARD_RIGHT) || Keyboard_GetKeyTrg(KEYBOARD_D))
            {
                m_joc.mouFigura(1);
            }
            else if (Keyboard_GetKeyTrg(KEYBOARD_LEFT) || Keyboard_GetKeyTrg(KEYBOARD_A))
            {
                m_joc.mouFigura(-1);
            }
            else if (Keyboard_GetKeyTrg(KEYBOARD_UP) || Keyboard_GetKeyTrg(KEYBOARD_E))
            {
                m_joc.giraFigura(GIR_HORARI);
            }
            else if (Keyboard_GetKeyTrg(KEYBOARD_DOWN) || Keyboard_GetKeyTrg(KEYBOARD_S))
            {
                m_joc.giraFigura(GIR_ANTI_HORARI);
            }
            else if (Keyboard_GetKeyTrg(KEYBOARD_SPACE) || Keyboard_GetKeyTrg(KEYBOARD_E))
            {
                m_puntuacioActual += m_joc.baixaFiguraComplet();
                m_puntuacioActual += 10;
            }
            else if (Keyboard_GetKeyTrg(KEYBOARD_ESCAPE))
            {
                m_estatPartida = ACABADA;
            }
            else if (m_temps > 1)
            {
                m_puntuacioActual += m_joc.baixaFigura();
                m_temps = 0;
            }
            Figura figura_actual = m_joc.getFigura();
            // cout << "POS X: " << figura_actual.getPosicioX() << " POS Y: " << figura_actual.getPosicioY() << endl;


            if (m_joc.xocFigura() == 1)
            {
                m_estatPartida = ACABADA;
            }
            else if (m_joc.getTauler().comprovaCaiguda(figura_actual, figura_actual.getPosicioX(), figura_actual.getPosicioY()) == 0)
            {
                m_joc.inicialitzaNovaFigura();
            }
            

            if (m_puntuacioActual % 3 == 0)
            {
                m_nivell++;
                m_puntuacioActual++;
            }



        }
        else // mode test
        {

            nodeMoviment* mov_actual = m_joc.getMoviment();
            
            if (m_movimentFinal == 0)
            {
                m_temps += deltaTime * pow(1.1, m_nivell);
                if (m_temps > 1)
                {

                    if (mov_actual == nullptr && m_endFigures == 1)
                    {
                        m_movimentFinal = 1; // si ja no hi ha més moviments posem final = 1 per acabar amb el bucle al final de la partida
                        m_estatPartida = ACABADA; //i acabem la partida
                    }
                    else
                    {
                        switch (mov_actual->getMoviment())
                        {
                        case MOVIMENT_ESQUERRA:
                            m_joc.mouFigura(-1);
                            break;

                        case MOVIMENT_DRETA:
                            m_joc.mouFigura(1);
                            break;

                        case MOVIMENT_GIR_HORARI:
                            m_joc.giraFigura(GIR_HORARI);
                            break;

                        case MOVIMENT_GIR_ANTI_HORARI:
                            m_joc.giraFigura(GIR_ANTI_HORARI);

                            break;

                        case MOVIMENT_BAIXA:
                            m_puntuacioActual += m_joc.baixaFigura();
                            break;

                        case MOVIMENT_BAIXA_FINAL:
                            m_puntuacioActual += m_joc.baixaFiguraComplet();
                            m_puntuacioActual += 10;
                            break;

                        }

                        m_joc.seguentMoviment();

                        Figura figura_actual = m_joc.getFigura();
                        if (m_joc.xocFigura() == 1)
                        {
                            m_estatPartida = ACABADA;
                        }
                        else if (m_joc.getTauler().comprovaCaiguda(figura_actual, figura_actual.getPosicioX(), figura_actual.getPosicioY()) == 0 && m_endFigures == 0)
                        {
                            m_endFigures = m_joc.inicialitzaSeguentFigura();
                        }


                        if (m_puntuacioActual % 3 == 0)
                        {
                            m_nivell++;
                            m_puntuacioActual++;
                        }
                    }

                    m_temps = 0;
                }

            }
        }

    }
    m_joc.dibuixa();
    string msg = "Puntuació:" + to_string(m_puntuacioActual) + " Nivell:" + to_string(m_estatPartida);
    GraphicManager::getInstance()->drawFont(FONT_GREEN_30, POS_X_TAULER, POS_Y_TAULER - 90, 1.0, msg);



}



void Partida::afegeixClassificacio()
{
    string nom;
    cout << "Nom del jugador: ";
    cin >> nom;

    //busquem a quina posició ha de ser-hi:
    bool trobat = false;

    auto
        actual = m_classificacio.begin();
    auto
        ultim = m_classificacio.end();
    
    if (m_classificacio.begin()->getNom() == "Classificacio" && m_classificacio.begin()->getPuntuacio() == 0)
    {
        m_classificacio.clear();
    }
    if (m_classificacio.empty())
    {
        Classificacio newClas(nom, m_puntuacioActual);
        m_classificacio.push_front(newClas);
    }
    else
    {
        while (actual != ultim && !trobat)
        {
            if (actual->getPuntuacio() > m_puntuacioActual)
            {
                trobat = true;
            }
            else
            {
                actual++;
            }
        }

        if (trobat == true)
        {
            Classificacio newClass(nom, m_puntuacioActual);
            m_classificacio.insert(actual, newClass);
        }
        else
        {
            Classificacio newClass(nom, m_puntuacioActual);
            m_classificacio.push_back(newClass);
        }
    }
}

void Partida::mostraClassificacio()
{

    auto
        actual = m_classificacio.rbegin();
    auto
        final = m_classificacio.rend();

    int contador = 1;

    cout << "== Classificacio ==" << endl;
    do {
        cout << contador << ". " << actual->getNom() << " " << actual->getPuntuacio() << endl;
        actual++;
        contador++;
    } while (actual != final && contador <= 10);
    cout << endl;
}


void Partida::guardarClassificacio(string fitxerIn)
{
    ofstream fitxer;
    fitxer.open(fitxerIn);
    
    if (fitxer.is_open())
    {
        if (m_classificacio.empty() == false)
        {
            auto
                actual = m_classificacio.begin();
            auto
                final = m_classificacio.end();

            do {
                fitxer << actual->getNom() << " " << actual->getPuntuacio() << endl;
                actual++;
            } while (actual != final);
        }
        else
        {
            fitxer << "Classificacio " << " " << 0 << endl;
        }
    }
    else
    {
        cout << "ERROR: No s'ha pogut obrir el fitxer de classificacio" << endl;
    }
}

void Partida::recuperaClassificacio(string fitxerIn)
{
    ifstream fitxer;
    fitxer.open(fitxerIn);

    if (fitxer.is_open())
    {
        string nom;
        int puntuacio;

        fitxer >> nom;
        while (!fitxer.eof())
        {
            fitxer >> puntuacio;
            Classificacio clas(nom, puntuacio);
            m_classificacio.push_back(clas);
            fitxer >> nom;
        }
    }
    else
    {
        cout << "ERROR: No s'ha pogut obrir el fitxer de classificacio" << endl;
    }
}

