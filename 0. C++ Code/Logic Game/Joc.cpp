#include "Joc.h"
#include<windows.h>

void Joc::inicialitzaNovaFigura()
{

	srand(time(NULL));
	int randomTipus = rand() % 7;
	srand(time(NULL));
	int randomRotacio = rand() % 4;
	TipusFigura tipus;
	ColorFigura color;
	
	switch (randomTipus)
	{
	case 1:
		color = COLOR_GROC;
		tipus = FIGURA_O;
		break;

	case 2:
		color = COLOR_BLAUCEL;
		tipus = FIGURA_I;
		break;

	case 3:
		color = COLOR_MAGENTA;
		tipus = FIGURA_T;
		break;

	case 4:
		color = COLOR_TARONJA;
		tipus = FIGURA_L;
		break;

	case 5:
		color = COLOR_BLAUFOSC;
		tipus = FIGURA_J;
		break;

	case 6:
		color = COLOR_VERMELL;
		tipus = FIGURA_Z;
		break;

	case 0:
		color = COLOR_VERD;
		tipus = FIGURA_S;
		break;

	default:
		color = NO_COLOR;
		tipus = NO_FIGURA;
		break;

	}
	int columna = 6, fila = 0;

	Figura novaFigura;
	if (tipus == FIGURA_O)
		randomRotacio = 0;
	novaFigura.setTipus(tipus);
	novaFigura.setRotacio(randomRotacio);
	novaFigura.setMatriuFigura(tipus, randomRotacio);
	novaFigura.setPosicioX(columna);
	novaFigura.setPosicioY(fila);
	novaFigura.setColor(color);
	m_tauler.introdueixFigura(columna, fila, novaFigura);

	m_figuraActual = novaFigura; //canviem la nova figura
}

bool Joc::inicialitzaSeguentFigura()
{
	Figura novaFigura;

	novaFigura = m_nextFigures->getFigura();
	m_nextFigures = m_nextFigures->getNext();

		int fila = novaFigura.getPosicioY(), columna = novaFigura.getPosicioX();
		m_tauler.introdueixFigura(columna, fila, novaFigura);

	m_figuraActual = novaFigura; //canviem la nova figura
	
	if (m_nextFigures != nullptr)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}


void Joc::llegeixFitxer(const string& nomFitxer)
{
	ifstream fitxer;

	fitxer.open(nomFitxer);

	TipusFigura tipus;
	ColorFigura color;
	int fila, columna, rotacio, i_tipus, i_color;

	if (fitxer.is_open())
	{
		int i_color;

		for (int i = 0; i < MAX_FILA; i++) // FILES
		{
			for (int j = 0; j < MAX_COL; j++) // COLUMNES
			{
				fitxer >> i_color;

				cout << i_color << " ";
			}
			cout << endl;
		}
	}
	else
	{
		cout << "Error, fitxer no obert." << endl;
	}

	fitxer.close();
}

