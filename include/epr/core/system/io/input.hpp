#ifndef EPR_CORE_SYSTEM_IO_INPUT_HPP
#define EPR_CORE_SYSTEM_IO_INPUT_HPP

#ifndef _WIN32

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

namespace epr::system::io {
    inline int getch(void) {
        struct termios oldt, newt;
        int ch;
        int oldf;

        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

        ch = getchar();

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, oldf);

        return ch;
    }
}

#endif

#endif