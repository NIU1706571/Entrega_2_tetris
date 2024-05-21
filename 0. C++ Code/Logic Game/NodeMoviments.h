#ifndef NODEMOV_H
#define NODEMOV_H
#include <string>
#include <fstream>
#include <iostream>

#include "Figura.h"

using namespace std;

typedef enum
{
	MOVIMENT_ESQUERRA = 0,
	MOVIMENT_DRETA = 1,
	MOVIMENT_GIR_HORARI = 2,
	MOVIMENT_GIR_ANTI_HORARI = 3,
	MOVIMENT_BAIXA = 4,
	MOVIMENT_BAIXA_FINAL = 5,
} TipusMoviment;

class nodeMoviment
{
public:
	nodeMoviment() : m_next(nullptr) {}
	nodeMoviment* getNext() { return m_next; }
	TipusMoviment getMoviment() { return m_tipus; }
	void setUtilitzat(bool utilitzat) { m_utilitzat = utilitzat; }
	TipusMoviment getUtilitzat() { return m_tipus; }
	void setMoviment(TipusMoviment tipus) { m_tipus = tipus; }
	void setNext(nodeMoviment* next) { m_next = next; }


private:
	nodeMoviment* m_next;
	TipusMoviment m_tipus;
	bool m_utilitzat;
};

#endif