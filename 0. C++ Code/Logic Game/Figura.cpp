#include "Figura.h"
#include <iostream>
using namespace std;

void Figura::borrarFila()
{
	//trobem la fila de més avall
	int i = f_max_y - 1;
	bool trobat = 0;
	int pos = 0;
	while (!trobat && i >= 0)
	{
		int k = 0;
		while (!trobat && k < f_max_x)
		{
			if (f_matriuFigura[i][k] != NO_COLOR)
			{
				trobat = 1;
				pos = i;
			}
			else
			{
				k++;
			}

			
		}
		if (trobat == 0)
		{
			i--;
		}
	}

	if (trobat == 1)
	{
		int j = 0;
		while (j < f_max_x)
		{

			f_matriuFigura[pos][j] = NO_COLOR;
			j++;

		}
	}
}


void Figura::setMatriuFigura(TipusFigura tipus, int rotacio)
{
	ColorFigura color;
	switch (tipus)
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

	int x = 0;
	int y = 0;

	for (int i = 0; i < MAX_ALCADA; i++)
	{
		for (int j = 0; j < MAX_AMPLADA; j++)
		{
			f_matriuFigura[i][j] = NO_COLOR;
		}
	}


	switch (tipus)
	{

	case FIGURA_O: //dona igual la rotacio
		f_matriuFigura[y][x] = color;
		f_matriuFigura[y + 1][x + 1] = color;
		f_matriuFigura[y][x + 1] = color;
		f_matriuFigura[y + 1][x] = color;
		f_max_x = 2;
		f_max_y = 2;
		f_pos_x_centre = 0;
		break;

	case FIGURA_J:
		switch (rotacio)
		{
		case 0:
			f_matriuFigura[y][x] = color;
			f_matriuFigura[y + 1][x] = color;
			f_matriuFigura[y + 1][x + 1] = color;
			f_matriuFigura[y + 1][x + 2] = color;
			break;

		case 1:
			f_matriuFigura[y][x + 1] = color;
			f_matriuFigura[y][x + 2] = color;
			f_matriuFigura[y + 1][x + 1] = color;
			f_matriuFigura[y + 2][x + 1] = color;
			break;

		case 2:
			f_matriuFigura[y + 1][x] = color;
			f_matriuFigura[y + 1][x + 1] = color;
			f_matriuFigura[y + 1][x + 2] = color;
			f_matriuFigura[y + 2][x + 2] = color;
			break;

		case 3:
			f_matriuFigura[y][x + 1] = color;
			f_matriuFigura[y + 1][x + 1] = color;
			f_matriuFigura[y + 2][x + 1] = color;
			f_matriuFigura[y + 2][x] = color;
			break;
		}
		f_max_x = 3;
		f_max_y = 3;
		break;

	case FIGURA_L:
		switch (rotacio)
		{
		case 0:
			f_matriuFigura[y + 1][x] = color;
			f_matriuFigura[y + 1][x + 1] = color;
			f_matriuFigura[y + 1][x + 2] = color;
			f_matriuFigura[y][x + 2] = color;
			break;

		case 1:
			f_matriuFigura[y][x + 1] = color;
			f_matriuFigura[y + 1][x + 1] = color;
			f_matriuFigura[y + 2][x + 1] = color;
			f_matriuFigura[y + 2][x + 2] = color;
			break;

		case 2:
			f_matriuFigura[y + 1][x] = color;
			f_matriuFigura[y + 1][x + 1] = color;
			f_matriuFigura[y + 1][x + 2] = color;
			f_matriuFigura[y + 2][x] = color;
			break;

		case 3:
			f_matriuFigura[y][x] = color;
			f_matriuFigura[y][x + 1] = color;
			f_matriuFigura[y + 1][x + 1] = color;
			f_matriuFigura[y + 2][x + 1] = color;
			break;
		}
		f_max_x = 3;
		f_max_y = 3;
		break;
	case FIGURA_S:
		switch (rotacio)
		{
		case 0:
			f_matriuFigura[y][x + 1] = color;
			f_matriuFigura[y][x + 2] = color;
			f_matriuFigura[y + 1][x + 1] = color;
			f_matriuFigura[y + 1][x] = color;
			break;

		case 1:
			f_matriuFigura[y][x + 1] = color;
			f_matriuFigura[y + 1][x + 1] = color;
			f_matriuFigura[y + 1][x + 2] = color;
			f_matriuFigura[y + 2][x + 2] = color;
			break;

		case 2:
			f_matriuFigura[y + 1][x + 1] = color;
			f_matriuFigura[y + 1][x + 2] = color;
			f_matriuFigura[y + 2][x] = color;
			f_matriuFigura[y + 2][x + 1] = color;
			break;

		case 3:
			f_matriuFigura[y][x] = color;
			f_matriuFigura[y + 1][x] = color;
			f_matriuFigura[y + 1][x + 1] = color;
			f_matriuFigura[y + 2][x + 1] = color;
			break;
		}
		f_max_x = 3;
		f_max_y = 3;
		break;
	case FIGURA_Z:
		switch (rotacio)
		{
		case 0:
			f_matriuFigura[y][x] = color;
			f_matriuFigura[y][x + 1] = color;
			f_matriuFigura[y + 1][x + 1] = color;
			f_matriuFigura[y + 1][x + 2] = color;
			break;

		case 1:
			f_matriuFigura[y][x + 2] = color;
			f_matriuFigura[y + 1][x + 2] = color;
			f_matriuFigura[y + 1][x + 1] = color;
			f_matriuFigura[y + 2][x + 1] = color;
			break;

		case 2:
			f_matriuFigura[y + 1][x] = color;
			f_matriuFigura[y + 1][x + 1] = color;
			f_matriuFigura[y + 2][x + 1] = color;
			f_matriuFigura[y + 2][x + 2] = color;
			break;

		case 3:
			f_matriuFigura[y][x + 1] = color;
			f_matriuFigura[y + 1][x + 1] = color;
			f_matriuFigura[y + 1][x] = color;
			f_matriuFigura[y + 2][x] = color;
			break;
		}
		f_max_x = 3;
		f_max_y = 3;
		break;
	case FIGURA_T:
		switch (rotacio)
		{
		case 0:
			f_matriuFigura[y][x + 1] = color;
			f_matriuFigura[y + 1][x] = color;
			f_matriuFigura[y + 1][x + 1] = color;
			f_matriuFigura[y + 1][x + 2] = color;
			break;

		case 1:
			f_matriuFigura[y][x + 1] = color;
			f_matriuFigura[y + 1][x + 1] = color;
			f_matriuFigura[y + 2][x + 1] = color;
			f_matriuFigura[y + 1][x + 2] = color;
			break;

		case 2:
			f_matriuFigura[y + 1][x + 1] = color;
			f_matriuFigura[y + 1][x] = color;
			f_matriuFigura[y + 1][x + 2] = color;
			f_matriuFigura[y + 2][x + 1] = color;
			break;

		case 3:
			f_matriuFigura[y][x + 1] = color;
			f_matriuFigura[y + 1][x + 1] = color;
			f_matriuFigura[y + 2][x + 1] = color;
			f_matriuFigura[y + 1][x] = color;
			break;
		}
		f_max_x = 3;
		f_max_y = 3;
		break;
	case FIGURA_I:
		switch (rotacio)
		{
		case 0:
			f_matriuFigura[y + 1][x] = color;
			f_matriuFigura[y + 1][x + 1] = color;
			f_matriuFigura[y + 1][x + 2] = color;
			f_matriuFigura[y + 1][x + 3] = color;
			break;

		case 1:
			f_matriuFigura[y][x + 2] = color;
			f_matriuFigura[y + 1][x + 2] = color;
			f_matriuFigura[y + 2][x + 2] = color;
			f_matriuFigura[y + 3][x + 2] = color;
			break;

		case 2:
			f_matriuFigura[y + 2][x] = color;
			f_matriuFigura[y + 2][x + 1] = color;
			f_matriuFigura[y + 2][x + 2] = color;
			f_matriuFigura[y + 2][x + 3] = color;
			break;

		case 3:
			f_matriuFigura[y][x + 1] = color;
			f_matriuFigura[y + 1][x + 1] = color;
			f_matriuFigura[y + 2][x + 1] = color;
			f_matriuFigura[y + 3][x + 1] = color;
			break;
		}
		f_max_x = 4;
		f_max_y = 4;
		break;
	}
	
}

