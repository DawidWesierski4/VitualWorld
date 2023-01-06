#include <iostream>
#include "swiat.h"

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
    const char* const imieAutora = "Dawid Wesierski";
    const char* const indeksAutora = "180029";
    int **swiatArray;
    int sizeSwiatArray;

public:
    void WykonajTure(void)
    {
        std::cout<<"WykonajTure"<<std::endl;
    }

    void rysujSwiat(int x)
    {
        int i;

    
        swiatArray = new int*[x];
        for (i = 0; i < x; i++)
            swiatArray[i] = new int[x];

        std::cout<<"rysujSwiat"<<std::endl;
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
    virtual int sila() = 0;
    virtual int inicjatywa() = 0;
    virtual void polozenie(int x, int y) = 0;
    virtual Swiat swiat() = 0;
};

int main()
{
    bool reset;
    Swiat virtualWorld;
    std::cout<<"hello world"<<std::endl;
    virtualWorld.rysujSwiat(10);
    virtualWorld.WykonajTure();
    rTerminal();
    virtualWorld.rysujSwiat(10);
    return 0;
}
