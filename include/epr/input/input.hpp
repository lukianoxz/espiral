#ifndef EPR_INPUT_HPP
#define EPR_INPUT_HPP

#ifndef _WIN32

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

namespace epr::input {
    struct Input {
        Input() {
            // get actual config
            tcgetattr(STDIN_FILENO, &oldt);
            newt = oldt;

            // disable echo mode
            newt.c_lflag &= ~(ICANON | ECHO);

            // apply new config
            tcsetattr(STDIN_FILENO, TCSANOW, &newt);

            // config to non-blocking
            oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
            fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
        }

        inline int read() {
            return getchar();
        }

        ~Input() {
            // restaure original config
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
            fcntl(STDIN_FILENO, F_SETFL, oldf);
        }
    private:
        struct termios oldt, newt;
        int oldf;
    };
}

#endif

#endif