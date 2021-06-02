#include "pocisk.h"
#include "przeciwnik.h"


using namespace sf;
using namespace std;

Pocisk::Pocisk(Vector2f position,bool face)
{   this->setPosition(position);
    this->setRadius(this->promien_pocisku);
    this->setFillColor(Color::Magenta);
    this->setOrigin(this->promien_pocisku,this->promien_pocisku);
    facing=face;
}

void Pocisk::set_speed(float speed){
    this->move(speed,0);
}
void Pocisk::set_position(sf::Vector2f new_position){
    this->setPosition(new_position);
}
float Pocisk::top(){
    return this->getPosition().y-this->getRadius();
}
float Pocisk::bottom(){
    return this->getPosition().y+this->getRadius();
}
float Pocisk::left(){
    return this->getPosition().x-this->getRadius();
}
float Pocisk::right(){
    return this->getPosition().x+this->getRadius();
}
bool Pocisk::getFacing(){
    return facing;
}
bool Pocisk::check_collision(Sprite &przeciwnik ){
        if(this->getGlobalBounds().intersects(przeciwnik.getGlobalBounds())){
            return true;
        }
    return false;
}
