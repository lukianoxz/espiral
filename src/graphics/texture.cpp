#include <epr/graphics/texture.hpp>

void epr::graphics::Texture::load(std::string texture) {
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

    if (texture[cursor] == 'F') flip_texture = true;
    cursor++;

    for (int i = 0; i < texture_size; i++) {
        for (int j = 0; j < texture_size; j++) {
            
        }
    }
}