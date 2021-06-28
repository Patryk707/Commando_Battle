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

void tworzenie_scian(vector<shared_ptr<Platforma>>& otoczenie, vector<shared_ptr<Sprite>> &bonusy,vector<shared_ptr<Przeciwnik>> &enemies,
                     Texture& sciana_tekstura, Texture& blok_tekstura,Texture& bonus_tekstura ) {

    vector<dane_platformy> platformy = load_map("../config/start_map.cfg");

    for (const dane_platformy& dane_platformy : platformy) {

        if (dane_platformy.typ_platformy == "blok") {
             shared_ptr<Platforma> platform;
            platform = make_shared<Platforma>(blok_tekstura);
            platform->setPosition(dane_platformy.pozycja);
            platform->setScale(dane_platformy.skala);
            otoczenie.emplace_back(platform);
        } else if(dane_platformy.typ_platformy == "sciana"){
            shared_ptr<Platforma> platform;
            platform = make_shared<Platforma>(sciana_tekstura);
            platform->setPosition(dane_platformy.pozycja);
            platform->setScale(dane_platformy.skala);
            otoczenie.emplace_back(platform);
        } else if(dane_platformy.typ_platformy == "bonus"){
            shared_ptr<Sprite> bonus;
            bonus = make_shared<Sprite>(bonus_tekstura);
            bonus->setPosition(dane_platformy.pozycja);
            bonus->setScale(dane_platformy.skala);
            bonusy.emplace_back(bonus);
        } else if (dane_platformy.typ_platformy == "platforma_ruszajaca") {
            shared_ptr<Platforma> platform;
            platform = make_shared<Platforma>(sciana_tekstura);
            platform->setPosition(dane_platformy.pozycja);
            platform->setScale(dane_platformy.skala);
            platform->platforma_ruszajaca = true;
            platform->speed_y = 100;
            platform->setBounds(dane_platformy.gorna_granica,dane_platformy.dolna_granica);
            otoczenie.emplace_back(platform);
        } else if (dane_platformy.typ_platformy == "przeciwnik") {
            shared_ptr<Przeciwnik> enemy;
            enemy = make_shared<Przeciwnik>(dane_platformy.skala);
            enemy->setPosition(dane_platformy.pozycja);
            enemy->shot_cooldown.restart();
            enemy->setBounds(dane_platformy.gorna_granica,dane_platformy.dolna_granica);
            enemies.emplace_back(enemy);
        } else if(dane_platformy.typ_platformy == "medal"){

        }


    }




}