void Joc::inicialitzaTauler(string nomFitxer)
{
	ifstream fitxer;

	fitxer.open(nomFitxer);

	TipusFigura tipus;
	ColorFigura color;
	int fila, columna, rotacio, i_tipus, i_color;

	if (fitxer.is_open())
	{
		fitxer >> i_tipus >> fila >> columna >> rotacio;

		switch (i_tipus)
		{
		case 1:
			tipus = FIGURA_O;
			break;

		case 2:
			tipus = FIGURA_I;
			break;

		case 3:
			tipus = FIGURA_T;
			break;

		case 4:
			tipus = FIGURA_L;
			break;

		case 5:
			tipus = FIGURA_J;
			break;

		case 6:
			tipus = FIGURA_Z;
			break;

		case 7:
			tipus = FIGURA_S;
			break;

		}

		m_figuraActual.setTipus(tipus);
		m_figuraActual.setRotacio(rotacio);
		m_figuraActual.setPosicioX(columna - 1);
		m_figuraActual.setPosicioY(fila - 1);
		m_figuraActual.setMatriuFigura(tipus, rotacio);


		ColorFigura color;
		int i_color;


		for (int i = 0; i < MAX_FILA; i++) // FILES
		{
			for (int j = 0; j < MAX_COL; j++) // COLUMNES
			{
				fitxer >> i_color;

				switch (i_color)
				{
				case 0:
					color = NO_COLOR;
					break;

				case 1:
					color = COLOR_GROC;
					break;

				case 2:
					color = COLOR_BLAUCEL;
					break;

				case 3:
					color = COLOR_MAGENTA;
					break;

				case 4:
					color = COLOR_TARONJA;
					break;

				case 5:
					color = COLOR_BLAUFOSC;
					break;

				case 6:
					color = COLOR_VERMELL;
					break;

				case 7:
					color = COLOR_VERD;
					break;

				default:
					color = NO_COLOR;
					break;

				}

				m_tauler.setPosicio(j, i, color);
			}
		}
		m_tauler.introdueixFigura(columna - 1, fila - 1, m_figuraActual);


	}
	else
	{
		cout << "Error, fitxer no obert." << endl;
	}

	fitxer.close();
}

void Joc::inicialitzaLlistaFigures(const string& nomFitxerFigures)
{
	ifstream fitxer;

	fitxer.open(nomFitxerFigures);

	TipusFigura tipus;
	ColorFigura color;
	int fila, columna, rotacio, i_tipus, i_color;
	Figura figuraNova;

	if (fitxer.is_open())
	{

		fitxer >> i_tipus >> fila >> columna >> rotacio;

		while (!fitxer.eof())
		{
			switch (i_tipus)
			{
			case 1:
				tipus = FIGURA_O;
				break;

			case 2:
				tipus = FIGURA_I;
				break;

			case 3:
				tipus = FIGURA_T;
				break;

			case 4:
				tipus = FIGURA_L;
				break;

			case 5:
				tipus = FIGURA_J;
				break;

			case 6:
				tipus = FIGURA_Z;
				break;

			case 7:
				tipus = FIGURA_S;
				break;

			}

			figuraNova.setTipus(tipus);
			figuraNova.setRotacio(rotacio);
			figuraNova.setPosicioX(columna - 1);
			figuraNova.setPosicioY(fila - 1);
			figuraNova.setMatriuFigura(tipus, rotacio);
			afegeixLlistaFigura(figuraNova);

			fitxer >> i_tipus >> fila >> columna >> rotacio; //agafem la nova figura
		}

	}
	else
	{
		cout << "Error, fitxer no obert." << endl;
	}

	fitxer.close();
}

void Joc::inicialitzaLlistaMoviments(const string& nomFitxerMoviments)
{
	ifstream fitxer;

	fitxer.open(nomFitxerMoviments);

	TipusMoviment moviment;
	int i_moviment;

	if (fitxer.is_open())
	{

		fitxer >> i_moviment;

		while (!fitxer.eof())
		{
			switch (i_moviment)
			{
			case 0:
				moviment = MOVIMENT_ESQUERRA;
				break;

			case 1:
				moviment = MOVIMENT_DRETA;
				break;

			case 2:
				moviment = MOVIMENT_GIR_HORARI;
				break;

			case 3:
				moviment = MOVIMENT_GIR_ANTI_HORARI;
				break;

			case 4:
				moviment = MOVIMENT_BAIXA;
				break;

			case 5:
				moviment = MOVIMENT_BAIXA_FINAL;
				break;

			}


			afegeixLlistaMoviment(moviment);

			fitxer >> i_moviment; //agafem la nova figura
		}

	}
	else
	{
		cout << "Error, fitxer no obert." << endl;
	}

	fitxer.close();
}


void Joc::inicialitza(const string& nomFitxerTauler, const string& nomFitxerFigures, const string& nomFitxerMoviments,  int mode)
{
	if (mode == 0)
	{
		m_tauler.inicialitzaTauler();
		inicialitzaNovaFigura();
		

	}
	else
	{
		inicialitzaTauler(nomFitxerTauler);
		inicialitzaLlistaFigures(nomFitxerFigures);
		inicialitzaLlistaMoviments(nomFitxerMoviments);
	}
}



