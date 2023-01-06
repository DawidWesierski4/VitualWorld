#include <iostream>
#include "swiat.h"


#define BLACK_BLOCK 0xE2

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
    /* It is impossible to change the name of the author cuz it is a const */
    const char* const imieAutora = "Dawid Węsierski";
    const char* const indeksAutora = "180029";
    Organizm ***swiatArray;
    int sizeSwiatArray;

public:
    Swiat(int x)
    {
        int i;
        this->sizeSwiatArray = i;
        swiatArray = new Organizm**[x];
        for (i = 0; i < x; i++)
        {
            this->swiatArray[i] = new Organizm*[x];

            for(i = 0; i < x; i++)
                this->swiatArray[i] == NULL;
        }
    }

    void WykonajTure(void)
    {
        std::cout<<"WykonajTure"<<std::endl;

    }

    void rysujSwiat()
    {
        int i, j;
        std::cout<<"Rysujemy Świat"<<std::endl;
        for (i = 0; i < this->sizeSwiatArray; i++ )
        {
            for (j = 0; j < this->sizeSwiatArray; j++)
            {
            if (!this->sizeSwiatArray)
                std::cout<<BLACK_BLOCK;
            else
                std::cout<<this->swiatArray[i][j]->symbol;
            }


        }
        rTerminal();
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

class Organizm
{
public:
    char symbol;
    Swiat* ourSwiat;
    virtual int sila() = 0;
    virtual int inicjatywa() = 0;
    virtual void polozenie(int x, int y) = 0;
    virtual Swiat* swiat() = 0;
};

class Zwierze : public Organizm
{
    int sila;
    int inicjatywa;

public:
    int symbol;
    Zwierze(char smb)
    {
        this->symbol = smb;
    }
    void 

}

int main()
{
    bool reset;
    Swiat virtualWorld(10);
    std::cout<<"hello world"<<std::endl;
    virtualWorld.rysujSwiat();
    return 0;
}
