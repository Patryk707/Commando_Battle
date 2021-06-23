#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include "bohater.h"
#include "przeciwnik.h"
#include "pocisk.h"
#include "platforma.h"
#include "wczytywanie.hpp"
#include "bonus.h"
#include "difficulty_level.hpp"
#include "dane_platformy.hpp"

using namespace std;
using namespace sf;

vector<Pocisk> Pocisk::wystrzelone_pociski;
vector<Pocisk> Pocisk::wrogie_pociski;

void tworzenie_scian(vector<shared_ptr<Platforma>>& otoczenie, Texture& sciana_tekstura, Texture& blok_tekstura) {

    vector<dane_platformy> platformy = load_map("../start_map.cfg");

    for (const dane_platformy& dane_platformy : platformy) {
        shared_ptr<Platforma> platform;
        if (dane_platformy.typ_platformy == "blok") {
            platform = make_shared<Platforma>(blok_tekstura);
        } else {
            platform = make_shared<Platforma>(sciana_tekstura);
        }
        platform->setPosition(dane_platformy.pozycja);
        platform->setScale(dane_platformy.skala);
        if (dane_platformy.typ_platformy == "platforma_ruszajaca") {
            platform->platforma_ruszajaca = true;
            platform->speed_y = 100;
            platform->setBounds(dane_platformy.gorna_granica,dane_platformy.dolna_granica);
        }
        otoczenie.emplace_back(platform);
    }

//    auto block6 = make_shared<Platforma>(blok_tekstura);
//    block6->setPosition(window.getSize().x / 2 - 210, window.getSize().y - 80 - 3 * postac.getGlobalBounds().height);
//    block6->setTextureRect(IntRect(0, 0, 128, 64));
//    block6->setScale(2.8, 0.5);
//    otoczenie.emplace_back(block6);

//    auto block7 = make_shared<Platforma>(blok_tekstura);
//    block7->setPosition(window.getSize().x / 2 - 594, window.getSize().y - 80 - 4 * postac.getGlobalBounds().height);
//    //block7->setTextureRect(IntRect(0,0,128,64));
//    block7->setScale(3, 0.43);
//    otoczenie.emplace_back(block7);

//    auto block8 = make_shared<Platforma>(blok_tekstura);
//    block8->setPosition(window.getSize().x / 2 - 594, 350);
//    //block7->setTextureRect(IntRect(0,0,128,64));
//    block8->setScale(3, 0.43);
//    otoczenie.emplace_back(block8);

//    auto block9 = make_shared<Platforma>(blok_tekstura);
//    block9->setPosition(window.getSize().x / 2 - 210, 350 - postac.getGlobalBounds().height);
//    //block7->setTextureRect(IntRect(0,0,128,64));
//    block9->setScale(3.5, 0.43);
//    otoczenie.emplace_back(block9);

//    auto wall4 = make_shared<Platforma>(sciana_tekstura);
//    wall4->setScale(1, 0.2);
//    wall4->setPosition(window.getSize().x / 2 + 340, 350 - postac.getGlobalBounds().height);
//    otoczenie.emplace_back(wall4);

//    auto block10 = make_shared<Platforma>(blok_tekstura);
//    block10->setPosition(window.getSize().x / 2 + 506, 150);
//    //block7->setTextureRect(IntRect(0,0,128,64));
//    block10->setScale(0.5, 0.2);
//    otoczenie.emplace_back(block10);

//    auto wall5 = make_shared<Platforma>(sciana_tekstura);
//    wall5->setScale(1, 0.2);
//    wall5->setPosition(window.getSize().x / 2 + 280, 150);
//    otoczenie.emplace_back(wall5);

//    auto wall6 = make_shared<Platforma>(sciana_tekstura);
//    wall6->setScale(1, 0.2);
//    wall6->setPosition(window.getSize().x / 2 + 50, 150);
//    otoczenie.emplace_back(wall6);

//    auto block11 = make_shared<Platforma>(blok_tekstura);
//    block11->setPosition(window.getSize().x / 2 - 434, 150);
//    //block7->setTextureRect(IntRect(0,0,128,64));
//    block11->setScale(3, 0.43);
//    otoczenie.emplace_back(block11);

//    auto block12 = make_shared<Platforma>(blok_tekstura);
//    block12->setPosition(0, 150 - postac.getGlobalBounds().height);
//    //block7->setTextureRect(IntRect(0,0,128,64));
//    block12->setScale(2.86, 0.43);
//    otoczenie.emplace_back(block12);

//    auto platforma1 = make_shared<Platforma>(sciana_tekstura);
//    platforma1->setPosition(0, window.getSize().y - 80 - 4 * postac.getGlobalBounds().height + 30);
//    platforma1->platforma_ruszajaca = true;
//    platforma1->speed_y = 100;
//    platforma1->setScale(1.6, 0.2);
//    platforma1->setBounds(350, 660);
//    otoczenie.emplace_back(platforma1);

//    auto platforma2 = make_shared<Platforma>(sciana_tekstura);
//    platforma2->setPosition(window.getSize().x / 2 + 570, 315);
//    platforma2->platforma_ruszajaca = true;
//    platforma2->speed_y = 100;
//    platforma2->setScale(1.6, 0.2);
//    platforma2->setBounds(150, 350);
//    otoczenie.emplace_back(platforma2);
}


