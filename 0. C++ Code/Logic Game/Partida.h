#ifndef PARTIDA_H
#define PARTIDA_H

#include <stdio.h>
#include <string>
#include "Joc.h"
#include "GraphicManager.h"
#include "InfoJoc.h"
#include <windows.h>

using namespace std;

typedef enum
{
    ENJOC = 0,
    ACABADA
}EstatPartida;

class Partida 
{
public:
    Partida();
    void inicialitza(int mode, const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments);
    void actualitza(double deltaTime);
    int getMode() { return m_modeJoc; }
    EstatPartida getEstatPartida() { return m_estatPartida; }
private:
    double m_temps;
    double deltaTime;
    int m_nivell;
    int m_modeJoc;
    int m_puntuacioActual;
    int m_contadorActual;;
    string m_fitxer;
    Joc m_joc;
    bool m_partidaIniciada;
    float m_velocitat;
    EstatPartida m_estatPartida;
    bool m_movimentFinal;

};

#endif 
