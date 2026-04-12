#include <iostream>
#include <epr/espiral.hpp>

int main() {
    std::cout << "Hello, World!\n";

    epr::graphics::Display disp(3, 3);
    
    disp.draw_pixel(0, 0, {255, 0, 0});
    disp.draw_pixel(2, 2, {255, 0, 0});

    disp.show();

    return 0;
}