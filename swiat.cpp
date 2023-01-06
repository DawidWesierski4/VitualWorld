#include <iostream>
#include <cstdlib>
#include <ctime>
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
private:
    /* It is impossible to change the name of the author cuz it is a const */
    const char* const imieAutora = "Dawid Węsierski";
    const char* const indeksAutora = "180029";
    Organizm ***swiatArray;
    int sizeSwiatArray;

public:
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

    void WykonajTure(void)
    {
        std::cout<<"WykonajTure"<<std::endl;
    }

    void rysujSwiat()
    {
        int i, j;
        // rTerminal();
        std::cout<<"Rysujemy Świat"<<std::endl;
        std::cout<<this->sizeSwiatArray<<std::endl;
        for (i = 0; i < this->sizeSwiatArray; i++ ) {
            for (j = 0; j < this->sizeSwiatArray; j++) {
                if (!this->swiatArray[i][j])
                    std::cout<<BLACK_BLOCK<<'|';
                else
                    std::cout<<(char)this->swiatArray[i][j]->rysowanie();
            }
            std::cout<<std::endl;
        }
        std::cout<<"imie Autora = "<<imieAutora<<std::endl;
        std::cout<<"indeks Autora = "<<indeksAutora<<std::endl;
    }

    ~Swiat()
    {
        int i;
        for (i = 0; i < sizeSwiatArray; i++)
            delete[] swiatArray[i];
        delete[] swiatArray;
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
    }

    char rysowanie()
    {
        return this->symbol;
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
    }

    char rysowanie()
    {
        return this->symbol;
    }
};

int main()
{
    bool reset;
    Swiat virtualWorld(20);
    std::cout<<"hello world"<<std::endl;
    virtualWorld.rysujSwiat();
    return 0;
}
