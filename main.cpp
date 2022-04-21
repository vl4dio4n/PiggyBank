#include "headers/App.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode((unsigned int) 1400, (unsigned int) 900), "PiggyBank", sf::Style::Close);
    window.setFramerateLimit((unsigned int) 60);
    App app(window);
    app.run();
    return 0;
}