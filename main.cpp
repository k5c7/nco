#include <iostream>
#include "nco.h"

int main()
{

    NCO nco(8, 0.01);

    for(int i = 0; i < 1000; i++)
    {
        std::cout << nco.step() << std::endl;
    }


    return 0;
}
