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
    int wiek;

    point polozenie;
    Swiat* ourSwiat;

    virtual int akcja() = 0;
    virtual int kolizja(Organizm* obj) = 0;
    virtual char rysowanie() = 0;
};

class Roslina;
class Organizm;

enum swiat_errors
{
    SWIAT_SUCCESS,
    SWIAT_COLLISION,
    SWIAT_MOVED_SUCCESSFULY,
    SWIAT_CHALLENGER_WINS,
    SWIAT_CHALLENGER_LOSES,
    SWIAT_BABY_CREATED,
    SWIAT_BABY_ABORTED_OVERPOPULATION,
    SWIAT_GROWED,
    SWIAT_NO_PLACE_TO_GROW
};

enum directions
{
    SWIAT_DIR_LEFT,
    SWIAT_DIR_RIGHT,
    SWIAT_DIR_TOP,
    SWIAT_DIR_BOTTOM,
    SWIAT_DIR_NMB
};

void rTerminal(void);

#endif /* SWIAT_H header guard */
