#include <iostream>
#include <chrono>
#include <vector>
#include <cmath>
#include "nco.h"

void benchmark_nco(const size_t array_length, const size_t num_of_iter);
void benchmark_nco_linear(const size_t array_length, const size_t num_of_iter);
void benchmark_sin(const size_t array_length, const size_t num_of_iter);

int main()
{
    constexpr size_t array_length = 4096;
    constexpr size_t num_of_iter = 1e6;

    benchmark_nco(array_length, num_of_iter);
    benchmark_nco_linear(array_length, num_of_iter);
    benchmark_sin(array_length, num_of_iter);

    return 0;
}

void benchmark_nco(size_t array_length, size_t num_of_iter)
{
    constexpr int table_bit_size = 8;
    constexpr float normalized_frequency = 0.01;
    NCO nco(table_bit_size, normalized_frequency);
    std::vector<float> sin_array(array_length);

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (int iter = 0; iter < num_of_iter; ++iter)
    {
        for(int idx = 0; idx < array_length; idx++)
        {
            sin_array[idx] = nco.step();
        }
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    const auto time_diff_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    std::cout << "nco " << time_diff_ms << "[ms] sin_array[0]=" << sin_array[0] << std::endl;

}

void benchmark_nco_linear(size_t array_length, size_t num_of_iter)
{
    constexpr int table_bit_size = 8;
    constexpr float normalized_frequency = 0.01;
    NCO nco(table_bit_size, normalized_frequency);
    std::vector<float> sin_array(array_length);

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (int iter = 0; iter < num_of_iter; ++iter)
    {
        for(int idx = 0; idx < array_length; idx++)
        {
            sin_array[idx] = nco.step_linear();
        }
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    const auto time_diff_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    std::cout << "nco linear = " << time_diff_ms << "[ms] sin_array[0]=" << sin_array[0] << std::endl;

}

void benchmark_sin(size_t array_length, size_t num_of_iter)
{
    constexpr int table_bit_size = 8;
    constexpr float normalized_frequency = 0.01;
    NCO nco(table_bit_size, normalized_frequency);
    std::vector<float> sin_array(array_length);

    float phase = 0.0f;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (int iter = 0; iter < num_of_iter; ++iter)
    {
        for(int idx = 0; idx < array_length; idx++)
        {
            sin_array[idx] = sin(2 * M_PI * phase);
            phase += 0.01f;
        }
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    const auto time_diff_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    std::cout << "sin = " << time_diff_ms << "[ms] sin_array[0]=" << sin_array[0] << std::endl;

}
