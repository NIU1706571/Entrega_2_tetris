#ifndef FIGURA_H
#define FIGURA_H
#include "InfoJoc.h"


const int MAX_ALCADA = 4;
const int MAX_AMPLADA = 4;

typedef enum
{
    GIR_HORARI = 0,
    GIR_ANTI_HORARI
} DireccioGir;

class Figura
{
public:
    //cons
    Figura() {}
    Figura(int x, int y, TipusFigura tipus, int rot) : f_tipus(tipus), f_rotacio(rot), f_posicio_x(x), f_posicio_y(y) {}

    //getters
    TipusFigura const getTipus() { return f_tipus; }
    //ColorFigura const getColor() { return f_color; }
    int const getRotacio() { return f_rotacio; }
    int const getPosicioX() { return f_posicio_x; }
    int const getPosicioY() { return f_posicio_y; }
    int const getMaxY() { return f_max_y; }
    int const getMaxX() { return f_max_x; }
    int const getPosXCentre() { return f_pos_x_centre; }
    ColorFigura getPosicioMatriu(int x, int y) { return f_matriuFigura[y][x]; }

    //setters
    void setTipus(TipusFigura tipus) { f_tipus = tipus; }
    void setColor(ColorFigura color) { f_color = color; }
    //void setColor(ColorFigura color) { f_color = color; }
    void setRotacio(int rotacio) { f_rotacio = rotacio; }
    void setPosicioX(int x) { f_posicio_x = x; }
    void setPosicioY(int y) { f_posicio_y = y; }
    void setMaxY(int y) { f_max_y = y; }
    void setFigura(int x, int y, TipusFigura tipus) { f_posicio_x = x, f_posicio_y = y, f_tipus = tipus; }
    void setMatriuFigura(TipusFigura tipus, int rotacio);
    void girHorari(int f_figura[][MAX_AMPLADA]);
    void girAntiHorari(int f_figura[][MAX_AMPLADA]);
    void rotarFigura(DireccioGir direccio);
    void borrarFila();

private:
    TipusFigura f_tipus;
    ColorFigura f_color;
    ColorFigura f_matriuFigura[MAX_ALCADA][MAX_AMPLADA];
    int f_rotacio; //0 - 3 pag 8 power
    int f_posicio_x;
    int f_posicio_y;
    int f_max_x;
    int f_max_y;
    int f_pos_x_centre;
};


#endif
