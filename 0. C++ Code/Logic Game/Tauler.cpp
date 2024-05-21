#include "Tauler.h"
#include <iostream>
using namespace std;

void Tauler::inicialitzaTauler()
{
	for (int i = 0; i < MAX_FILA; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			m_posicions[i][j] = NO_COLOR;
		}
	}
}

void Tauler::introdueixFigura(int x, int y, Figura figura)
{

	int y_actual = y;
	for (int i = 0; i < figura.getMaxY(); i++)
	{
		int x_actual = x;
		for (int j = 0; j < figura.getMaxX(); j++)
		{
			if (figura.getPosicioMatriu(j, i) != NO_COLOR)
			{
				m_posicions[y_actual][x_actual] = figura.getPosicioMatriu(j, i);
			}
			x_actual++;

		}
		y_actual++;
	}

}

void Tauler::borraFigura(int x, int y, Figura figura)
{

	int y_actual = y;
	for (int i = 0; i < figura.getMaxY(); i++)
	{
		int x_actual = x;
		for (int j = 0; j < figura.getMaxX(); j++)
		{
			if (figura.getPosicioMatriu(j, i) != NO_COLOR)
			{
				m_posicions[y_actual][x_actual] = NO_COLOR;
			}
			x_actual++;

		}
		y_actual++;
	}

}

bool const Tauler::comprovaCaiguda(Figura& figura, int pos_x, int pos_y)
{

	bool potCaure = 1; //comprovarem si pot caure, si és igual a 1 si ho pot.
	if ((figura.getTipus() == FIGURA_O && figura.getPosicioY() > (MAX_FILA - 1)) || (figura.getRotacio() == 0 && figura.getPosicioY() + 2 > (MAX_FILA - 1)) || (figura.getRotacio() == 1 && figura.getPosicioY() + 3 > (MAX_FILA - 1) && figura.getTipus()!=FIGURA_I) || (figura.getRotacio() == 1 && figura.getPosicioY() + 4 > (MAX_FILA - 1) && figura.getTipus() == FIGURA_I) || (figura.getRotacio() == 2 && figura.getPosicioY() + 3 > (MAX_FILA - 1)) || (figura.getRotacio() == 3 && figura.getPosicioY() + 3 > (MAX_FILA - 1) && figura.getTipus()!= FIGURA_I) || (figura.getRotacio() == 3 && figura.getPosicioY() + 4 > (MAX_FILA - 1) && figura.getTipus() == FIGURA_I))
	{
		potCaure = 0;
	}
	else
	{
		for (int i = 0; i < figura.getMaxX(); i++)
		{
			bool trobatY = 0;
				int j = figura.getMaxY() - 1;
				while (j >= 0 && trobatY == 0)
				{
					if (figura.getPosicioMatriu(i, j) != NO_COLOR)
					{
						int pos = pos_y + j;
							if (m_posicions[pos_y + j + 1][pos_x + i] != NO_COLOR)
							{
								potCaure = 0;
							}
							else
							{
								trobatY = 1;
							}
					}
					j--;
				}
		}
	}


	/*if (potCaure == 1)
	{
		cout << endl << "La figura pot caure!!!!!!!" << endl;
}
	else
	{
		cout << endl << "La figura NO POT CAURE" << endl;
	} */
	return potCaure;


}

void Tauler::baixaFigura(int x, int y, Figura& figura)
{

	int y_actual = y;
	for (int i = 0; i < figura.getMaxY(); i++) //esborrem la figura actual
	{
		int x_actual = x;
		for (int j = 0; j < figura.getMaxX(); j++)
		{
			if (figura.getPosicioMatriu(j, i) != NO_COLOR)
			{
				m_posicions[y_actual][x_actual] = NO_COLOR;
			}
			x_actual++;
		}
		y_actual++;
	}

	y_actual = y + 1;
	for (int i = 0; i < figura.getMaxY(); i++) //i la posem una més avall
	{
		int x_actual = x;
		for (int j = 0; j < figura.getMaxX(); j++)
		{
			if (figura.getPosicioMatriu(j, i) != NO_COLOR)
			{
				m_posicions[y_actual][x_actual] = figura.getPosicioMatriu(j, i);
			}
			x_actual++;

		}
		y_actual++;
	}

	figura.setPosicioY((figura.getPosicioY() + 1));

}

