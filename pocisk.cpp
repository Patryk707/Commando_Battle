#include "pocisk.h"
#include "przeciwnik.h"


using namespace sf;
using namespace std;

Pocisk::Pocisk(Vector2f position,bool face,bool enemy_bullet)
{   if(enemy_bullet){
        setTexture(pocisk_wroga_texture());
    }
    else{
        setTexture(pocisk_gracza_texture());
    }
    if(face){
        setScale(0.5,0.5);
    }
    else{
        setScale(-0.5,0.5);
    }
    setPosition(position);    
    facing=face;
}

void Pocisk::set_speed(float speed){
    move(speed,0);
}
void Pocisk::set_position(Vector2f new_position){
    setPosition(new_position);
}
float Pocisk::top(){
    return getGlobalBounds().top;
}
float Pocisk::bottom(){
    return getGlobalBounds().top+getGlobalBounds().height;
}
float Pocisk::left(){
    return getGlobalBounds().left;
}
float Pocisk::right(){
    return getGlobalBounds().left+getGlobalBounds().width;
}
bool Pocisk::getFacing(){
    return facing;
}
bool Pocisk::check_collision(Sprite &przeciwnik ){
        if(getGlobalBounds().intersects(przeciwnik.getGlobalBounds())){
            return true;
        }
    return false;
}
