#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include "nco.h"

void write_to_file(const std::string& file_name,
                   const std::vector<float>& original,
                   const std::vector<float>& nco,
                   const std::vector<float>& nco_linear);

void write_as_csv(std::ofstream &output, const std::vector<float>& vec);

int main()
{
    constexpr size_t length = 100;
    constexpr float increment = 0.01f;

    std::vector<float> original_vector(length, 0);
    std::vector<float> nco_vector(length, 0);
    std::vector<float> nco_linear_vector(length, 0);

    constexpr int table_bit_length = 8;
    constexpr float frequency = increment;
    NCO nco(table_bit_length, frequency);
    NCO nco_linear(table_bit_length, frequency);

    float angle = 0;

    for (size_t idx = 0; idx < length; idx++)
    {
        original_vector[idx] = sin(angle);
        nco_vector[idx] = nco.step();
        nco_linear_vector[idx] = nco_linear.step_linear();
        angle = angle + increment;
    }

    const std::string file_name = "data.csv";
    write_to_file(file_name, original_vector, nco_vector, nco_linear_vector);

    return 0;
}


void write_as_csv(std::ofstream& output, const std::vector<float>& vec)
{
    const size_t vector_length = vec.size();

    for (size_t idx = 0; idx < vector_length; idx++)
    {
        if(idx != vector_length - 1)
        {
            output << vec[idx] << ",";
        }
        else
        {
            output << vec[idx] << std::endl;
        }
    }
}

void write_to_file(const std::string& file_name,
                   const std::vector<float>& original,
                   const std::vector<float>& nco,
                   const std::vector<float>& nco_linear)
{
    std::ofstream output_file(file_name);

    if(!output_file.is_open())
    {
        std::cout << file_name << "is not opened!" << std::endl;
        return;
    }

    write_as_csv(output_file, original);
    write_as_csv(output_file, nco);
    write_as_csv(output_file, nco_linear);
}
