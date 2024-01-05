#include "application.hpp"

//std
#include <iostream>
#include <cstdlib>
#include <stdexcept>

int main() {
    vkte::Application app{};

    try {
        app.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
