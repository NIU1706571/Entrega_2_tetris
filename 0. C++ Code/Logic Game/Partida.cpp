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
    m_puntuacioActual = 0;
    m_temps = 0;
    m_contadorActual = 1;
    m_estatPartida = ENJOC;
    m_puntuacioAux = 0;

    if (opcio == 1 || opcio == 2) //si està al mode test o mode normal, inicialitza tot
    {
        m_joc.inicialitza(fitxerInicial, fitxerFigures, fitxerMoviments, mode);
    }

    m_endFigures = 0;
    recuperaClassificacio(fitxerClassificacio); //recuperem la classificació del fitxer

}

void Partida::actualitza(double deltaTime)
{
    int puntuacioAux = 0;
    bool space = 0;
    if (m_estatPartida == ENJOC) //quan no s'hagi acabat la partida
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
            else if (Keyboard_GetKeyTrg(KEYBOARD_UP) || Keyboard_GetKeyTrg(KEYBOARD_W))
            {
                m_joc.giraFigura(GIR_HORARI);
            }
            else if (Keyboard_GetKeyTrg(KEYBOARD_DOWN) || Keyboard_GetKeyTrg(KEYBOARD_S))
            {
                m_joc.giraFigura(GIR_ANTI_HORARI);
            }
            else if (Keyboard_GetKeyTrg(KEYBOARD_SPACE) || Keyboard_GetKeyTrg(KEYBOARD_E))
            {
                puntuacioAux += 10*m_joc.baixaFiguraComplet();
                puntuacioAux += 10;
                m_puntuacioAux += puntuacioAux;
                m_puntuacioActual += puntuacioAux;
                space = 1;
            }
            else if (Keyboard_GetKeyTrg(KEYBOARD_ESCAPE))
            {
                m_estatPartida = ACABADA;
            }
            else if (m_temps > 1)
            {
                puntuacioAux += 10*m_joc.baixaFigura();
                m_puntuacioAux += puntuacioAux;
                m_puntuacioActual += puntuacioAux;
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

                puntuacioAux += 10 * m_joc.comprovaIBorraFiles();
                if (space == 0)
                {
                    m_puntuacioAux += puntuacioAux + 10;
                    m_puntuacioActual += puntuacioAux;
                }

                m_joc.inicialitzaNovaFigura();
                
            }
            

            if (m_puntuacioAux >= 100)
            {
                m_nivell++;
                m_puntuacioAux = 0;
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

                    if (mov_actual == nullptr && m_endFigures == 1 || mov_actual == nullptr)
                    {
                        m_movimentFinal = 1; // si ja no hi ha més moviments posem final = 1 per acabar amb el bucle al final de la partida
                        m_estatPartida = ACABADA; //i acabem la partida
                        cout << "Partida test finalitzada" << endl;
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
                            puntuacioAux += 10 * m_joc.baixaFigura();
                            m_puntuacioAux += puntuacioAux;
                            m_puntuacioActual += puntuacioAux;
                            break;

                        case MOVIMENT_BAIXA_FINAL:
                            puntuacioAux += 10 * m_joc.baixaFiguraComplet();
                            puntuacioAux += 10;
                            m_puntuacioAux += puntuacioAux;
                            m_puntuacioActual += puntuacioAux;
                            space = 1;
                            break;

                        }

                        m_joc.seguentMoviment();

                        Figura figura_actual = m_joc.getFigura();
                        if (m_joc.xocFigura() == 1 || Keyboard_GetKeyTrg(KEYBOARD_ESCAPE))
                        {
                            m_estatPartida = ACABADA;
                        }
                        else if (m_joc.getTauler().comprovaCaiguda(figura_actual, figura_actual.getPosicioX(), figura_actual.getPosicioY()) == 0 && m_endFigures == 0)
                        {
                            puntuacioAux += 10 * m_joc.comprovaIBorraFiles();
                            if (space == 0)
                            {
                                m_puntuacioAux += puntuacioAux + 10;
                                m_puntuacioActual += puntuacioAux;
                            }
                            m_endFigures = m_joc.inicialitzaSeguentFigura();
                        }


                        if (m_puntuacioAux >= 100)
                        {
                            m_nivell++;
                            m_puntuacioAux = 0;
                        }
                    }

                    m_temps = 0;
                }

            }
        }

    }
    m_joc.dibuixa();
    string msg = "Puntuacio:" + to_string(m_puntuacioActual) + " Nivell:" + to_string(m_nivell);
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
        m_classificacio.clear(); //si està buida (nom = classificacio i puntuació = 0) hem de borrar-la abans.
    }

    if (m_classificacio.empty())
    {
        Classificacio newClas(nom, m_puntuacioActual);
        m_classificacio.push_front(newClas); //si està buida ho posem al principi
    }
    else
    {
        while (actual != ultim && !trobat)
        {
            if (actual->getPuntuacio() > m_puntuacioActual) //sinó busquem la posició on ha d'anar
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

