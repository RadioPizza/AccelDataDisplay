#include "my_math.h"

// Коэффициент для перевода радиан в градусы
#define RAD_TO_DEG 57.29577951308232f

// Константы для итеративного метода
#define SQRT_ITERATIONS 10
#define ATAN_ITERATIONS 10

float my_sqrt(float x)
{
    if (x <= 0.0f)
        return 0.0f;

    float guess = x / 2.0f;
    for (int i = 0; i < SQRT_ITERATIONS; i++)
    {
        if (guess == 0.0f)
            break;
        guess = (guess + x / guess) / 2.0f;
    }
    return guess;
}

float my_atan(float z)
{
    // Если |z| > 1, используем свойство: atan(z) = PI/2 - atan(1/z)
    if (z > 1.0f)
    {
        return 1.5707963267948966f - my_atan(1.0f / z);
    }
    if (z < -1.0f)
    {
        return -1.5707963267948966f - my_atan(1.0f / z);
    }

    // Разложение Тейлора для atan(z) до n-го порядка
    float result = z;
    float z_squared = z * z;
    float term = z;
    for (int n = 1; n < ATAN_ITERATIONS; n++)
    {
        term *= -z_squared;
        float frac = 1.0f / (2.0f * n + 1.0f);
        result += frac * term;
    }
    return result;
}

float my_atan2(float y, float x)
{
    // Угол в пределах -PI до PI
    if (x > 0.0f)
    {
        return my_atan(y / x);
    }
    else if (x < 0.0f && y >= 0.0f)
    {
        return my_atan(y / x) + 3.14159265358979323846f;
    }
    else if (x < 0.0f && y < 0.0f)
    {
        return my_atan(y / x) - 3.14159265358979323846f;
    }
    else if (x == 0.0f && y > 0.0f)
    {
        return 1.5707963267948966f; // PI/2
    }
    else if (x == 0.0f && y < 0.0f)
    {
        return -1.5707963267948966f; // -PI/2
    }
    else
    {
        return 0.0f; // Неопределено, возвращаем 0
    }
}

float calculate_roll(int16_t x, int16_t y, int16_t z)
{
    float fx = (float)x;
    float fy = (float)y;
    float fz = (float)z;

    float denominator = my_sqrt(fx * fx + fz * fz);
    if (denominator == 0.0f)
        denominator = 0.0001f; // Избегаем деления на ноль

    float angle_rad = my_atan2(fy, denominator);
    return angle_rad * RAD_TO_DEG;
}

float calculate_pitch(int16_t x, int16_t y, int16_t z)
{
    float fx = (float)x;
    float fy = (float)y;
    float fz = (float)z;

    float denominator = my_sqrt(fy * fy + fz * fz);
    if (denominator == 0.0f)
        denominator = 0.0001f; // Избегаем деления на ноль
    float angle_rad = my_atan2(-fx, denominator);
    return angle_rad * RAD_TO_DEG;
}