#ifndef POSTAC_H
#define POSTAC_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <memory>
#include "difficulty_level.hpp"
#include "platforma.h"
#include "bonus.h"

using namespace sf;
using namespace std;

class Bohater : public ::Sprite {
public:
    //poruszanie sie
    Bohater(Vector2f& position);

    void setSpeed(float x, float y);

    void setFacing(bool f);

    bool getFacing();

    void animate(const Time& elapsed, const vector<shared_ptr<Platforma>>& walls, Clock& jump_cooldown);

    //granice
    void setBounds(float l, float r, float t, float b);

    void bounce();

    //strzelanie
    void shoot();

    float shot_cooldown = 1;

    //zycia
    void add_lives(int l);

    bool is_alive();

    //tekstura
    void animated_hero_texture();

    static Texture load_textura(const string& filename_with_path) {
        Texture texture;
        if (!texture.loadFromFile(filename_with_path)) {
            cerr << "Could not load texture" << endl;
        }
        return texture;
    }

    static Texture& static_john_texture() {
        const static Texture texture = load_textura("../john_static.png");
        return const_cast<Texture&>(texture);
    }

    static Texture& running_john_texture() {
        const static Texture texture = load_textura("../john_run.png");
        return const_cast<Texture&>(texture);
    }

    bool is_running = false;

    //kolizje ze scianami
    bool czy_pozioma_kolizja(float potential_x, const Platforma& obiekt);

    bool czy_pionowa_kolizja(float potential_y, const Platforma& obiekt);

    bool czy_stoi_na(const Platforma& obiekt);

    //zwyciestwo
    bool check_collision(Sprite& bonus);

    bool chec_collision(Bonus& medal);

    void add_points(int p);

    bool win(Bonus& medal);


private:
    float right_borderline;
    float left_borderline;
    float top_borderline;
    float bottom_borderline;

    float speed_x;
    float speed_y;
    int lives = difficulty_level::bohater_hp;
    int points = 0;


    bool facing = true;


    Clock animation_clock;
    int current_texture = 0;
    const Vector2<int> texture_size = {26, 22};
    const int frame_count = 10;
    const float frame_duration = 0.1f;

};

#endif // POSTAC_H


