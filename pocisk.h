#ifndef POCISK_H
#define POCISK_H
#include <SFML/Graphics.hpp>
#include "przeciwnik.h"
#include <iostream>
#include <memory>

using namespace sf;
using namespace std;

class Pocisk:public::Sprite
{
    //float promien_pocisku=4.0f;
    bool facing;
public:
    Pocisk(Vector2f size, bool face);
    static Texture load_textura(const string& filename_with_path) {
        Texture texture;
        if (!texture.loadFromFile(filename_with_path)) {
            cerr << "Could not load texture" << endl;
        }
        return texture;
    }

    static Texture& pocisk_texture() {
        const static Texture pocisk_tekstura = load_textura("../bulletYellowSilver_outline.png");
        return const_cast<Texture&>(pocisk_tekstura);
    }
    //pocisk_tekstura = load_textura("../bulletYellowSilver_outline.png");

    void set_speed(float speed);
    void set_position(sf::Vector2f new_position);
    bool check_collision(Sprite &przeciwnik);


    float top();
    float bottom();
    float left();
    float right();

    bool getFacing();
    static vector<Pocisk> wystrzelone_pociski;
    static vector<Pocisk> wrogie_pociski;





};

#endif // POCISK_H
