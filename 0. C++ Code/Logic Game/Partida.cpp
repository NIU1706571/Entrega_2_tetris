#include "Partida.h"
#include "InfoJoc.h"
#include "GraphicManager.h"
#include<windows.h>

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

void Partida::inicialitza(int mode, const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments)
{
    m_modeJoc = mode;
    m_nivell = 1;
    m_puntuacioActual = 1;
    m_temps = 0;
    m_contadorActual = 1;
    m_estatPartida = ENJOC;
    m_joc.inicialitza(fitxerInicial, fitxerFigures, fitxerMoviments, mode);

}

void Partida::actualitza(double deltaTime)
{
    if (m_estatPartida == ENJOC)
    {
        if (m_modeJoc == 0) // mode normal
        {
            m_temps += 0.00100 * pow(1.1, m_nivell);
            if (Keyboard_GetKeyTrg(KEYBOARD_RIGHT))
            {
                m_joc.mouFigura(1);
            }
            else if (Keyboard_GetKeyTrg(KEYBOARD_LEFT))
            {
                m_joc.mouFigura(-1);
            }
            else if (Keyboard_GetKeyTrg(KEYBOARD_UP))
            {
                m_joc.giraFigura(GIR_HORARI);
            }
            else if (Keyboard_GetKeyTrg(KEYBOARD_DOWN))
            {
                m_joc.giraFigura(GIR_ANTI_HORARI);
            }
            else if (Keyboard_GetKeyTrg(KEYBOARD_SPACE))
            {
                m_puntuacioActual += m_joc.baixaFiguraComplet();
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
                if (mov_actual->getNext() == nullptr)
                {
                    m_movimentFinal = 1; // si ja no hi ha més moviments posem final = 1 per acabar amb el bucle al final de la partida
                }
                else
                {
                    switch (mov_actual -> getMoviment())
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
                        break;

                    }

                    m_joc.seguentMoviment();

                    Figura figura_actual = m_joc.getFigura();
                    if (m_joc.xocFigura() == 1)
                    {
                        m_estatPartida = ACABADA;
                    }
                    else if (m_joc.getTauler().comprovaCaiguda(figura_actual, figura_actual.getPosicioX(), figura_actual.getPosicioY()) == 0)
                    {
                        m_joc.inicialitzaSeguentFigura();
                    }


                    if (m_puntuacioActual % 3 == 0 )
                    {
                        m_nivell++;
                        m_puntuacioActual++;
                    }
                }

            }
        }

    }
    m_joc.dibuixa();
    string msg = "Puntuació:" + to_string(m_puntuacioActual) + " Nivell:" + to_string(m_nivell);
    GraphicManager::getInstance()->drawFont(FONT_GREEN_30, POS_X_TAULER, POS_Y_TAULER - 90, 1.0, msg);



}

