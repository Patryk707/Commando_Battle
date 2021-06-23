#ifndef DANE_PLATFORMY_HPP
#define DANE_PLATFORMY_HPP

#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

struct dane_platformy {
    string typ_platformy;
    Vector2f pozycja, skala;
    float gorna_granica, dolna_granica;
};

#endif //DANE_PLATFORMY_HPP
