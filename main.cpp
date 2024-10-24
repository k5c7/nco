#include <iostream>
#include "nco.h"

int main()
{
    constexpr int table_bit_size = 8;
    constexpr float normalized_frequency = 0.01; // freq = fs * normalized_freq

    NCO nco(table_bit_size, normalized_frequency);

    for(int i = 0; i < 1000; i++)
    {
        std::cout << nco.step_linear() << std::endl;
    }

    return 0;
}
