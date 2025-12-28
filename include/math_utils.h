#ifndef MATH_UTILS_H
#define MATH_UTILS_H

float math_utils_clampf(float number, float min_value, float max_value)
{
    return number < min_value
        ? min_value
        : number > max_value
            ? max_value
            : number;
}

float math_utils_clamp(int number, int min_value, int max_value)
{
    return number < min_value
        ? min_value
        : number > max_value
            ? max_value
            : number;
}

float math_utils_max(float f1, float f2)
{
    return f1 > f2 ? f1 : f2;
}

float math_utils_min(float f1, float f2)
{
    return f1 < f2 ? f1 : f2;
}

#endif /* MATH_UTILS_H */