void Tauler::mouFigura(int x, int y, Figura& figura, int mov)
{
	if (mov == 1) //moviment a la dreta
	{
		int y_actual = y;
		for (int i = 0; i < figura.getMaxY(); i++) //esborrem la figura actual
		{
			int x_actual = x;
			for (int j = 0; j < figura.getMaxX(); j++)
			{
				if (figura.getPosicioMatriu(j, i) != NO_COLOR)
				{
					m_posicions[y_actual][x_actual] = NO_COLOR;
				}
				x_actual++;
			}
			y_actual++;
		}

		y_actual = y;
		for (int i = 0; i < figura.getMaxY(); i++) //i la posem una més avall
		{
			int x_actual = x + 1;
			for (int j = 0; j < figura.getMaxX(); j++)
			{
				if (figura.getPosicioMatriu(j, i) != NO_COLOR)
				{
					m_posicions[y_actual][x_actual] = figura.getPosicioMatriu(j, i);
				}
				x_actual++;

			}
			y_actual++;
		}
		figura.setPosicioX((figura.getPosicioX() + 1));
	}
	else
	{
		int y_actual = y;
		for (int i = 0; i < figura.getMaxY(); i++) //esborrem la figura actual
		{
			int x_actual = x;
			for (int j = 0; j < figura.getMaxX(); j++)
			{
				if (figura.getPosicioMatriu(j, i) != NO_COLOR)
				{
					m_posicions[y_actual][x_actual] = NO_COLOR;
				}
				x_actual++;
			}
			y_actual++;
		}

		y_actual = y;
		for (int i = 0; i < figura.getMaxY(); i++) //i la posem una més avall
		{
			int x_actual = x - 1;
			for (int j = 0; j < figura.getMaxX(); j++)
			{
				if (figura.getPosicioMatriu(j, i) != NO_COLOR)
				{
					m_posicions[y_actual][x_actual] = figura.getPosicioMatriu(j, i);
				}
				x_actual++;

			}
			y_actual++;
		}
		figura.setPosicioX((figura.getPosicioX() - 1));
	}
}



bool const Tauler::comprovaMoviment(Figura& figura, int pos_x, int pos_y, int mov)
{

	bool potMoure = 1; //comprovarem si pot caure, si és igual a 1 si ho pot.

	if (mov == 1) //moviment cap a la dreta
	{

		int j;

		if (figura.getRotacio() == 3 && figura.getTipus() != 2 || figura.getRotacio() == 1 && figura.getTipus() == 2)
		{
			j = figura.getMaxX() - 2;
		}
		else if (figura.getRotacio() == 3 && figura.getTipus() == 2)
		{
			j = figura.getMaxX() - 3;
		}
		else if (figura.getTipus() == 1)
		{
			j = figura.getMaxX();
		}
		else
		{
			j = figura.getMaxX() - 1;
		}

		for (int i = 0; i < figura.getMaxY(); i++)
		{
			bool trobatX = 0;
			int k = j;
			while (k >= 0 && trobatX == 0)
			{
				if (figura.getPosicioMatriu(k, i) != NO_COLOR)
				{
					int pos = pos_y + k;
					//cout << m_posicions[pos_y + i][pos_x + k + 1] << endl;
					if ((m_posicions[pos_y + i][pos_x + k + 1] != NO_COLOR) || (pos_x + k + 1 >= MAX_COL))
					{
						potMoure = 0;
					}
					else
					{
						trobatX = 1;
					}
				}
				k--;
			}
		}

	}
	else if (mov == -1)
	{

		for (int i = 0; i < figura.getMaxY(); i++)
		{
			bool trobatX = 0;
			int j;
			if ((figura.getRotacio() == 1 && figura.getTipus() != FIGURA_I && figura.getTipus() != FIGURA_O) || (figura.getRotacio() == 3 && figura.getTipus() == FIGURA_I))
			{
				j = 1;
			}
			else if (figura.getRotacio() == 1 && figura.getTipus() == FIGURA_I)
			{
				j = 2;
			}
			else
			{
				j = 0;
			}

			while (j < figura.getMaxX() && trobatX == 0)
			{
				if (figura.getPosicioMatriu(j, i) != NO_COLOR)
				{
					int pos = pos_y + i;
					if (m_posicions[pos_y + i][pos_x + j - 1] != NO_COLOR || pos_x + j - 1 < 0)
					{
						potMoure = 0;
					}
					else
					{
						trobatX = 1;
					}
				}
				j++;
			}
		}

	}
	/*if (potCaure == 1)
	{
		cout << endl << "La figura pot caure!!!!!!!" << endl;
}
	else
	{
		cout << endl << "La figura NO POT CAURE" << endl;
	} */
	return potMoure;


}