int main() {
    RenderWindow window(VideoMode(1600, 900), "Projekt");
    window.setFramerateLimit(60);
    Event event{};

    difficulty_level::load_diff_level("../difficulty_levels.cfg");

    Font font;
    font.loadFromFile("../slkscr.ttf");
    Text poziom(difficulty_level::level_name, font);
    poziom.setCharacterSize(30);
    poziom.setStyle(Text::Bold);
    poziom.setFillColor(Color::Red);
    poziom.setPosition(window.getSize().x -20 - poziom.getGlobalBounds().width, 20);


    Texture sciana_tekstura = load_texture("../grass.png");
    Texture blok_tekstura = load_texture("../grassMid.png");
    //Texture przeciwnik_tekstura=load_texture("./../Projekt_proba_3/grunt.png");
    Texture bonus_tekstura = load_texture("../star.png");
    Texture tlo_tekstura = load_texture("../bg_bluecolor.png");
    Texture medaaal_tekstura = load_texture("../shaded_medal4.png");    
    sciana_tekstura.setRepeated(true);
    blok_tekstura.setRepeated(true);

    vector<shared_ptr<Platforma>> otoczenie;
//tlo
    Sprite tlo;
    tlo.setPosition(0, 0);
    tlo.setTexture(tlo_tekstura);
    tlo.setScale(10, 10);


    //postac
    Vector2f position(50, window.getSize().y - 100);
    //Vector2f position(window.getSize().x / 2 - 500,320);
    Bohater postac(position);
    postac.setScale(2.5, 2.5);
    //postac.setOrigin(float(bohater_tekstura.getSize().x) / 2, float(bohater_tekstura.getSize().y) / 2);
    postac.setBounds(0, window.getSize().x, 0, window.getSize().y);
    postac.setSpeed(200, 200);
    //walls
    tworzenie_scian(otoczenie, sciana_tekstura, blok_tekstura);

//platforma








    //przeciwnik
    //vector<shared_ptr<Sprite>> przeciwnicy;
    //auto przeciwnik1=make_shared<Przeciwnik>(Vector2f(0.4,0.4));
    //przeciwnik1->setTexture(przeciwnik_tekstura);
    //przeciwnik1->set_position(Vector2f(1000,500));
    //przeciwnicy.emplace_back(przeciwnik1);

    //auto przeciwnik2=make_shared<Przeciwnik>(Vector2f(0.4,0.4));
    //przeciwnik2->setTexture(przeciwnik_tekstura);
    //przeciwnik2->set_position(Vector2f(500,500));
    //przeciwnicy.emplace_back(przeciwnik2);

    // auto przeciwnik3=make_shared<Przeciwnik>(Vector2f(0.4,0.4));
    //przeciwnik3->setTexture(przeciwnik_tekstura);
    //przeciwnik3->set_position(Vector2f(800,500));
    //przeciwnicy.emplace_back(przeciwnik3);


    //----------------
    vector<Przeciwnik> enemies;
    Przeciwnik enemy1(Vector2f(-2.5, 2.5));
    enemy1.set_position(Vector2f(400, window.getSize().y - 80));
    enemy1.shot_cooldown.restart();
    enemy1.setBounds(280, window.getSize().x / 2 + 200);
    enemies.emplace_back(enemy1);

//    Przeciwnik enemy2(Vector2f(-2.5, 2.5));
//    enemy2.set_position(Vector2f(700, window.getSize().y - 80));
//    enemy2.shot_cooldown.restart();
//    enemy2.setBounds(280, window.getSize().x / 2 + 200);
//    enemies.emplace_back(enemy2);

    Przeciwnik enemy2(Vector2f(-2.5, 2.5));
    enemy2.set_position(Vector2f(400, window.getSize().y - 178));
    enemy2.shot_cooldown.restart();
    enemy2.setBounds(385, 769);
    enemies.emplace_back(enemy2);

    Przeciwnik enemy3(Vector2f(-2.5, 2.5));
    enemy3.set_position(
            Vector2f(window.getSize().x / 2 + 300, window.getSize().y - 76 - 2 * postac.getGlobalBounds().height));
    enemy3.shot_cooldown.restart();
    enemy3.setBounds(window.getSize().x / 2 + 250, window.getSize().x / 2 + 584);
    enemies.emplace_back(enemy3);

    Przeciwnik enemy4(Vector2f(-2.5, 2.5));
    enemy4.set_position(Vector2f(window.getSize().x / 2, 627));
    enemy4.shot_cooldown.restart();
    enemy4.setBounds(window.getSize().x / 2 - 210, window.getSize().x / 2 + 150);
    enemies.emplace_back(enemy4);

    Przeciwnik enemy5(Vector2f(-2.5, 2.5));
    enemy5.set_position(Vector2f(500, 322));
    enemy5.shot_cooldown.restart();
    enemy5.setBounds(800 - 594, 800 - 210);
    enemies.emplace_back(enemy5);

    Przeciwnik enemy6(Vector2f(-2.5, 2.5));
    enemy6.set_position(Vector2f(window.getSize().x / 2, 350 - postac.getGlobalBounds().height - 27));
    enemy6.shot_cooldown.restart();
    enemy6.setBounds(window.getSize().x / 2 - 210, window.getSize().x / 2 + 238);
    enemies.emplace_back(enemy6);



    //bonusy
    vector<shared_ptr<Sprite>> bonusy;
    //vector<Bonus> bonusy_klasa;

    auto bonus1 = make_shared<Sprite>();
    bonus1->setTexture(bonus_tekstura);
    bonus1->setPosition(550, window.getSize().y - 115);
    bonus1->setScale(0.5, 0.5);
    bonusy.emplace_back(bonus1);

    auto bonus2 = make_shared<Sprite>();
    bonus2->setTexture(bonus_tekstura);
    bonus2->setPosition(window.getSize().x - 200, window.getSize().y - 115 - 3 * postac.getGlobalBounds().height);
    bonus2->setScale(0.5, 0.5);
    bonusy.emplace_back(bonus2);

    auto bonus3 = make_shared<Sprite>();
    bonus3->setTexture(bonus_tekstura);
    bonus3->setPosition(350, 535);
    bonus3->setScale(0.5, 0.5);
    bonusy.emplace_back(bonus3);

    auto bonus4 = make_shared<Sprite>();
    bonus4->setTexture(bonus_tekstura);
    bonus4->setPosition(window.getSize().x / 2, 230);
    bonus4->setScale(0.5, 0.5);
    bonusy.emplace_back(bonus4);

    auto bonus5 = make_shared<Sprite>();
    bonus5->setTexture(bonus_tekstura);
    bonus5->setPosition(window.getSize().x / 2 + 300, 85);
    bonus5->setScale(0.5, 0.5);
    bonusy.emplace_back(bonus5);

    auto bonus6 = make_shared<Sprite>();
    bonus6->setTexture(bonus_tekstura);
    bonus6->setPosition(500, 85);
    bonus6->setScale(0.5, 0.5);
    bonusy.emplace_back(bonus6);

    //Bonus bonus4(Vector2f(0.5,0.5),bonus_tekstura,Vector2f(200,200));
    //bonusy_klasa.emplace_back(bonus4);

    //warunek zwyciestwa
    Bonus medal(Vector2f(0.8, 0.8), medaaal_tekstura, Vector2f(25, 25));


    //pocisk
    bool wystrzelony = false;


    Clock clock;
    Clock shot_cooldown;
    Clock jump_cooldown;
    shot_cooldown.restart();
    jump_cooldown.restart();
    srand(time(NULL));
    while (window.isOpen()) {
        Time elapsed = clock.restart();
        window.clear(Color::Black);
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
                break;
            }
        }
        window.draw(tlo);

        //wystrzeliwanie pociskow
        if (!wystrzelony and Keyboard::isKeyPressed(Keyboard::Space)
            and shot_cooldown.getElapsedTime().asSeconds() >= postac.shot_cooldown) {
            postac.shoot();
            shot_cooldown.restart();
            wystrzelony = true;
        } else if (wystrzelony and !Keyboard::isKeyPressed(Keyboard::Space)) {
            wystrzelony = false;
        }

        //wystrzeliwanie pociskow
        for (auto& wystrzelony_pocisk : Pocisk::wystrzelone_pociski) {
            window.draw(wystrzelony_pocisk);
            wystrzelony_pocisk.set_speed(wystrzelony_pocisk.getFacing() ? difficulty_level::bohater_bullet_speed
                                                                        : -difficulty_level::bohater_bullet_speed);
        }
        for (auto& wrogi_pocisk : Pocisk::wrogie_pociski) {
            window.draw(wrogi_pocisk);
            wrogi_pocisk.set_speed(wrogi_pocisk.getFacing() ? difficulty_level::przeciwnik_bullet_speed
                                                            : -difficulty_level::przeciwnik_bullet_speed);
        }

        //otoczenie a pociski
        for (auto wystrzelony_pocisk = Pocisk::wystrzelone_pociski.begin();
             wystrzelony_pocisk < Pocisk::wystrzelone_pociski.end(); ++wystrzelony_pocisk) {
            for (auto& sciana : otoczenie) {
                if (wystrzelony_pocisk->check_collision(*sciana)) {
                    Pocisk::wystrzelone_pociski.erase(wystrzelony_pocisk);
                }
            }
        }

        for (auto wystrzelony_pocisk = Pocisk::wrogie_pociski.begin();
             wystrzelony_pocisk < Pocisk::wrogie_pociski.end(); ++wystrzelony_pocisk) {
            for (auto& sciana : otoczenie) {
                if (wystrzelony_pocisk->check_collision(*sciana)) {
                    Pocisk::wrogie_pociski.erase(wystrzelony_pocisk);
                }
            }
        }


        //przeciwnik a pocisk
        for (auto wystrzelony_pocisk = Pocisk::wystrzelone_pociski.begin();
             wystrzelony_pocisk < Pocisk::wystrzelone_pociski.end(); ++wystrzelony_pocisk) {
            for (auto enemy = enemies.begin();
                 enemy < enemies.end(); ++enemy) {
                if (wystrzelony_pocisk->check_collision(*enemy)) {
                    Pocisk::wystrzelone_pociski.erase(wystrzelony_pocisk);
                    enemy->set_lives(-1);
                    if (!enemy->is_alive()) {
                        enemies.erase(enemy);
                    }
                }
            }
        }
