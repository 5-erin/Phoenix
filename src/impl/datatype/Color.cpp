#include <format>

#include "datatype/Color.hpp"
#include "Utilities.hpp"

Color::Color()
{
    this->R = 0.f;
    this->G = 0.f;
    this->B = 0.f;
}

Color::Color(float S)
{
    R = S;
    G = S;
    B = S;
}

Color::Color(float r, float g, float b)
{
    this->R = r;
    this->G = g;
    this->B = b;
}
