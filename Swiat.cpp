#include <iostream>

class Swiat {

public:
    void WykonajTure(void)
    {
        std::cout<<"WykonajTure"<<std::endl;
    }

    void rysujSwiat(void)
    {
        std::cout<<"rysujSwiat"<<std::endl;
    }
};

int main()
{
    Swiat virtualWorld;
    std::cout<<"hello world"<<std::endl;
    virtualWorld.rysujSwiat();
    virtualWorld.WykonajTure();
    return 0;
}
