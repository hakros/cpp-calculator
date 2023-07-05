#include <cmath>

float add (float a, float b) {
    return a + b;
}

float subtract (float a, float b) {
    return a - b;
}

float multiply (float a, float b) {
    if (a == 0 || b == 0) {
        return 0;
    }

    return a * b;
}

float divide (float a, float b) {
    if (a == 0 || b == 0) {
        return 0;
    }

    return a / b;
}

float power(float a, float b) {
    return std::pow(a, b);
}