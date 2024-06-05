#include "font-enum.h"
#include "font-manager.h"
#include "surfer.h"
#include "word.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc > 2) {
        std::cerr << "Usage: sfml-surfer [html file]" << std::endl;
    } else if (argc == 2) {
        Surfer::runFile(argv[1]);
    } else {
        Surfer::runPrompt();
    }

    return 0;
}
