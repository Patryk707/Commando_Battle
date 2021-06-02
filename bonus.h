#ifndef BONUS_H
#define BONUS_H
#include <SFML/Graphics.hpp>


using namespace sf;
using namespace std;

class Bonus:public::Sprite
{public:
    Bonus(Vector2f size, Texture &tekstura, Vector2f position);
};

#endif // BONUS_H