void Joc::escriuTauler(const string& nomFitxer)
{
	ofstream fitxer;
	fitxer.open(nomFitxer);

	if (fitxer.is_open())
	{
		int tipus;
		for (int i = 0; i < MAX_FILA; i++)
		{
			for (int j = 0; j < MAX_COL; j++)
			{
				switch (m_tauler.getPosicio(j, i))
				{
				case NO_COLOR:
					tipus = 0;
					break;

				case COLOR_GROC:
					tipus = 1;
					break;

				case COLOR_BLAUCEL:
					tipus = 2;
					break;

				case COLOR_MAGENTA:
					tipus = 3;
					break;

				case COLOR_TARONJA:
					tipus = 4;
					break;

				case COLOR_BLAUFOSC:
					tipus = 5;
					break;

				case COLOR_VERMELL:
					tipus = 6;
					break;

				case COLOR_VERD:
					tipus = 7;
					break;

				default:
					tipus = NO_COLOR;
					break;

				}

				fitxer << tipus << " ";
			}
			fitxer << endl;
		}
	}
	else
	{
		cout << "Error: fitxer no trobat";
	}

	fitxer.close();
}


int Joc::baixaFigura()
{
	int n_filesCompletades = 0;

	if (m_tauler.comprovaCaiguda(m_figuraActual, m_figuraActual.getPosicioX(), m_figuraActual.getPosicioY()) == 1)
	{
		m_tauler.baixaFigura(m_figuraActual.getPosicioX(), m_figuraActual.getPosicioY(), m_figuraActual);
	}

	//comprovem si hi ha alguna fila ja feta
	for (int i = 0; i < MAX_FILA; i++) //podem tenir un màx de 8 files repetides
	{
		int fila = m_tauler.comprovaFilaCompleta();

		if (fila != -1)
		{
			m_tauler.baixaFila(fila);
			m_figuraActual.setPosicioY(m_figuraActual.getPosicioY() + 1); //també baixa 1 la figura.
			m_figuraActual.borrarFila();
			m_figuraActual.setMaxY(m_figuraActual.getMaxY() - 1);
			n_filesCompletades++;
		}

	}

	return n_filesCompletades;



}

int Joc::baixaFiguraComplet()
{
	int n_filesCompletades = 0;

	while (m_tauler.comprovaCaiguda(m_figuraActual, m_figuraActual.getPosicioX(), m_figuraActual.getPosicioY()) == 1)
	{
		m_tauler.baixaFigura(m_figuraActual.getPosicioX(), m_figuraActual.getPosicioY(), m_figuraActual);
	}

	//comprovem si hi ha alguna fila ja feta
	for (int i = 0; i < MAX_FILA; i++) //podem tenir un màx de 8 files repetides
	{
		int fila = m_tauler.comprovaFilaCompleta();

		if (fila != -1)
		{
			m_tauler.baixaFila(fila);
			m_figuraActual.setPosicioY(m_figuraActual.getPosicioY() + 1); //també baixa 1 la figura.
			m_figuraActual.borrarFila();
			m_figuraActual.setMaxY(m_figuraActual.getMaxY() - 1);
			n_filesCompletades++;
		}

	}

	return n_filesCompletades*100;
}


bool Joc::mouFigura(int dirX)
{


	if (m_tauler.comprovaMoviment(m_figuraActual, m_figuraActual.getPosicioX(), m_figuraActual.getPosicioY(), dirX) == 1)
	{
		m_tauler.mouFigura(m_figuraActual.getPosicioX(), m_figuraActual.getPosicioY(), m_figuraActual, dirX);

		return 1;
	}
	else
	{
		return 0;
	}
}

