#include <iostream>
#include <cstdlib>
#include <random>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
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
    std::vector<Organizm*> delQueue;

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


        std::cout<<"ptr 1"<<std::endl;

        for(; x <= x1; x++) {
            for (; y <= y1; y++) {
                if (this->isEmpty({x,y}) && ((x != obj.x) || (y != obj.y)))
                {
                    freebies.push_back({x,y});
                }
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

        x = distr(generator);

        if(ret == 0)
            return {-1,-1};
        else
            return freebies[x];
    }



    void WykonajTure(void)
    {
        int i, j, force;
        int niechMocBedzieStobo = 0;
        std::string log = "---";

        makeTurnqueue();

        for (i = 0; i < operationQueue.size(); i++) {
            if(operationQueue[i] == NULL)
                continue;
            log = operationQueue[i]->rysowanie() + log;
            log += this->enumToString( operationQueue[i]->akcja() );
            logsQueue.push_back(log);
            log = "---";
        }
        this->operationQueue.clear();
    }


    void rysujSwiat()
    {
        int i, j, last;
        rTerminal();

        while (!logsQueue.empty()) {
            std::cout<<logsQueue.back()<<std::endl;
            logsQueue.pop_back();
        }
    
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
        makeTurnqueue();

        for (i = 0; i < operationQueue.size(); i++) {
            if(operationQueue[i] == NULL)
                continue;
            delete operationQueue[i];
        }

        for (i = 0; i < sizeSwiatArray; i++)
            delete[] swiatArray[i];
        delete[] swiatArray;
    }

private:
    /* It is impossible to change the name of the author cuz it is a const */
    const char* const imieAutora = "Dawid Węsierski";
    const char* const indeksAutora = "180029";
    std::vector<Organizm*> operationQueue;
    std::vector<std::string> logsQueue;

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

    std::string enumToString(int a)
    {
        switch (a) {
            case SWIAT_SUCCESS:
                return "SWIAT_NOTHING";

            case SWIAT_COLLISION:
                return "SWIAT_COLLISION";
            case SWIAT_MOVED_SUCCESSFULY:
                return "SWIAT_MOVED_SUCCESSFULY";
            case SWIAT_CHALLENGER_WINS:
                return "SWIAT_CHALLENGER_WINS";
            case SWIAT_CHALLENGER_LOSES:
                return "SWIAT_CHALLENGER_LOSES";
            case SWIAT_BABY_CREATED:
                return "SWIAT_BABY_CREATED";
            case SWIAT_BABY_ABORTED_OVERPOPULATION:
                return " SWIAT_BABY_ABORTED_OVERPOPULATION";
            case SWIAT_GROWED:
                return "SWIAT_GROWED";
            case   SWIAT_NO_PLACE_TO_GROW:
                return "  SWIAT_NO_PLACE_TO_GROW";
            case   SWIAT_CHALLENGER_SCARED_OF_LION:
                return "  SWIAT_CHALLENGER_SCARED_OF_LION";
            case SWIAT_LAZY_SLOTH:
                return "SWIAT_LAZY_SLOTH";
            default:
                return "SWIAT UNIMAGINABLE HORROR";
        }
    }
};

class Zwierze : public Organizm
{
public:
    Zwierze(Swiat* swiat, point polozenie, char smb)
    {
        this->symbol = smb;
        this->wiek = this->inicjatywa + this->sila;
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
                std::cout<<"mtb -"<<leap.x<<" y - "<<leap.y<<std::endl;
            }

        if (this->ourSwiat->isEmpty(leap))
        {
            this->ourSwiat->swiatArray[polozenie.x][polozenie.y] = NULL;
            this->ourSwiat->swiatArray[leap.x][leap.y] = this;
            polozenie = leap;
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
        } else if (this->sila >= obj->sila) {
            this->ourSwiat->delQueue.push_back(obj);
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
        this->inicjatywa = 0;
        this->sila = 0;
        this->ourSwiat->addToSwiat(polozenie, this);
    }

    char rysowanie()
    {
        return this->symbol;
    }

    int akcja()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> propability(0, 100);

        if (propability(gen) < 95)
            return SWIAT_SUCCESS;

        point sprout = this->ourSwiat->findNearEmpty(this->polozenie);

        if(sprout.x != -1) {
            this->ourSwiat->swiatArray[sprout.x][sprout.y]
                = new Roslina(this->ourSwiat, sprout, this->symbol);
            return SWIAT_GROWED;
        }
        return SWIAT_NO_PLACE_TO_GROW;
    }

    int kolizja(Organizm* obj)
    {
        std::cout<<"kolizja ?"<<std::endl;
        obj->kolizja(this);
        return SWIAT_CHALLENGER_WINS;
    }
};

