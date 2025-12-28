#include <rand_utils.h>
#include <time.h>
#include <stdbool.h>

static bool has_been_seed = false;

void rand_utils_seed(void)
{
    has_been_seed = true;
    srand((unsigned int)time(NULL));
}

void ensure_seed(void)
{
    if (!has_been_seed) rand_utils_seed();
}

int rand_utils_int(int min, int max)
{
    ensure_seed();
    if (max <= min) return min;
    return min + rand() % (max - min + 1);
}

float rand_utils_float(float min, float max)
{
    ensure_seed();
    if (max <= min) return min;
    return min + ((float)rand() / (float)RAND_MAX) * (max - min);
}
