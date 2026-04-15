#include <epr/graphics/texture.hpp>

#include <vector>

epr::graphics::Texture epr::graphics::Texture::load(std::string &texture) {
    int cursor = 0;

    int texture_size = 0;
    bool flip_texture = false;

    std::string acc = "";

    while (texture[cursor] != ';') {
        acc += texture[cursor];
        cursor++;
    }
    cursor++;
    texture_size = std::stoi(acc);
    acc.clear();

    epr::graphics::Texture temp_texture(texture_size);

    if (texture[cursor] == 'F') flip_texture = true;
    cursor++;

    std::vector <epr::graphics::rgba> converted_texture;

    for (int i = 0; i < (texture_size * texture_size); i++) {
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

    if (flip_texture) {
        temp_texture.data = converted_texture;
    } else {
        for (int i = 0; i < texture_size; i++) {
            for (int j = 0; j < texture_size; j++) {
                int inverse_i = texture_size - 1 - i;
                int inverse_j = texture_size - 1 - j;

                temp_texture.data[i * texture_size + j] = converted_texture[inverse_i * texture_size + inverse_j];
            }
        }
    }

    return temp_texture;
}