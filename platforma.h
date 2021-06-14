#ifndef PLATFORMA_H
#define PLATFORMA_H

#include <SFML/Graphics.hpp>
#include <iostream>


using namespace sf;
using namespace std;


class Platforma : public Sprite {
private:

    float top_borderline=getGlobalBounds().top;
    float bottom_borderline=getGlobalBounds().top+getGlobalBounds().height;
public:
    Platforma(Texture& tekstura);

    void setBounds(float t, float b);

    void animate(const Time& elapsed);

    float speed_y;

    bool platforma_ruszajaca=false;
};

#endif // PLATFORMA_H
