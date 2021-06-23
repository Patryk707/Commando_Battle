#include "przeciwnik.h"

Przeciwnik::Przeciwnik(Vector2f size) {
    setScale(size);
    setOrigin(float(texture_size.x) / 2, float(texture_size.y) / 2);

}

void Przeciwnik::set_position(Vector2f new_position) {
    setPosition(new_position);
}


void Przeciwnik::set_speed(float speed) {
    speed_x = speed;
}

void Przeciwnik::animate(const Time& elapsed) {
    float sec = elapsed.asSeconds();
    set_speed(difficulty_level::przeciwnik_speed);
    set_kierunek_ruchu();
    float droga = speed_x * sec;
    if (!kierunek_ruchu) {
        setScale(-2.5, 2.5);
        move(-abs(droga), 0);
        setFacing(false);
    } else {
        setScale(2.5, 2.5);
        move(abs(droga), 0);
        setFacing(true);
    }

    if (animation_clock.getElapsedTime().asSeconds() >= frame_duration) {
        animated_enemy_texture();
        animation_clock.restart();
    }

}

void Przeciwnik::animated_enemy_texture() {
    setTexture(running_enemy_texture());
    current_texture++;
    if (current_texture == frame_count) current_texture = 0;
    setTextureRect({current_texture * texture_size.x, 0, texture_size.x, texture_size.y});
}

void Przeciwnik::setBounds(float left, float right) {
    left_borderline = left;
    right_borderline = right;
}

void Przeciwnik::set_kierunek_ruchu() {
    if (getGlobalBounds().left <= left_borderline) {
        kierunek_ruchu = true;
        setScale(2.5, 2.5);
    }
    if (getGlobalBounds().left + getGlobalBounds().width >= right_borderline) {
        kierunek_ruchu = false;
        setScale(-2.5, 2.5);
    }
}


void Przeciwnik::set_lives(int l) {
    lives += l;
}

bool Przeciwnik::is_alive() {
    if (lives <= 0) {
        return false;
    }
    return true;
}

void Przeciwnik::setFacing(bool f) {
    facing = f;
}

bool Przeciwnik::getFacing() {
    return facing;
}

void Przeciwnik::shoot() {
    Pocisk nowy_pocisk(Vector2f(20, 20), getFacing());
    nowy_pocisk.set_position(Vector2f(getPosition().x, getPosition().y));
    Pocisk::wrogie_pociski.emplace_back(nowy_pocisk);
}



