#ifndef PRZECIWNIK_H
#define PRZECIWNIK_H
#include <SFML/Graphics.hpp>
#include "pocisk.h"
#include<iostream>

using namespace sf;
using namespace std;


class Przeciwnik:public::Sprite
{
public:
    Przeciwnik(Vector2f size);
    void set_position(Vector2f new_position);

    //ruch
    void set_speed(float speed);
    void setBounds(float l,float r);
    void set_kierunek_ruchu();
    void animate(const Time &elapsed);
    //zycia
    void set_lives(int l);
    bool is_alive();
    //strzelanie
    void shoot();
    void setFacing(bool f);
    bool getFacing();
    bool wrogi_wystrzelony=false;
    Clock shot_cooldown;
    //tekstura
    void animated_enemy_texture();
    static Texture load_textura(const string &filename_with_path){
        Texture texture;
        if(!texture.loadFromFile(filename_with_path)){
            cerr<<"Could not load texture"<<endl;
        }
        return texture;
    }
    static Texture& static_enemy_texture() {
        const static Texture texture = load_textura("../grunt.png");
        return const_cast<Texture&>(texture);
    }

    static Texture& running_enemy_texture() {
        const static Texture texture = load_textura("../grunt_run.png");
        return const_cast<Texture&>(texture);
    }
    bool is_running=false;

    float right_borderline;
    float left_borderline;
private:

    float speed_x;
    bool kierunek_ruchu=false;
    bool facing=true;
    int lives=3;

    Clock animation_clock;
    int current_texture=0;
    Vector2<int> texture_size = {26, 22};
    int frame_count = 10;
    float frame_duration = 0.1f;
};

#endif // PRZECIWNIK_H