void Figura::girHorari(int f_figura[][MAX_AMPLADA])
{
	int temp[MAX_AMPLADA][MAX_ALCADA];

	for (int i = 0; i < MAX_AMPLADA; i++)
	{
		for (int j = 0; j < MAX_AMPLADA; j++)
		{
			temp[j][MAX_AMPLADA - i - 1] = f_figura[i][j];
		}
	}


	for (int i = 0; i < MAX_AMPLADA; i++) {
		for (int j = 0; j < MAX_AMPLADA; j++) {
			f_figura[i][j] = temp[i][j];
		}
	}

}
void Figura::girAntiHorari(int f_figura[][MAX_AMPLADA])
{
	int temp[MAX_AMPLADA][MAX_ALCADA];
	for (int i = 0; i < MAX_AMPLADA; i++)
	{
		for (int j = 0; j < MAX_AMPLADA; j++) {
			temp[MAX_AMPLADA - j - 1][i] = f_figura[i][j];
		}
	}

	for (int i = 0; i < MAX_AMPLADA; i++) {
		for (int j = 0; j < MAX_AMPLADA; j++) {
			f_figura[i][j] = temp[i][j];
		}
	}
}

void Figura::rotarFigura(DireccioGir direccio)
{
	if (direccio == GIR_HORARI)
	{
		if (f_rotacio == 3)
		{
			f_rotacio = 0;
		}
		else
		{
			f_rotacio++;
		}
	}
	else
	{
		if (f_rotacio == 0)
		{
			f_rotacio = 3;
		}
		else
		{
			f_rotacio--;
		}
	}
}


