#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "bohater.h"
#include "przeciwnik.h"
#include "pocisk.h"
#include <vector>
#include "wczytywanie.hpp"
#include "bonus.h"

using namespace std;
using namespace sf;

vector<Pocisk> Pocisk::wystrzelone_pociski;
vector<Pocisk> Pocisk::wrogie_pociski;

void tworzenie_scian(vector<unique_ptr<Sprite>> &otoczenie, Texture &sciana_tekstura,Texture &blok_tekstura,RenderWindow &window, Bohater &postac){
    auto block0=make_unique<Sprite>();
    block0->setTexture(blok_tekstura);
    block0->setPosition(0,window.getSize().y-50);
    block0->setTextureRect(IntRect(0,0,window.getSize().x,50));
    otoczenie.emplace_back(move(block0));

    auto block1=make_unique<Sprite>();
    block1->setTexture(blok_tekstura);
    block1->setPosition(150,window.getSize().y-50-postac.getGlobalBounds().height);
    block1->setScale(0.5,0.43);
    otoczenie.emplace_back(move(block1));

    auto block2=make_unique<Sprite>();
    block2->setTexture(blok_tekstura);
    block2->setPosition(214,window.getSize().y-50-2*postac.getGlobalBounds().height);
    block2->setScale(0.5,0.86);
    otoczenie.emplace_back(move(block2));


    auto wall2=make_unique<Sprite>();
    wall2->setTexture(sciana_tekstura);
    wall2->setPosition(385,window.getSize().y-152);
    wall2->setScale(3,0.2);
    otoczenie.emplace_back(move(wall2));

    auto block3=make_unique<Sprite>();
    block3->setTexture(blok_tekstura);
    block3->setPosition(window.getSize().x/2+200,window.getSize().y-50-1*postac.getGlobalBounds().height);
    block3->setScale(0.5,0.43);
    otoczenie.emplace_back(move(block3));

    auto block4=make_unique<Sprite>();
    block4->setTexture(blok_tekstura);
    block4->setPosition(window.getSize().x/2+264,window.getSize().y-50-2*postac.getGlobalBounds().height);
    block4->setScale(2.5,0.86);
    otoczenie.emplace_back(move(block4));

    auto block5=make_unique<Sprite>();
    block5->setTexture(blok_tekstura);
    block5->setPosition(window.getSize().x/2+584,window.getSize().y-50-3*postac.getGlobalBounds().height);
    block5->setScale(2,1.29);
    otoczenie.emplace_back(move(block5));

    auto wall3=make_unique<Sprite>();
    wall3->setTexture(sciana_tekstura);
    wall3->setScale(1.75,0.2);
    wall3->setPosition(window.getSize().x/2+264,window.getSize().y-60-3*postac.getGlobalBounds().height-30);
    otoczenie.emplace_back(move(wall3));

    auto block6=make_unique<Sprite>();
    block6->setTexture(blok_tekstura);
    block6->setPosition(window.getSize().x/2-210,window.getSize().y-80-3*postac.getGlobalBounds().height);
    block6->setTextureRect(IntRect(0,0,128,64));
    block6->setScale(2.8,0.5);
    otoczenie.emplace_back(move(block6));

    auto block7=make_unique<Sprite>();
    block7->setTexture(blok_tekstura);
    block7->setPosition(window.getSize().x/2-594,window.getSize().y-80-4*postac.getGlobalBounds().height);
    //block7->setTextureRect(IntRect(0,0,128,64));
    block7->setScale(3,0.43);
    otoczenie.emplace_back(move(block7));
}



