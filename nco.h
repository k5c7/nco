#ifndef NCO_H
#define NCO_H
#include <vector>

class NCO
{
public:
    NCO(int log_table_size, float frequency);
    float step();
    float step_linear();

private:
    const unsigned int m_log_length;
    const unsigned int m_length;
    const unsigned int m_mask;
    unsigned int m_phase;
    unsigned int m_phase_diff;
    std::vector<float> m_table;

    static constexpr float SAMPLE_RATE = 1.0;
    static constexpr float ONE_ROTATION = 2.0 * (1u << (sizeof(unsigned) * 8 - 1));

};

#endif // NCO_H