//bohater a pocisk
        for (auto wystrzelony_pocisk = Pocisk::wrogie_pociski.begin();
             wystrzelony_pocisk < Pocisk::wrogie_pociski.end(); ++wystrzelony_pocisk) {
            if (wystrzelony_pocisk->check_collision(postac)) {
                Pocisk::wrogie_pociski.erase(wystrzelony_pocisk);
                postac.add_lives(-1);
                if (!postac.is_alive()) {
                    cout << "Przegrana";
                    window.close();
                    break;
                }
            }
        }
//bohater a bonus
        for (auto bonus = bonusy.begin();
             bonus < bonusy.end(); ++bonus) {
            if (postac.check_collision(**bonus)) {
                postac.add_points(1);
                int losowy_bonus = rand() % 2;
                switch (losowy_bonus) {
                    case 0: {
                        postac.add_lives(1);
                        cout << "Brawo, dzieki bonusowi zyskales dodatkowe zycie" << endl;
                        break;
                    }
                    case 1: {
                        postac.shot_cooldown = postac.shot_cooldown / 2;
                        cout << "Brawo, dzieki bonusowi zyskales szybsze wystrzeliwanie pociskow" << endl;
                        break;
                    }
                }
                bonusy.erase(bonus);
            }
        }
        if (postac.win(medal)) {
            cout << "Wygrales";
            break;
        }






