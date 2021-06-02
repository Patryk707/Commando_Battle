#ifndef WCZYTYWANIE_HPP
#define WCZYTYWANIE_HPP
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;


Texture load_texture(const string &filename_with_path){
    Texture texture;
    if(!texture.loadFromFile(filename_with_path)){
        cerr<<"Could not load texture"<<endl;
    }
    return texture;
}

#endif // WCZYTYWANIE_HPP
