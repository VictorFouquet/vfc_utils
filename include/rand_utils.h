#ifndef RAND_UTILS_H
#define RAND_UTILS_H

/**
 * @file rand_utils.h
 * @brief Utility functions for generating random numbers in C.
 */

#include <stdlib.h>

/**
 * @brief Initializes the random number generator using the current time.
 *
 * Must be called once before using any other random functions.
 */
void rand_utils_seed(void);

/**
 * @brief Generates a random integer between min and max (inclusive).
 *
 * @param min Minimum possible value.
 * @param max Maximum possible value.
 * @return Random integer between min and max.
 */
int rand_utils_int(int min, int max);

/**
 * @brief Generates a random float between min and max.
 *
 * @param min Minimum possible value.
 * @param max Maximum possible value.
 * @return Random float in [min, max).
 */
float rand_utils_float(float min, float max);

#endif /* RAND_UTILS_H */
