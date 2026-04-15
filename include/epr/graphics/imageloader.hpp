#ifndef EPR_GRAPHICS_IMAGELOADER_HPP
#define EPR_GRAPHICS_IMAGELOADER_HPP

#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <iostream>

namespace epr::graphics {
    static std::string load_image(std::string image_name) {
        std::filesystem::path img_path = std::filesystem::current_path() / image_name;

        std::ifstream file(img_path);

        if (file.is_open()) {
            std::stringstream buffer;

            buffer << file.rdbuf();
            file.close();

            return buffer.str();
        } else {
            std::cerr << "Error during open image\n";
            std::cerr << "Attempted path: " << img_path << "\n";
            std::exit(-1);
        }

        return "";
    }
}

#endif