//enemy animation

        for (auto& enemy : enemies) {
            if (postac.getGlobalBounds().left > enemy.left_borderline and
                postac.getGlobalBounds().left + postac.getGlobalBounds().width < enemy.right_borderline and
                postac.getGlobalBounds().top > enemy.getGlobalBounds().top - enemy.getGlobalBounds().height and
                postac.getGlobalBounds().top + postac.getGlobalBounds().height <
                enemy.getGlobalBounds().top + 2 * enemy.getGlobalBounds().height) {
                enemy.setTexture(enemy.static_enemy_texture(), true);
                if (postac.getGlobalBounds().left < enemy.getGlobalBounds().left) {
                    enemy.setScale(-2.5, 2.5);
                    enemy.setFacing(false);
                }
                if (postac.getGlobalBounds().left > enemy.getGlobalBounds().left) {
                    enemy.setScale(2.5, 2.5);
                    enemy.setFacing(true);
                }

                if (!enemy.wrogi_wystrzelony and enemy.shot_cooldown.getElapsedTime().asSeconds() >= 1) {
                    enemy.shoot();
                    enemy.shot_cooldown.restart();
                    enemy.wrogi_wystrzelony = true;
                } else if (enemy.wrogi_wystrzelony) {
                    enemy.wrogi_wystrzelony = false;
                }
            } else {
                enemy.animate(elapsed);
            }
        }


        //collision postac
        postac.animate(elapsed, otoczenie, jump_cooldown);
        for(const auto& ksztalty:otoczenie){
            if(ksztalty->platforma_ruszajaca){
                ksztalty->animate(elapsed);
            }
        }





        //drawing

        for (const auto& ksztalty:otoczenie) {
            window.draw(*ksztalty);
        }
        for (auto& enemy : enemies) {
            window.draw(enemy);
        }
        for (const auto& bonus:bonusy) {
            window.draw(*bonus);
        }
        //for(auto &bonus:bonusy_klasa){
        //   window.draw(bonus);
        //}
        window.draw(postac);
        window.draw(medal);
        window.draw(poziom);


        window.display();
    }
    return 0;
}
