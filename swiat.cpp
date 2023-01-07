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
    i = (rand() % range);
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
        std::vector<point> freebies;
        int x, y, x1, y1, ret;
        if (obj.x != 0)
            x = obj.x - 1;
        else
            x = obj.x;

        if (obj.y != 0)
            y = obj.y - 1;
        else 
            y = obj.y;

        if (obj.x + 1 < this->sizeSwiatArray)
            x1 = obj.x + 1;
        else
            x1 = obj.x;
        if (obj.y + 1 < this->sizeSwiatArray)
            y1 = obj.y + 1;
        else
            y1 = obj.y;

        for(; x <= x1; x++) {
            for (; y <= y1; y++) {
                if (this->isEmpty({x,y}) && (x != obj.x && y != obj.y))
                    freebies.push_back({x,y});
            }
        if (obj.y != 0)
            y = obj.y - 1;
        else 
            y = obj.y;
        }

        ret = freebies.size();
        if(ret == 0)
            return {-1,-1};
        else
            return freebies[randInt(freebies.size())];
    }

    void WykonajTure(void)
    {
        int i, j, force;
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

        /* FORCE METHOD! FUTURE DAWID OPTIMALIZATION PROBLEM */
        for (force = niechMocBedzieStobo; force > 0; force--)
        {
            for (i = 0; i < this->sizeSwiatArray; i++ ) {
                for (j = 0; j < this->sizeSwiatArray; j++) {
                    if (this->swiatArray[i][j] == NULL)
                        continue;
                    if (force == this->swiatArray[i][j]->inicjatywa);
                        swiatArray[i][j]->akcja();
                    }
            }
            std::cout<<force<<std::endl;
        }
    }


    void rysujSwiat()
    {
        int i, j;
        rTerminal();
        std::cout<<"Rysujemy Świat"<<std::endl;
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
    Zwierze(Swiat* swiat, point polozenie, char smb)
    {
        this->symbol = smb;
        this->polozenie.x = polozenie.x;
        this->polozenie.y = polozenie.y;
        this->ourSwiat = swiat;
        this->ourSwiat->swiatArray[polozenie.x][polozenie.y] = this;
        this->inicjatywa = 1;
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
            return SWIAT_MOVED_SUCCESSFULY;
        } else {
            return this->ourSwiat->swiatArray[leap.x][leap.y]->kolizja(this);
        }
    }

    int kolizja(Organizm* obj)
    {
        if(this->symbol == obj->symbol) {
            point babyPosition;
            babyPosition = this->ourSwiat->findNearEmpty(this->polozenie);
            if (babyPosition.x == -1)
                return SWIAT_BABY_ABORTED_OVERPOPULATION;

            new Zwierze(this->ourSwiat, babyPosition, this->symbol);
            return SWIAT_BABY_CREATED;

        } else if (this->sila > obj->sila) {
            delete ourSwiat->swiatArray[obj->polozenie.x][obj->polozenie.y];
            ourSwiat->swiatArray[obj->polozenie.x][obj->polozenie.y] = NULL;

            return SWIAT_CHALLENGER_LOSES;
        } else {
            obj->kolizja(this);
            return SWIAT_CHALLENGER_WINS;
        }
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
    Swiat virtualWorld(5);
    point a = {0,0};

    Zwierze* pimpek0 = new Zwierze(&virtualWorld, {1,1}, 'a');
    Zwierze* pimpek1 = new Zwierze(&virtualWorld, {0,1}, 'a');
    Zwierze* pimpek2 = new Zwierze(&virtualWorld, {1,0}, 'a');
    virtualWorld.rysujSwiat();
    a = virtualWorld.findNearEmpty({0,0});
    std::cout<<"x = "<<a.x <<" y = "<<a.y<<std::endl;
    // virtualWorld.WykonajTure();
    return 0;
}