class Mlecz : public Roslina
{
public:
    Mlecz(Swiat* swiat, point polozenie, char smb = '#') :
        Roslina (swiat, polozenie, smb) {};
    
    int akcja()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> propability(0, 100);

        for(int i = 0; i < 3; i++) {
            if (propability(gen) < 95)
                    continue;
            else if (propability(gen) < 95 && i == 2) {
                return SWIAT_SUCCESS;
            }
        }

        point sprout = this->ourSwiat->findNearEmpty(this->polozenie);

        if(sprout.x != -1) {
            this->ourSwiat->swiatArray[sprout.x][sprout.y]
                = new Roslina(this->ourSwiat, sprout, this->symbol);
            return SWIAT_GROWED;
        }
        return SWIAT_NO_PLACE_TO_GROW;
    }
};

class Ciern : public Roslina
{
public:
    Ciern(Swiat* swiat, point polozenie, char smb = '$') :
        Roslina (swiat, polozenie, smb) {};

    int akcja()
    {
        point sprout = this->ourSwiat->findNearEmpty(this->polozenie);

        if(sprout.x != -1) {
            this->ourSwiat->swiatArray[sprout.x][sprout.y]
                = new Roslina(this->ourSwiat, sprout, this->symbol);
            return SWIAT_GROWED;
        }
        return SWIAT_NO_PLACE_TO_GROW;
    }

};


class Wilk : public Zwierze
{
public:
    Wilk(Swiat* swiat, point polozenie, char smb = 'W') :
        Zwierze (swiat, polozenie, smb )
    {
        this->sila = 9;
        this->inicjatywa = 5;
    }
};

class Owca : public Zwierze
{
public:
    Owca(Swiat* swiat, point polozenie, char smb = 'O') :
        Zwierze (swiat, polozenie, smb )
    {
        this->sila = 4;
        this->inicjatywa = 4;
    }
};

class Lew : public Zwierze
{
public:
    Lew(Swiat* swiat, point polozenie, char smb = 'L') :
        Zwierze (swiat, polozenie, smb )
    {
        this->sila = 11;
        this->inicjatywa = 7;
    }

    int kolizja(Organizm* obj)
    {
        if(obj->sila < 5){
            return SWIAT_CHALLENGER_SCARED_OF_LION;
        } else {
            return Zwierze::kolizja(obj);
        }
    }

};

class Zulw : public Zwierze
{
public:
    Zulw(Swiat* swiat, point polozenie, char smb = 'Z') :
        Zwierze (swiat, polozenie, smb )
    {
        this->sila = 2;
        this->inicjatywa = 1;
    }

    int kolizja(Organizm* obj)
    {
        if(obj->sila < 5){
            return SWIAT_CHALLENGER_UNABLE_TO_PENETRATE_TURTLE;
        } else {
            return Zwierze::kolizja(obj);
        }
    }

    int akcja()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> propability(0, 100);

        if (propability(gen) < 75)
            return SWIAT_SUCCESS;
        else {
            return Zwierze::akcja();
        }
    }
};

class Leniwiec : public Zwierze
{
public:
    Leniwiec(Swiat* swiat, point polozenie, char smb = 'S') :
        Zwierze (swiat, polozenie, smb )
    {
        this->sila = 2;
        this->inicjatywa = 1;
        this->moved = false;
    }

    int akcja()
    {
        if (this->moved) {
            return SWIAT_LAZY_SLOTH;
            this->moved = false;
        } else {
            this->moved = true;
            std::cout<<this->moved<<std::endl;
            return Zwierze::akcja();
        }
    }

private:
    bool moved;

};


class Terminal
{
public:
    Terminal(int x)
    {
        control = 0;
        virtualWorld = new Swiat(x);
        new Owca(virtualWorld, {1,0});
        new Owca(virtualWorld, {1,1});
        new Lew(virtualWorld, {0,1});
        new Wilk(virtualWorld, {2,1});
        new Lew (virtualWorld, {5,1});
        new Leniwiec(virtualWorld, {4,1});
        new Mlecz(virtualWorld, {0,0});
        new Ciern(virtualWorld, {4,5});

        while(control != 'x')
        {
            virtualWorld->rysujSwiat();
            control = terminalHandler();
            virtualWorld->WykonajTure();
        }
    }

    ~Terminal()
    {
        delete virtualWorld;
    }

protected:
    Swiat* virtualWorld;
    char control;

    static char terminalHandler ()
    {
        int cntrl = 0;
        std::cout << "Naciśnij enter, aby kontynuować..." << std::endl;
        return getchar();
    }
};


int main()
{
    try
    {
        Terminal one(13);
    }
    catch(...)
    {
    std::cout << "\nOj zlapany wyjatek\n";
    }
    return 0;


}
