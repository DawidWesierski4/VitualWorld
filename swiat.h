#ifndef SWIAT_H
#define SWIAT_H


typedef struct point
{
    int x;
    int y;
} point;

class Swiat;

class Organizm
{
public:
    char symbol;
    int sila;
    int inicjatywa;
    point polozenie;
    Swiat* ourSwiat;

    virtual int akcja() = 0;
    virtual int kolizja() = 0;
    virtual char rysowanie() = 0;
};

class Roslina;
class Organizm;

enum directions
{
    SWIAT_DIR_LEFT,
    SWIAT_DIR_RIGHT,
    SWIAT_DIR_TOP,
    SWIAT_DIR_BOTTOM
};

void rTerminal(void);

#endif /* SWIAT_H header guard */
