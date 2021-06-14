#include "platforma.h"

Platforma::Platforma(Texture& tekstura) : sf::Sprite(tekstura) {
    speed_y = 0;
}

void Platforma::setBounds(float t, float b) {
    top_borderline = t;
    bottom_borderline = b;
}

void Platforma::animate(const Time& elapsed) {

    if(platforma_ruszajaca){
        float sec = elapsed.asSeconds();

        float droga = speed_y * sec;
        move(0, droga);
        if (getGlobalBounds().top <= top_borderline) {
            speed_y = 100;
        }
        if (getGlobalBounds().top + getGlobalBounds().height >= bottom_borderline) {
            speed_y = -100;
        }
    }

}