int Tauler::comprovaFilaCompleta()
{
	//comencem des d'avall i pugem
	bool completa = 0;
	int i = MAX_FILA - 1;

	while (i >= 0 && completa == 0)
	{
		if (m_posicions[i][0] != NO_COLOR && m_posicions[i][1] != NO_COLOR && m_posicions[i][2] != NO_COLOR && m_posicions[i][3] != NO_COLOR && m_posicions[i][4] != NO_COLOR && m_posicions[i][5] != NO_COLOR && m_posicions[i][6] != NO_COLOR && m_posicions[i][7] != NO_COLOR && m_posicions[i][8] != NO_COLOR && m_posicions[i][9] != NO_COLOR && m_posicions[i][10] != NO_COLOR)
		{
			completa = 1;
		}
		else
		{
			i--;
		}
	}

	if (completa == 1)
	{
		return i; //retorna la posicio de la fila si està complerta
	}
	else
	{
		return -1; //sinó retorna -1
	}

}



void Tauler::baixaFila(int y)
{
	for (int j = 0; j < MAX_COL; j++)
	{
		for (int i = y; i >= 0; i--)
		{
			if (i > 1) //Si està a la posició 0 ha de posar a i y j NO_FIGURA per no obtenir dades random
			{
				m_posicions[i][j] = m_posicions[i - 1][j];

			}
			else if (i != 0)
			{
				m_posicions[i][j] = m_posicions[i - 1][j];
				m_posicions[i - 1][j] = NO_COLOR;

			}
		}

	}

}



void Tauler::escriuTauler()
{
	int tipus;
	for (int i = 0; i < MAX_FILA; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			switch (m_posicions[i][j])
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
				tipus = 0;
				break;

			}

			cout << tipus << " ";
		}
		cout << endl;
	}
}

void Tauler::dibuixaPeces()
{
	IMAGE_NAME tipus;
	for (int i = 0; i < MAX_FILA; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			switch (m_posicions[i][j])
			{
			case NO_COLOR:
				tipus = GRAFIC_QUADRAT_NEGRE;
				break;
				
			case COLOR_GROC:
				tipus = GRAFIC_QUADRAT_GROC;
				break;

			case COLOR_BLAUCEL:
				tipus = GRAFIC_QUADRAT_BLAUCEL;
				break;

			case COLOR_MAGENTA:
				tipus = GRAFIC_QUADRAT_MAGENTA;
				break;

			case COLOR_TARONJA:
				tipus = GRAFIC_QUADRAT_TARONJA;
				break;

			case COLOR_BLAUFOSC:
				tipus = GRAFIC_QUADRAT_BLAUFOSC;
				break;

			case COLOR_VERMELL:
				tipus = GRAFIC_QUADRAT_VERMELL;
				break;

			case COLOR_VERD:
				tipus = GRAFIC_QUADRAT_VERD;
				break;
			default:
				tipus = GRAFIC_QUADRAT_NEGRE;
				break;
				


			}
			GraphicManager::getInstance()->drawSprite(tipus, POS_X_TAULER + ((j + 1) * MIDA_QUADRAT), POS_Y_TAULER + (i) * MIDA_QUADRAT, false);
		/*	GraphicManager::getInstance()->drawSprite(tipus,
				POS_X_TAULER + (j * MIDA_QUADRAT), POS_Y_TAULER + ((i - 1) * MIDA_QUADRAT), false);
				*/
		}
	}
	//GraphicManager::getInstance()->drawSprite(GRAFIC_QUADRAT_GROC, POS_X_TAULER + (0 * MIDA_QUADRAT), POS_Y_TAULER + (0) * MIDA_QUADRAT, false);
}


