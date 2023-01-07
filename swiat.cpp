#include <iostream>
#include <cstdlib>
#include <random>
#include <vector>
#include <algorithm>
#include <random>
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

class Swiat
{
public:
    int sizeSwiatArray;
    Organizm ***swiatArray;

    Swiat(int x)
    {
        int i, j;
        this->sizeSwiatArray = x;
        swiatArray = new Organizm**[x];
        for (i = 0; i < x; i++)
        {
            this->swiatArray[i] = new Organizm*[x];

            for(j = 0; j < x; j++)
                this->swiatArray[i][j] == NULL;
        }
    }

    void moveToBounds(point *p)
    {
        if (p->x < 0)
            p->x=0;
        if (p->y < 0)
            p->y=0;
        if (p->x >= this->sizeSwiatArray)
            p->x = this->sizeSwiatArray-1;
        if (p->y >= this->sizeSwiatArray)
            p->y = this->sizeSwiatArray-1;
    }

    /**
      * findNearEmpty
      *     this funciton goes around the input point and points to the first 
      *     NULL pointer it finds (NULL pointer nothing resides there in our
      *     world ) If every field is taken it returns pointer to -1 -1
     **/
    point findNearEmpty(point obj) {
        std::vector<point> freebies;
        std::default_random_engine generator;
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

        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(0, ret-1); // define the range

        if(ret == 0)
            return {-1,-1};
        else
            return freebies[distr(gen)];
    }



    void WykonajTure(void)
    {
        int i, j, force;
        int niechMocBedzieStobo = 0;

        makeTurnqueue();

        for (i = 0; i < operationQueue.size(); i++) {
            if(operationQueue[i] == NULL)
                continue;
            operationQueue[i]->akcja();
        }
        this->operationQueue.clear();
    }


    void rysujSwiat()
    {
        int i, j;
        //rTerminal();
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
    std::vector<Organizm*> operationQueue;

    static bool comp(Organizm* a, Organizm* b) {
        if ((a->inicjatywa > b->inicjatywa) ||
            (a->inicjatywa == b->inicjatywa) && (a->wiek > b->wiek))
            return true;
        else
            return false;
    }

    void makeTurnqueue()
    {
        int x, y;

        for(x = 0; x < this->sizeSwiatArray; x++) {
            for (y = 0; y < this->sizeSwiatArray; y++) {
                if (this->swiatArray[x][y] != NULL) {
                    this->operationQueue.push_back(this->swiatArray[x][y]);
                }
            }
        }
        std::sort(operationQueue.begin(), operationQueue.end(), comp);
    }
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
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(-1, 1); // define the range
        point leap = {polozenie.x, polozenie.y};
            while(leap.x == polozenie.x && leap.y == polozenie.y) {
                leap.x = this->polozenie.x + distr(gen);
                leap.y = this->polozenie.y + distr(gen);
                ourSwiat->moveToBounds(&leap);
                std::cout<<"before x = "<<leap.x<<" y = "<<leap.y<<std::endl;
            }

        std::cout<<"after x = "<<leap.x<<" y = "<<leap.y<<std::endl;

        if (this->ourSwiat->isEmpty(leap))
        {
            std::cout<<"YAS"<<std::endl;
            this->ourSwiat->swiatArray[polozenie.x][polozenie.y] = NULL;
            this->ourSwiat->swiatArray[leap.x][leap.y] = this;
            polozenie = leap;
            return SWIAT_MOVED_SUCCESSFULY;
        } else {
            std::cout<<"WTKURWAFUCK"<<this->ourSwiat->isEmpty(leap)<<std::endl;

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

static char terminalHandler ()
{
    int cntrl = 0;
    std::cout << "Naciśnij enter, aby kontynuować..." << std::endl;
    return getchar();
}


int main()
{
    Swiat virtualWorld(35);
    char control = 0;
    Zwierze* pimpek0 = new Zwierze(&virtualWorld, {34,34}, 'a');

    std::cout<<"Hey";
    while(control != 'x')
    {
        virtualWorld.rysujSwiat();
        control = terminalHandler();
        virtualWorld.WykonajTure();
    }


    return 0;
}
