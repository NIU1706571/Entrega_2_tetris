#ifndef TAULER_H
#define TAULER_H
#include "Figura.h"
#include "GraphicManager.h"

const int MAX_FILA = 21;
const int MAX_COL = 11;

class Tauler
{

public:
	//setters
	void setPosicio(int x, int y, ColorFigura color) { m_posicions[y][x] = color; }

	//getters
	ColorFigura getPosicio(int x, int y) { return m_posicions[y][x]; }
	Figura getFigura();
	void inicialitzaTauler();

	void baixaFigura(int x, int y, Figura& figura);
	bool const comprovaCaiguda(Figura &figura, int pos_x, int pos_y); //comprova si caure 1 cap a avall és vàlid en una figura (1 si ho és, 0 si no)
	void introdueixFigura(int x, int y, Figura figura);
	void borraFigura(int x, int y, Figura figura);
	int comprovaFilaCompleta();
    void baixaFila(int y);
	bool const comprovaMoviment(Figura& figura, int pos_x, int pos_y, int mov);
	void mouFigura(int pos_x, int pos_y, Figura& figura, int mov);
	void escriuTauler();
	bool const comprovaGir(Figura& figura, int pos_x, int pos_y, DireccioGir direccio);
	void dibuixaPeces(); //dibuixa les diferents peces col·locades al tauler


private:
	ColorFigura m_posicions[MAX_FILA][MAX_COL]; //generem el tauler

};

//ifstream& operator>>(ifstream& input, Tauler& tauler);

#endif