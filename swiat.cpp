#include <iostream>
#include <cstdlib>
#include <random>
#include <vector>
#include "swiat.h"

#define BLACK_BLOCK "▪"

/**
 * reset Terminal
 *  Function should reset/clear the terminal so that you don't write lines one
 *  after another. Instead you overwrite what was written before
 *  idk how this works but does the job on linux <3 happy googling folks
*/
inline void rTerminal(void)
{
    std::cout<<"\033[2J"<<std::flush;
}

/**
  * randNear Point
  *  Function returns point that is moved by specifed reange in random direction
  *  
*/
int randInt(unsigned int range = 1)
{
    int i;
    if (range == 0)
        return 0;
    i = (rand() % ((range + 1)));
    if(rand() % 2 == 0)
        return i * -1;
    return i;

}

class Swiat
{
public:
    int sizeSwiatArray;
    Organizm ***swiatArray;

    Swiat(int x)
    {
        int i, j;
        this->sizeSwiatArray = x;
        std::cout<<sizeSwiatArray<<" "<<i<<std::endl;
        swiatArray = new Organizm**[x];
        for (i = 0; i < x; i++)
        {
            this->swiatArray[i] = new Organizm*[x];

            for(j = 0; j < x; j++)
                this->swiatArray[i][j] == NULL;
        }
    }

    /**
      * findNearEmpty
      *     this funciton goes around the input point and points to the first 
      *     NULL pointer it finds (NULL pointer nothing resides there in our
      *     world ) If every field is taken it returns pointer to -1 -1
     **/
    point findNearEmpty(point obj) {
        int i,j;
        for (i = -1; i <= 1; i++) {
            for (j = -1; j <= 1; j++ ) {
                if (obj.x + i < 0 || obj.y + j < 0)
                    continue;
                else if (swiatArray[obj.x + i][obj.y + j] == NULL)
                    return {obj.x + i, obj.y + j};
            }
        }
        return {-1,-1};
    }

    void WykonajTure(void)
    {
        int i, j;
        int niechMocBedzieStobo = 0;

        /* find the biggest icnetive */
        for (i = 0; i < this->sizeSwiatArray; i++ ) {
            for (j = 0; j < this->sizeSwiatArray; j++) {
                if(this->swiatArray[i][j] != NULL &&
                   this->swiatArray[i][j]->inicjatywa > niechMocBedzieStobo)
                    niechMocBedzieStobo = this->swiatArray[i][j]->inicjatywa;
                }
            }

        std::cout<<"Rysujemy Świat"<<std::endl;
        std::cout<<this->sizeSwiatArray<<std::endl;
        /* FORCE METHOD! */
        
        for (i = 0; i < this->sizeSwiatArray; i++ ) {
            std::cout<<"|";
            for (j = 0; j < this->sizeSwiatArray; j++) {
                if (this->swiatArray[i][j] == NULL)
                    continue;
                
                    swiatArray[i][j]->akcja() == SWIAT_SUCCESS)


                }
            }
    }


    void rysujSwiat()
    {
        int i, j;
        rTerminal();
        std::cout<<"Rysujemy Świat"<<std::endl;
        std::cout<<this->sizeSwiatArray<<std::endl;
        for (i = 0; i < this->sizeSwiatArray; i++ ) {
            std::cout<<"|";
            for (j = 0; j < this->sizeSwiatArray; j++) {
                if (!this->swiatArray[i][j])
                    std::cout<<BLACK_BLOCK<<'|';
                else
                    std::cout<<(char)this->swiatArray[i][j]->rysowanie()<<"|";
            }
            std::cout<<std::endl;//the first pipe ( ͡° ͜ʖ ͡°)
        }
        std::cout<<"imie Autora = "<<imieAutora<<std::endl;
        std::cout<<"indeks Autora = "<<indeksAutora<<std::endl;
    }

    bool isEmpty(point p)
    {
        if(p.x < sizeSwiatArray && p.y < sizeSwiatArray &&
           swiatArray[p.x][p.y] != NULL)
           return false;
        else
            return true;
    }

    void addToSwiat(point pol, Organizm* obj)
    {
        swiatArray[pol.x][pol.y] = obj;
    }

    ~Swiat()
    {
        int i;
        for (i = 0; i < sizeSwiatArray; i++)
            delete[] swiatArray[i];
        delete[] swiatArray;
    }

private:
    /* It is impossible to change the name of the author cuz it is a const */
    const char* const imieAutora = "Dawid Węsierski";
    const char* const indeksAutora = "180029";
};

class Zwierze : public Organizm
{
public:
    point leapCords;

    Zwierze(Swiat* swiat, point polozenie, char smb)
    {
        this->symbol = smb;
        this->polozenie.x = polozenie.x;
        this->polozenie.y = polozenie.y;
        this->ourSwiat = swiat;
        this->ourSwiat->swiatArray[polozenie.x][polozenie.y] = this;
    }

    char rysowanie()
    {
        return this->symbol;
    }

    int akcja()
    {
        point leap = {
            .x = this->polozenie.x + randInt(),
            .y = this->polozenie.y + randInt()
        };

        if (this->ourSwiat->isEmpty(leap))
        {
            this->ourSwiat->swiatArray[polozenie.x][polozenie.y] = NULL;
            this->ourSwiat->swiatArray[leap.x][leap.y] = this;
        } else {
            this->leapCords.x = leap.x;
            this->leapCords.y = leap.y;
        }

        return SWIAT_SUCCESS;
    }

    int kolizja(Organizm* obj)
    {
        Organizm* obj = 
               this->ourSwiat->swiatArray[this->leapCords.x][this->leapCords.y];

        if(this->symbol == obj->symbol) {
            point babyPosition;
            babyPosition = this->ourSwiat->findNearEmpty(this->polozenie);
            Zwierze(this->ourSwiat, babyPosition, this->symbol);
            return SWIAT_BABY_CREATED;
        } else if (this->sila > obj->sila) {
            Organizm *aux = ourSwiat->swiatArray[leapCords.x][leapCords.y];
            ourSwiat->swiatArray[polozenie.x][polozenie.y] = NULL;
            ourSwiat->swiatArray[leapCords.x][leapCords.y] = this;
            delete aux;
            this->polozenie.x = this->leapCords.x;
            this->polozenie.y = this->leapCords.y;
            return SWIAT_WINS;
        } else {

            return SWIAT_LOST;
        }

        return SWIAT_SUCCESS;
    }
};

class Roslina : public Organizm
{
public:
    Roslina(Swiat* swiat, point polozenie, char smb)
    {
        this->symbol = smb;
        this->polozenie.x = polozenie.x;
        this->polozenie.y = polozenie.y;
        this->ourSwiat = swiat;
        this->ourSwiat->addToSwiat(polozenie, this);
    }

    char rysowanie()
    {
        return this->symbol;
    }

    int akcja()
    {
        //we are a plant what did ya expect a flip ?
        return SWIAT_SUCCESS;
    }

    int kolizja(Organizm* obj)
    {
        
        //we are being eaten ><
        return SWIAT_SUCCESS;
    }
};

int main()
{
    srand((unsigned)time(0));
    bool reset;
    Swiat virtualWorld(20);
    point a = {0,0};
    Zwierze* pimpek = new Zwierze(&virtualWorld, a, 'a');
    virtualWorld.rysujSwiat();
    return 0;
}
