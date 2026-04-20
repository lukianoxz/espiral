#ifndef EPR_CORE_SYSTEM_IO_FILE_LOADER_HPP
#define EPR_CORE_SYSTEM_IO_FILE_LOADER_HPP

#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <iostream>

namespace epr::system::io {
    static std::string load_file(std::string path) {
        std::filesystem::path img_path = std::filesystem::current_path() / path;

        std::ifstream file(img_path);

        if (file.is_open()) {
            std::stringstream buffer;

            buffer << file.rdbuf();
            file.close();

            return buffer.str();
        } else {
            std::cerr << "Error during open file\n";
            std::cerr << "Attempted path: " << img_path << "\n";
            std::exit(-1);
        }

        return "";
    }
}

#endif