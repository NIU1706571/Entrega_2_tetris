#ifndef NODEFIG_H
#define NODEFIG_H
#include <string>
#include <fstream>
#include <iostream>

#include "Figura.h"

using namespace std;
class nodeFigura
{
public:
	nodeFigura() : m_next(nullptr) {}
	nodeFigura* getNext() { return m_next; }
	Figura getFigura() { return m_figura; }
	void setUtilitzat(bool utilitzat) { m_utilitzat = utilitzat; }
	bool getUtilitzat() { return m_utilitzat; }
	void setFigura(Figura figura) { m_figura = figura; }
	void setNext(nodeFigura* next) { m_next = next; }


private:
	nodeFigura* m_next;
	Figura m_figura;
	int m_nFigures;
	bool m_utilitzat;
};

#endif