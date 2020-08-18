#ifndef ROBOT_HPP
#define ROBOT_HPP

#define _USE_MATH_DEFINES
#include <cmath>

// ENCODER
#define CPR 7   // Counts per revolution
#define MRR 380 // Motor reduction ratio
#define QER 4   // Quadrature encoder resolution

/**
 * @brief A method to convert counts of encoder to radians
 * 
 * @param counts the number of counts of encoder
 * @return float the radians converted
 */
static inline float counts2rad(float counts) {
    return (2 * M_PI * (counts / ((float)(CPR * MRR * QER))));
}

#endif