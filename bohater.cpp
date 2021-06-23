#include "bohater.h"
#include "pocisk.h"

Bohater::Bohater(Vector2f& position) {
    setPosition(position);

    setTextureRect({0, 0, texture_size.x, texture_size.y});
    setOrigin(float(texture_size.x) / 2, float(texture_size.y) / 2);
}


void Bohater::setSpeed(float x, float y) {
    speed_x = x;
    speed_y = y;
}

void Bohater::setFacing(bool f) {
    facing = f;
}

bool Bohater::getFacing() {
    return facing;
}


void Bohater::setBounds(float left, float right, float top, float bottom) {
    left_borderline = left;
    right_borderline = right;
    top_borderline = top;
    bottom_borderline = bottom;
}

void Bohater::bounce() {
    if (getGlobalBounds().top <= top_borderline) {
        speed_y = abs(speed_y);
    } else if (getGlobalBounds().top + getGlobalBounds().height >= bottom_borderline) {
        speed_y = -abs(speed_y);
    } else if (getGlobalBounds().left <= left_borderline) {
        speed_x = abs(speed_x);
    } else if (getGlobalBounds().left + getGlobalBounds().width >= right_borderline) {
        speed_x = -abs(speed_x);
    }
}

void Bohater::shoot() {
    Pocisk nowy_pocisk(Vector2f(20, 20), getFacing());
    nowy_pocisk.set_position(Vector2f(getPosition().x, getPosition().y));
    Pocisk::wystrzelone_pociski.emplace_back(nowy_pocisk);
}

void Bohater::animate(const Time& elapsed, const vector<shared_ptr<Platforma>>& platforms, Clock& jump_cooldown) {
    float sec = elapsed.asSeconds();

    if (Keyboard::isKeyPressed(Keyboard::Key::A) && getGlobalBounds().left > left_borderline) {
        speed_x = -difficulty_level::bohater_speed;
        setScale(-2.5, 2.5);
        setFacing(false);
        is_running = true;
    } else if (Keyboard::isKeyPressed(Keyboard::Key::D) &&
               getGlobalBounds().left + getGlobalBounds().width < right_borderline) {
        speed_x = difficulty_level::bohater_speed;
        setScale(2.5, 2.5);
        setFacing(true);
        is_running = true;

    } else {
        speed_x = 0;
        is_running = false;

    }
    if (Keyboard::isKeyPressed(Keyboard::Key::W) && getGlobalBounds().top > top_borderline &&
        jump_cooldown.getElapsedTime().asSeconds() >= 1) {
        //setSpeed(0, -400);
        speed_y = -700;
        jump_cooldown.restart();
    }
    speed_y += 3000 * sec;

    float potential_x = speed_x * sec;
    float potential_y = speed_y * sec;

    if (!is_running) {
        setTexture(static_john_texture());
        setTextureRect({0, 0, 26, 22});

    } else {
        if (animation_clock.getElapsedTime().asSeconds() >= frame_duration) {
            animated_hero_texture();
            animation_clock.restart();
        }
    }

    bool kolizja_pozioma = false;
    bool kolizja_pionowa = false;

    for (const shared_ptr<Platforma>& platform : platforms) {
        if (czy_pozioma_kolizja(potential_x, *platform) and !czy_stoi_na(*platform)) {
            kolizja_pozioma = true;
        }
        if (czy_pionowa_kolizja(potential_y, *platform)) {
            kolizja_pionowa = true;
        }
        bool stoi_na_innej = false;
        for (const shared_ptr<Platforma>& platform2 : platforms) {
            if (platform.get() != platform2.get() && czy_stoi_na(*platform2)) {
                stoi_na_innej = true;
            }

        }
        if (czy_stoi_na(*platform) && platform->platforma_ruszajaca && !stoi_na_innej) {
            move({0, platform->speed_y * sec});


        }
    }

    if (!kolizja_pozioma) {
        move({potential_x, 0});
    }
    if (!kolizja_pionowa) {
        move({0, potential_y});
    } else {
        speed_y = 0;
    }


    bounce();

}

void Bohater::animated_hero_texture() {
    setTexture(running_john_texture());
    current_texture++;
    if (current_texture == frame_count) current_texture = 0;
    setTextureRect({current_texture * texture_size.x, 0, texture_size.x, texture_size.y});
}

void Bohater::add_lives(int l) {
    lives += l;
}

bool Bohater::is_alive() {
    if (lives > 0) {
        return true;
    } else {
        return false;
    }
}

bool Bohater::czy_pozioma_kolizja(float potential_x, const Platforma& obiekt) {
    return getGlobalBounds().left + potential_x <= obiekt.getGlobalBounds().left + obiekt.getGlobalBounds().width &&
           getGlobalBounds().left + getGlobalBounds().width + potential_x >= obiekt.getGlobalBounds().left &&
           !(getGlobalBounds().top >= obiekt.getGlobalBounds().top + obiekt.getGlobalBounds().height ||
             getGlobalBounds().top + getGlobalBounds().height <= obiekt.getGlobalBounds().top);
}

bool Bohater::czy_pionowa_kolizja(float potential_y, const Platforma& obiekt) {
    return getGlobalBounds().top + potential_y <= obiekt.getGlobalBounds().top + obiekt.getGlobalBounds().height &&
           getGlobalBounds().top + getGlobalBounds().height + potential_y >= obiekt.getGlobalBounds().top &&
           !(getGlobalBounds().left >= obiekt.getGlobalBounds().left + obiekt.getGlobalBounds().width ||
             getGlobalBounds().left + getGlobalBounds().width <= obiekt.getGlobalBounds().left);
}

bool Bohater::czy_stoi_na(const Platforma& obiekt) {
    return getGlobalBounds().top - 0.1 <= obiekt.getGlobalBounds().top + obiekt.getGlobalBounds().height &&
           getGlobalBounds().top + getGlobalBounds().height + 0.1 >= obiekt.getGlobalBounds().top &&
           !(getGlobalBounds().left >= obiekt.getGlobalBounds().left + obiekt.getGlobalBounds().width ||
             getGlobalBounds().left + getGlobalBounds().width <= obiekt.getGlobalBounds().left);
}

bool Bohater::check_collision(Sprite& bonus) {
    if (getGlobalBounds().intersects(bonus.getGlobalBounds())) {
        return true;
    } else {
        return false;
    }
}

bool Bohater::chec_collision(Bonus& medal) {
    if (getGlobalBounds().intersects(medal.getGlobalBounds())) {
        return true;
    } else {
        return false;
    }
}

void Bohater::add_points(int p) {
    points += p;
}

bool Bohater::win(Bonus& medal) {
    if (points >= 6 && chec_collision(medal)) {
        return true;
    } else {
        return false;
    }
}
