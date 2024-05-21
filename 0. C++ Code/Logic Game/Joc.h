#ifndef JOC_H
#define JOC_H
#include <string>
#include <fstream>
#include <iostream>
#include "NodeFigura.h"
#include "NodeMoviments.h"
#include "Tauler.h"




using namespace std;



class Joc
{
public:
	Joc() : m_nextFigures(nullptr) {}

	void inicialitza(const string& nomFitxerTauler, const string& nomFitxerFigures, const string& nomFitxerMoviments, int mode);
	bool giraFigura(DireccioGir direccio);
	int baixaFigura();
	int baixaFiguraComplet();
	bool xocFigura();
	bool mouFigura(int dirX);
	Figura getFigura() { return m_figuraActual; }
	void escriuTauler(const string& nomFitxer);
	void llegeixFitxer(const string& nomFitxer);
	void dibuixa();
	void actualitza(double deltaTime);
	void inicialitzaNovaFigura();
	Tauler getTauler() { return m_tauler; }
	void inicialitzaTauler(string nomFitxer);
	void inicialitzaLlistaFigures(const string& nomFitxerFigures);
	void inicialitzaLlistaMoviments(const string& nomFitxerMoviments);
	void inicialitzaSeguentFigura();

	//Nodes
	void afegeixLlistaFigura(Figura figura);
	void afegeixLlistaMoviment(TipusMoviment moviment);
	nodeMoviment* getMoviment() { return m_nextMoviments; }
	void seguentMoviment() { m_nextMoviments = m_nextMoviments->getNext(); }

private:
	Tauler m_tauler;
	Figura m_figuraActual;
	nodeFigura* m_nextFigures;
	nodeMoviment* m_nextMoviments;

	
};

#endif