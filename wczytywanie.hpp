#ifndef WCZYTYWANIE_HPP
#define WCZYTYWANIE_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "dane_platformy.hpp"

using namespace sf;
using namespace std;

Texture load_texture(const string& filename_with_path) {
    Texture texture;
    if (!texture.loadFromFile(filename_with_path)) {
        cerr << "Could not load texture" << endl;
    }
    return texture;
}

vector<dane_platformy> load_map(const string& filename_with_path) {

    vector<dane_platformy> mapa;

    fstream file_input(filename_with_path);
    if (file_input.good()) {
        for (string line; getline(file_input, line);) {
            if (line[0] != '#') {
                stringstream line_stream(line);

                string typ_platformy;
                float pos_x, pos_y, scale_x, scale_y, gorna_granica, dolna_granica;

                line_stream >> typ_platformy;
                line_stream >> pos_x;
                line_stream >> pos_y;
                line_stream >> scale_x;
                line_stream >> scale_y;
                line_stream >> gorna_granica;
                line_stream >> dolna_granica;

                mapa.push_back({typ_platformy, {pos_x, pos_y}, {scale_x, scale_y}, gorna_granica, dolna_granica});
            }
        }
        file_input.close();

    } else {
        cerr << "Could not read a map file " << filename_with_path;
    }

    return mapa;
}

#endif // WCZYTYWANIE_HPP