bool const Tauler::comprovaGir(Figura& figura, int pos_x, int pos_y, DireccioGir direccio)
{

	bool potGirar = 1; //comprovarem si pot caure, si és igual a 1 si ho pot.

	if (figura.getTipus() == FIGURA_O)
	{
		potGirar = 0;
	}
	else
	{
		borraFigura(figura.getPosicioX(), figura.getPosicioY(), figura);
		Figura figuraTemp;
		if (direccio == GIR_HORARI)
		{
			if (figura.getRotacio() == 0)
			{
				figuraTemp.setMatriuFigura(figura.getTipus(), 1);
			}
			else if (figura.getRotacio() == 1)
			{
				figuraTemp.setMatriuFigura(figura.getTipus(), 2);

			}
			else if (figura.getRotacio() == 2)
			{
				figuraTemp.setMatriuFigura(figura.getTipus(), 3);
			}
			else if (figura.getRotacio() == 3)
			{
				figuraTemp.setMatriuFigura(figura.getTipus(), 0);
			}
		}
		else
		{
			if (figura.getRotacio() == 0)
			{
				figuraTemp.setMatriuFigura(figura.getTipus(), 3);
			}
			else if (figura.getRotacio() == 1)
			{
				figuraTemp.setMatriuFigura(figura.getTipus(), 0);
			}
			else if (figura.getRotacio() == 2)
			{
				figuraTemp.setMatriuFigura(figura.getTipus(), 1);
			}
			else if (figura.getRotacio() == 3)
			{
				figuraTemp.setMatriuFigura(figura.getTipus(), 2);
			}
		}

		if ((figura.getPosicioX() <= -1 && figura.getRotacio() == 1) || (figura.getPosicioX() <= -1 && figura.getRotacio() == 3 && figura.getTipus() == FIGURA_I) || (figura.getPosicioX() >= (MAX_COL - 3) && figura.getRotacio() == 3 && figura.getTipus() == FIGURA_I) || (figura.getPosicioX() >= (MAX_COL - 2) && figura.getRotacio() == 3 && figura.getTipus() != FIGURA_I) || (figura.getPosicioX() >= (MAX_COL - 3) && figura.getRotacio() == 1 && figura.getTipus() == FIGURA_I) || (figura.getPosicioX() == (MAX_COL-2) && figura.getRotacio() == 3))
		{
			potGirar = 0;
		}
		else
		{
			for (int i = 0; i < figura.getMaxX(); i++)
			{
				for (int j = 0; j < figura.getMaxY(); j++)
				{
					//cout << m_posicions[pos_y + j][pos_x + i] << endl;
					if ((figuraTemp.getPosicioMatriu(i, j) != NO_COLOR) && (m_posicions[pos_y + j][pos_x + i] != NO_COLOR))
					{
						potGirar = 0;
					}
				}
			}
		}

		introdueixFigura(figura.getPosicioX(), figura.getPosicioY(), figura); //retornem la figura a l'estat d'abans
	}

	return potGirar;


}

/*
ifstream& operator>>(ifstream& input, Tauler& tauler)
{

	ColorFigura color;
	int i_color;


	for (int i = 0; i < MAX_FILA; i++) // FILES
	{
		for (int j = 0; j < MAX_COL; j++) // COLUMNES
		{
			input >> i_color;

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

			}

			tauler.setPosicio(j, i, color);
		}
	}

	return input;
}

*/