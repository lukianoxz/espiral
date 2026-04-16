#include <epr/graphics/texture.hpp>

#include <vector>

epr::graphics::Texture epr::graphics::Texture::load(std::string &texture) {
    int cursor = 0;

    int texture_size_x = 0;
    int texture_size_y = 0;

    std::string acc = "";

    while (texture[cursor] != ';') {
        acc += texture[cursor];
        cursor++;
    }
    cursor++;
    texture_size_x = std::stoi(acc);
    acc.clear();

    while (texture[cursor] != ';') {
        acc += texture[cursor];
        cursor++;
    }
    cursor++;
    texture_size_y = std::stoi(acc);
    acc.clear();

    epr::graphics::Texture temp_texture(texture_size_x, texture_size_y);

    std::vector <epr::graphics::rgba> converted_texture;

    for (int i = 0; i < (texture_size_y * texture_size_x); i++) {
        epr::graphics::rgba temp_color;

        // channel red
        acc = texture.substr(cursor, 3);
        temp_color.r = std::stoi(acc);
        cursor += 3;

        // channel green
        acc = texture.substr(cursor, 3);
        temp_color.g = std::stoi(acc);
        cursor += 3;

        // channel blue
        acc = texture.substr(cursor, 3);
        temp_color.b = std::stoi(acc);
        cursor += 3;

        // channel alpha
        acc = texture.substr(cursor, 3);
        temp_color.a = std::stoi(acc);
        cursor += 3;

        converted_texture.push_back(temp_color);
    }
    
    temp_texture.data = std::move(converted_texture);

    return temp_texture;
}