bool Joc::giraFigura(DireccioGir direccio)
{
	bool comprova = m_tauler.comprovaGir(m_figuraActual, m_figuraActual.getPosicioX(), m_figuraActual.getPosicioY(), direccio);

	if (comprova == 1)
	{
		m_tauler.borraFigura(m_figuraActual.getPosicioX(), m_figuraActual.getPosicioY(), m_figuraActual); //borrem la figura actual  
		m_figuraActual.rotarFigura(direccio);
		m_figuraActual.setMatriuFigura(m_figuraActual.getTipus(), m_figuraActual.getRotacio());
		m_tauler.introdueixFigura(m_figuraActual.getPosicioX(), m_figuraActual.getPosicioY(), m_figuraActual);
		return 1;
	}
	else
	{
		return 0;
	}


}

void Joc::actualitza(double deltaTime)
{
	GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
	GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER, false);
}

void Joc::dibuixa()
{
	GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
	GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER, false);
	m_tauler.dibuixaPeces();





}

bool Joc::xocFigura()
{
	if (m_tauler.comprovaCaiguda(m_figuraActual, m_figuraActual.getPosicioX(), m_figuraActual.getPosicioY()) == 0 && (m_figuraActual.getPosicioY() == 0 || m_figuraActual.getPosicioY() == 1))
	{
		return 1;
		/*
		bool xoca = 0;
		int pos_x = m_figuraActual.getPosicioX();
		int pos_y = m_figuraActual.getPosicioY();
		for (int i = 0; i < m_figuraActual.getMaxX(); i++)
		{
			for (int j = 0; j < m_figuraActual.getMaxY(); j++)
			{
				//cout << m_posicions[pos_y + j][pos_x + i] << endl;
				if ((m_figuraActual.getPosicioMatriu(i, j) != NO_COLOR) && (m_tauler.getPosicio(pos_x + i, pos_y + j) != NO_COLOR))
				{
					xoca = 1;
				}
			}
		}

		if (xoca == 1)
		{
			return 1;
		}
		else
		{
			return 0;
		}
		*/

	}
	else
	{
		return 0;
	}
}



void Joc::afegeixLlistaFigura(Figura figura)
{
	if (m_nextFigures == nullptr) //si no n'hi ha cap
	{
		nodeFigura* newNodeFigura = new nodeFigura;
		Figura newFigura;
		newFigura = figura;

		newNodeFigura->setFigura(newFigura);
		m_nextFigures = newNodeFigura;
		//l'afegim a l'inici
    }
	else
	{
		//iterem fins trobar el nullptr
		bool trobat = false;

		nodeFigura* actual = m_nextFigures;
		while(!trobat)
		{
			if (actual->getNext() != nullptr)
			{
				actual = actual->getNext();
			}
			else
			{
				trobat = 1;
			}
		}

		nodeFigura* newNodeFigura = new nodeFigura;
		Figura newFigura;
		newFigura = figura;

		newNodeFigura->setFigura(newFigura);

		actual->setNext(newNodeFigura);
	}
}

void Joc::afegeixLlistaMoviment(TipusMoviment moviment)
{
	if (m_nextMoviments == nullptr) //si no n'hi ha cap
	{
		nodeMoviment* newNodeMoviment = new nodeMoviment;
		TipusMoviment newMoviment;
		newMoviment = moviment;

		newNodeMoviment->setMoviment(newMoviment);
		m_nextMoviments = newNodeMoviment;
		//l'afegim a l'inici
	}
	else
	{
		//iterem fins trobar el nullptr
		bool trobat = false;

		nodeMoviment* actual = m_nextMoviments;
		while (!trobat)
		{
			if (actual->getNext() != nullptr)
			{
				actual = actual->getNext();
			}
			else
			{
				trobat = 1;
			}
		}

		nodeMoviment* newNodeMoviment = new nodeMoviment;
		TipusMoviment newMoviment;
		newMoviment = moviment;

		newNodeMoviment->setMoviment(newMoviment);

		actual->setNext(newNodeMoviment);
	}
}
