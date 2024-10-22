#include "nco.h"
#include <cmath>
#include <iostream>

NCO::NCO(const int lgtblsize, const float freq) :
    m_log_length{lgtblsize},
    m_length{(1 << lgtblsize)},
    m_mask{m_length - 1},
    m_phase{0},
    m_phase_diff {(int)(freq * ONE_ROTATION / SAMPLE_RATE)},
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