int main() {
    RenderWindow window(VideoMode(1600, 900), "Projekt");
    window.setFramerateLimit(60);
    Event event{};

    difficulty_level::load_diff_level("../config/difficulty_levels.cfg");
//poziom
    Font font;
    font.loadFromFile("../font/slkscr.ttf");
    Text poziom(difficulty_level::level_name, font);
    poziom.setCharacterSize(30);
    poziom.setStyle(Text::Bold);
    poziom.setFillColor(Color::Red);
    poziom.setPosition(window.getSize().x -20 - poziom.getGlobalBounds().width, 20);

//tekstury
    Texture sciana_tekstura = load_texture("../textures/grass.png");
    Texture blok_tekstura = load_texture("../textures/grassMid.png");
    Texture bonus_tekstura = load_texture("../textures/star.png");
    Texture tlo_tekstura = load_texture("../textures/bg_bluecolor.png");
    Texture medal_tekstura = load_texture("../textures/shaded_medal4.png");
    Texture przegrana_tekstura=load_texture("../textures/sGameover_1.png");
    Texture wygrana_testura=load_texture("../textures/WYGRANA.png");
    Texture zycia_tekstura=load_texture("../textures/heart pixel art 32x32.png");
    sciana_tekstura.setRepeated(true);
    blok_tekstura.setRepeated(true);

//wektory obiektow
    vector<shared_ptr<Platforma>> otoczenie;
    vector<shared_ptr<Sprite>> bonusy;
    vector<shared_ptr<Przeciwnik>> enemies;
     vector<shared_ptr<Sprite>> zycia;
//tlo
    Sprite tlo;
    tlo.setPosition(0, 0);
    tlo.setTexture(tlo_tekstura);
    tlo.setScale(10, 10);





//postac
    Vector2f position(50, window.getSize().y - 100);
    Vector2f scale(2.5, 2.5);
    Bohater postac(position,scale,0, window.getSize().x, 0, window.getSize().y);


//mapa
    tworzenie_scian(otoczenie,bonusy, enemies, sciana_tekstura, blok_tekstura,bonus_tekstura);

//serduszka
               for(int i=0; i<postac.get_lives(); i++){
                   shared_ptr<Sprite> serduszko;
                   serduszko = make_shared<Sprite>(zycia_tekstura);
                   serduszko->setPosition(window.getSize().x-30-((i+1)*serduszko->getGlobalBounds().width),window.getSize().y-30-serduszko->getGlobalBounds().height);
                   zycia.emplace_back(serduszko);
               }








    //warunek zwyciestwa
    Bonus medal(Vector2f(0.8, 0.8), medal_tekstura, Vector2f(25, 25));


    //pocisk
    bool wystrzelony = false;


    Clock clock;
    Clock shot_cooldown;
    Clock jump_cooldown;
    shot_cooldown.restart();
    jump_cooldown.restart();
    srand(time(NULL));
    bool defeat=false;
    bool victory=false;
    while (window.isOpen()) {

        Time elapsed = clock.restart();
        window.clear(Color::Black);
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
                break;
            }
        }
        if(!defeat && !victory){
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
                if (wystrzelony_pocisk->check_collision(**enemy)) {
                    Pocisk::wystrzelone_pociski.erase(wystrzelony_pocisk);
                    enemy->get()->set_lives(-1);
                    if (!enemy->get()->is_alive()) {
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
                zycia.erase(zycia.end()-1);
                if (!postac.is_alive()) {
                   defeat=true;
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
                        shared_ptr<Sprite> serduszko;
                        serduszko = make_shared<Sprite>(zycia_tekstura);
                        serduszko->setPosition(window.getSize().x-30-((zycia.size()+1)*serduszko->getGlobalBounds().width),window.getSize().y-30-serduszko->getGlobalBounds().height);
                        zycia.emplace_back(serduszko);
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
            victory=true;
        }






//enemy animation

        for (auto& enemy : enemies) {
            if (postac.getGlobalBounds().left + postac.getGlobalBounds().width > enemy->left_borderline and
                postac.getGlobalBounds().left  < enemy->right_borderline and
                postac.getGlobalBounds().top > enemy->getGlobalBounds().top - enemy->getGlobalBounds().height and
                postac.getGlobalBounds().top + postac.getGlobalBounds().height <
                enemy->getGlobalBounds().top + 2 * enemy->getGlobalBounds().height) {
                enemy->setTexture(enemy->static_enemy_texture(), true);
                if (postac.getGlobalBounds().left < enemy->getGlobalBounds().left) {
                    enemy->setScale(-2.5, 2.5);
                    enemy->setFacing(false);
                }
                if (postac.getGlobalBounds().left > enemy->getGlobalBounds().left) {
                    enemy->setScale(2.5, 2.5);
                    enemy->setFacing(true);
                }

                if (!enemy->wrogi_wystrzelony and enemy->shot_cooldown.getElapsedTime().asSeconds() >= 1) {
                    enemy->shoot();
                    enemy->shot_cooldown.restart();
                    enemy->wrogi_wystrzelony = true;
                } else if (enemy->wrogi_wystrzelony) {
                    enemy->wrogi_wystrzelony = false;
                }
            } else {
                enemy->animate(elapsed);
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

        for (const auto& ksztalt:otoczenie) {
            window.draw(*ksztalt);
        }
        for (auto& enemy : enemies) {
            window.draw(*enemy);
        }
        for (const auto& bonus:bonusy) {
            window.draw(*bonus);
        }
        for(const auto& zycie:zycia){
            window.draw(*zycie);
        }
        window.draw(postac);
        window.draw(medal);
        window.draw(poziom);
  }
  else if(defeat && !victory){
 //usuwanie mapy
            for(auto enemy = enemies.begin();
                enemy < enemies.end(); ++enemy){
                enemies.erase(enemy);
            }
            for(auto bonus = bonusy.begin();
                bonus < bonusy.end(); ++bonus){
                bonusy.erase(bonus);
            }
            for(auto blok = otoczenie.begin();
                blok < otoczenie.end(); ++blok){
                otoczenie.erase(blok);
            }
            for (auto wystrzelony_pocisk = Pocisk::wrogie_pociski.begin();
                 wystrzelony_pocisk < Pocisk::wrogie_pociski.end(); ++wystrzelony_pocisk) {
                Pocisk::wrogie_pociski.erase(wystrzelony_pocisk);
            }
            for (auto wystrzelony_pocisk = Pocisk::wystrzelone_pociski.begin();
                 wystrzelony_pocisk < Pocisk::wystrzelone_pociski.end(); ++wystrzelony_pocisk) {
                Pocisk::wystrzelone_pociski.erase(wystrzelony_pocisk);
            }
            window.clear(Color::Black);
            Sprite porazka;
            porazka.setPosition(0,0);
            porazka.setTexture(przegrana_tekstura);
            porazka.setScale(5,5);
            window.draw(porazka);
            if(Keyboard::isKeyPressed(Keyboard::Space)){
                postac.shot_cooldown=1;
                postac.set_points(0);
                postac.setPosition(position);
                postac.set_lives(difficulty_level::bohater_hp);
                for(int i=0; i<postac.get_lives(); i++){
                    shared_ptr<Sprite> serduszko;
                    serduszko = make_shared<Sprite>(zycia_tekstura);
                    serduszko->setPosition(window.getSize().x-30-((i+1)*serduszko->getGlobalBounds().width),window.getSize().y-30-serduszko->getGlobalBounds().height);
                    zycia.emplace_back(serduszko);
                }
                tworzenie_scian(otoczenie,bonusy, enemies, sciana_tekstura, blok_tekstura,bonus_tekstura);
                defeat=!defeat;

            }

        }
   else if(!defeat && victory){
//usuwanie mapy

          for(auto enemy = enemies.begin();
              enemy < enemies.end(); ++enemy){
              enemies.erase(enemy);
          }
          for(auto bonus = bonusy.begin();
               bonus < bonusy.end(); ++bonus){
               bonusy.erase(bonus);
          }
          for(auto blok = otoczenie.begin();
               blok < otoczenie.end(); ++blok){
               otoczenie.erase(blok);
          }
          for (auto wystrzelony_pocisk = Pocisk::wrogie_pociski.begin();
               wystrzelony_pocisk < Pocisk::wrogie_pociski.end(); ++wystrzelony_pocisk) {
               Pocisk::wrogie_pociski.erase(wystrzelony_pocisk);
          }
          for (auto wystrzelony_pocisk = Pocisk::wystrzelone_pociski.begin();
               wystrzelony_pocisk < Pocisk::wystrzelone_pociski.end(); ++wystrzelony_pocisk) {
               Pocisk::wystrzelone_pociski.erase(wystrzelony_pocisk);
          }
          for (auto serduszko = zycia.begin();
               serduszko < zycia.end(); ++serduszko) {
               zycia.erase(serduszko);
          }
            window.clear(Color::Black);
            Sprite zwyciestwo;
            zwyciestwo.setPosition(0,0);
            zwyciestwo.setTexture(wygrana_testura);
            zwyciestwo.setScale(window.getSize().x/1152,window.getSize().y/648);
            window.draw(zwyciestwo);
            if(Keyboard::isKeyPressed(Keyboard::Space)){
                postac.shot_cooldown=1;
                postac.set_points(0);
                postac.setPosition(position);
                postac.set_lives(difficulty_level::bohater_hp);
                for(int i=0; i<postac.get_lives(); i++){
                    shared_ptr<Sprite> serduszko;
                    serduszko = make_shared<Sprite>(zycia_tekstura);
                    serduszko->setPosition(window.getSize().x-30-((i+1)*serduszko->getGlobalBounds().width),window.getSize().y-30-serduszko->getGlobalBounds().height);
                    zycia.emplace_back(serduszko);
                }
                tworzenie_scian(otoczenie,bonusy, enemies, sciana_tekstura, blok_tekstura,bonus_tekstura);
                victory=!victory;
            }

        }





        window.display();
    }
    return 0;
}
