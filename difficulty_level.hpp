#ifndef DIFFICULTY_LEVEL_HPP
#define DIFFICULTY_LEVEL_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;


struct difficulty_level {

    inline static string level_name;
    inline static int bohater_hp, przeciwnik_hp;
    inline static float bohater_speed, bohater_bullet_speed, przeciwnik_speed, przeciwnik_bullet_speed;

    static void load_diff_level(const string& filename_with_path) {

        string level_line;

        fstream file_input(filename_with_path);
        if (file_input.good()) {
            for (string line; getline(file_input, line);) {
                if (line[0] != '#') {
                    level_line = line;
                }
            }
            file_input.close();

            stringstream line_stream(level_line);

            line_stream >> level_name;
            level_name="level: "+level_name;
            line_stream >> bohater_hp;
            line_stream >> bohater_speed;
            line_stream >> bohater_bullet_speed;
            line_stream >> przeciwnik_hp;
            line_stream >> przeciwnik_speed;
            line_stream >> przeciwnik_bullet_speed;

        } else {
            cerr << "Could not read a configuration file " << filename_with_path;
        }
    }
};

#endif //DIFFICULTY_LEVEL_HPP
