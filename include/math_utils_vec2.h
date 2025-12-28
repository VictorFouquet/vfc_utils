#ifndef MATH_UTILS_VEC2_H
#define MATH_UTILS_VEC2_H

#include <stdlib.h>

typedef struct t_math_utils_vec2
{
    float x;
    float y;
} t_math_utils_vec2;

t_math_utils_vec2 math_utils_vec2(float x, float y)
{
    return (t_math_utils_vec2) { x, y };
}

t_math_utils_vec2 math_utils_vec2_add(t_math_utils_vec2 v1, t_math_utils_vec2 v2)
{
    return (t_math_utils_vec2) {
        .x = v1.x + v2.x,
        .y = v1.y + v2.y
    };
}

t_math_utils_vec2 math_utils_vec2_sub(t_math_utils_vec2 v1, t_math_utils_vec2 v2)
{
    return (t_math_utils_vec2) {
        .x = v1.x - v2.x,
        .y = v1.y - v2.y
    };
}

t_math_utils_vec2 math_utils_vec2_scale(t_math_utils_vec2 v1, float scale)
{
    return (t_math_utils_vec2) {
        .x = v1.x * scale,
        .y = v1.y * scale
    };
}

#endif /* MATH_UTILS_VEC2_H */
