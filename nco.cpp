#include "nco.h"
#include <cmath>
#include <iostream>

NCO::NCO(const int log_table_size, const float frequency) :
    m_log_length{log_table_size},
    m_length{(1 << log_table_size)},
    m_mask{m_length - 1},
    m_phase{0},
    m_phase_diff {static_cast<unsigned int>(frequency * ONE_ROTATION / SAMPLE_RATE)},
    m_table{std::vector<float>(m_length)}
{
    for(int k = 0; k < m_length; k++)
    {
        m_table[k] = sin(2.0 * M_PI * k / ((double)m_length));
    }
}


float NCO::step()
{
    m_phase += m_phase_diff;
    unsigned int index = m_phase >> ((sizeof(unsigned int) * 8) - m_log_length);
    index &= m_mask;
    return m_table[index];
}

float NCO::step_linear()
{
    // linear interpolation applied here

    m_phase += m_phase_diff;

    const unsigned int index = m_phase >> ((sizeof(unsigned int) * 8) - m_log_length);
    const unsigned int current_idx = index & m_mask;
    const unsigned int next_idx = (current_idx + 1) % m_length;

    // TODO: make 0x00ffffff variable dependent to unsigned int
    const float ratio = static_cast<float>(m_phase & 0x00ffffff) / 0x00ffffff;

    return m_table[current_idx] + (m_table[next_idx] - m_table[current_idx]) * ratio;

}