int main()
{
    RenderWindow window(VideoMode(1600,900 ),"Projekt");
    window.setFramerateLimit(60);
    Event event;



    //Texture platformy_tekstura=loadtexture("./../Projekt_proba1/Environment/ground_grass_small.png");
    //platformy_tekstura.setRepeated(true);
    //Texture bohater_tekstura=loadtexture("./../Projekt_proba2/john_run.png");
    Texture sciana_tekstura=load_texture("../grass.png");
    Texture blok_tekstura=load_texture("../grassMid.png");
    //Texture przeciwnik_tekstura=load_texture("./../Projekt_proba_3/grunt.png");
    Texture bonus_tekstura=load_texture("../star.png");
    sciana_tekstura.setRepeated(true);
    blok_tekstura.setRepeated(true);

    vector<unique_ptr<Sprite>> otoczenie;


    //postac
    Vector2f position(50, window.getSize().y-80);
    Bohater postac(position);
    postac.setScale(2.5,2.5);
    //postac.setOrigin(float(bohater_tekstura.getSize().x) / 2, float(bohater_tekstura.getSize().y) / 2);
    postac.setBounds(0, window.getSize().x, 0, window.getSize().y);
    postac.setSpeed(200, 200);
    //walls
    tworzenie_scian(otoczenie,sciana_tekstura,blok_tekstura,window, postac);






    //przeciwnik
    //vector<unique_ptr<Sprite>> przeciwnicy;
    //auto przeciwnik1=make_unique<Przeciwnik>(Vector2f(0.4,0.4));
    //przeciwnik1->setTexture(przeciwnik_tekstura);
    //przeciwnik1->set_position(Vector2f(1000,500));
    //przeciwnicy.emplace_back(move(przeciwnik1));

    //auto przeciwnik2=make_unique<Przeciwnik>(Vector2f(0.4,0.4));
    //przeciwnik2->setTexture(przeciwnik_tekstura);
    //przeciwnik2->set_position(Vector2f(500,500));
    //przeciwnicy.emplace_back(move(przeciwnik2));

   // auto przeciwnik3=make_unique<Przeciwnik>(Vector2f(0.4,0.4));
    //przeciwnik3->setTexture(przeciwnik_tekstura);
    //przeciwnik3->set_position(Vector2f(800,500));
    //przeciwnicy.emplace_back(move(przeciwnik3));


    //----------------
    vector<Przeciwnik> enemies;
    Przeciwnik enemy1(Vector2f(-2.5,2.5));
    //enemy1.setTexture(przeciwnik_tekstura);
    enemy1.set_position(Vector2f(400,window.getSize().y-80));
    //enemy1.setOrigin(float(przeciwnik_tekstura.getSize().x) / 2, float(przeciwnik_tekstura.getSize().y) / 2);
    enemy1.shot_cooldown.restart();
    enemy1.setBounds(280,window.getSize().x/2+200);
    enemies.emplace_back(enemy1);

    //Przeciwnik enemy2(Vector2f(-2.5,2.5));
    //enemy2.setTexture(przeciwnik_tekstura);
    //enemy2.set_position(Vector2f(700,window.getSize().y-80));
    //enemy2.setOrigin(float(przeciwnik_tekstura.getSize().x) / 2, float(przeciwnik_tekstura.getSize().y) / 2);
    //enemy2.shot_cooldown.restart();
    //enemy2.setBounds(280,window.getSize().x/2+200);
    //enemies.emplace_back(enemy2);

    //Przeciwnik enemy3(Vector2f(-2.5,2.5));
    //enemy3.setTexture(przeciwnik_tekstura);
    //enemy3.set_position(Vector2f(400,window.getSize().y-178));
    //enemy3.setOrigin(float(przeciwnik_tekstura.getSize().x) / 2, float(przeciwnik_tekstura.getSize().y) / 2);
    //enemy3.shot_cooldown.restart();
    //enemy3.setBounds(385,769);
    //enemies.emplace_back(enemy3);

    //Przeciwnik enemy4(Vector2f(-2.5,2.5));
    //enemy4.setTexture(przeciwnik_tekstura);
    //enemy4.set_position(Vector2f(window.getSize().x/2+300,window.getSize().y-76-2*postac.getGlobalBounds().height));
    //enemy4.setOrigin(float(przeciwnik_tekstura.getSize().x) / 2, float(przeciwnik_tekstura.getSize().y) / 2);
    //enemy4.shot_cooldown.restart();
    //enemy4.setBounds(window.getSize().x/2+264,window.getSize().x/2+584);
    //enemies.emplace_back(enemy4);

    //Przeciwnik enemy5(Vector2f(-2.5,2.5));
    //enemy5.setTexture(przeciwnik_tekstura);
    //enemy5.set_position(Vector2f(window.getSize().x/2,627));
    //enemy5.setOrigin(float(przeciwnik_tekstura.getSize().x) / 2, float(przeciwnik_tekstura.getSize().y) / 2);
    //enemy5.shot_cooldown.restart();
    //enemy5.setBounds(window.getSize().x/2-210,window.getSize().x/2+150);
    //enemies.emplace_back(enemy5);

    //bonusy
    vector<unique_ptr<Sprite>> bonusy;
    vector<Bonus> bonusy_klasa;

    auto bonus1=make_unique<Sprite>();
    bonus1->setTexture(bonus_tekstura);
    bonus1->setPosition(550,window.getSize().y-115);
    bonus1->setScale(0.5,0.5);
    bonusy.emplace_back(move(bonus1));

    auto bonus2=make_unique<Sprite>();
    bonus2->setTexture(bonus_tekstura);
    bonus2->setPosition(window.getSize().x-200,window.getSize().y-115-3*postac.getGlobalBounds().height);
    bonus2->setScale(0.5,0.5);
    bonusy.emplace_back(move(bonus2));

    auto bonus3=make_unique<Sprite>();
    bonus3->setTexture(bonus_tekstura);
    bonus3->setPosition(530,535);
    bonus3->setScale(0.5,0.5);
    bonusy.emplace_back(move(bonus3));

    //Bonus bonus4(Vector2f(0.5,0.5),bonus_tekstura,Vector2f(200,200));
    //bonusy_klasa.emplace_back(bonus4);



    //pocisk
    bool wystrzelony=false;




    Clock clock;
    Clock shot_cooldown;
    shot_cooldown.restart();
        srand(time(NULL));
    while(window.isOpen()){
        Time elapsed = clock.restart();
        window.clear(Color::Black);
        window.pollEvent(event);
        if(event.type==Event::Closed){
            window.close();
            break;
        }

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
            wystrzelony_pocisk.set_speed(wystrzelony_pocisk.getFacing() ? 3 : -3);
        }
        for (auto& wrogi_pocisk : Pocisk::wrogie_pociski) {
            window.draw(wrogi_pocisk);
            wrogi_pocisk.set_speed(wrogi_pocisk.getFacing() ? 3 : -3);
        }

        //otoczenie a pociski
        for(auto wystrzelony_pocisk = Pocisk::wystrzelone_pociski.begin();
            wystrzelony_pocisk<Pocisk::wystrzelone_pociski.end(); ++wystrzelony_pocisk){
            for(auto &sciana : otoczenie){
                if(wystrzelony_pocisk->check_collision(*sciana)){
                    Pocisk::wystrzelone_pociski.erase(wystrzelony_pocisk);
                }
            }
        }

        for(auto wystrzelony_pocisk = Pocisk::wrogie_pociski.begin();
            wystrzelony_pocisk < Pocisk::wrogie_pociski.end(); ++wystrzelony_pocisk){
            for(auto &sciana : otoczenie){
                if(wystrzelony_pocisk->check_collision(*sciana)){
                    Pocisk::wrogie_pociski.erase(wystrzelony_pocisk);
                }
            }
        }


        //przeciwnik a pocisk
        for(auto wystrzelony_pocisk = Pocisk::wystrzelone_pociski.begin();
            wystrzelony_pocisk<Pocisk::wystrzelone_pociski.end(); ++wystrzelony_pocisk){
            for(auto enemy = enemies.begin();
                enemy<enemies.end(); ++enemy){
                if(wystrzelony_pocisk->check_collision(*enemy)){
                    Pocisk::wystrzelone_pociski.erase(wystrzelony_pocisk);
                   enemy->set_lives(-1);
                   if(!enemy->is_alive()){
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
                postac.set_lives(-1);
                if (!postac.is_alive()) {
                    postac.move(10000, 10000);
                }
            }
        }

        //for (auto &bonus:bonusy) {
         //   if (postac.check_collision(*bonus)) {
        //       cout<<"kolizja";
        //    }
        //}





        //enemy animation

        for(auto &enemy : enemies){
            if(postac.getGlobalBounds().left>enemy.left_borderline and
                    postac.getGlobalBounds().left+postac.getGlobalBounds().width<enemy.right_borderline and
                    postac.getGlobalBounds().top>enemy.getGlobalBounds().top-enemy.getGlobalBounds().height and
                    postac.getGlobalBounds().top+postac.getGlobalBounds().height<enemy.getGlobalBounds().top+2*enemy.getGlobalBounds().height){
                if(postac.getGlobalBounds().left<enemy.getGlobalBounds().left){
                    enemy.setScale(-2.5,2.5);
                    enemy.setFacing(false);
                }
                if(postac.getGlobalBounds().left>enemy.getGlobalBounds().left){
                    enemy.setScale(2.5,2.5);
                    enemy.setFacing(true);
                }

                if (!enemy.wrogi_wystrzelony and enemy.shot_cooldown.getElapsedTime().asSeconds() >= 1) {
                    enemy.shoot();
                    enemy.shot_cooldown.restart();
                    enemy.wrogi_wystrzelony = true;
                } else if (enemy.wrogi_wystrzelony) {
                    enemy.wrogi_wystrzelony = false;
                }
            }
            else{
            enemy.animate(elapsed);
            }
        }


        //collision postac
        postac.animate(elapsed,otoczenie);




        //drawing
        for(const auto &ksztalty:otoczenie){
            window.draw(*ksztalty);
        }
        //for(const auto &przeciwnik:przeciwnicy){
        //    window.draw(*przeciwnik);
        //}
        for(auto &enemy : enemies){
            window.draw(enemy);
        }
        for(const auto &bonus:bonusy){
            window.draw(*bonus);
        }
        //for(auto &bonus:bonusy_klasa){
        //    window.draw(bonus);
        //}
        window.draw(postac);



        window.display();
       }
    return 0;
}
