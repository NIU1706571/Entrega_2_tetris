#ifndef CLASS_H
#define CLASS_H
#include <string>
#include <fstream>
#include <iostream>


using namespace std;

class Classificacio
{
public:
	Classificacio() : m_nom(""), m_puntuacio(0) {}
	Classificacio(string nom, int puntuacio) { m_nom = nom; m_puntuacio = puntuacio; }
	string getNom() { return m_nom; }
	int getPuntuacio() { return m_puntuacio; }
	void setNom(string nom) { m_nom = nom; }
	void setPuntuacio(int puntuacio) { m_puntuacio = puntuacio; }


private:
	string m_nom;
	int m_puntuacio;
};

#endif