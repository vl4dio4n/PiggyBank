//
// Created by vladi on 4/12/2022.
//

#ifndef OOP_APP_HPP
#define OOP_APP_HPP

#include <SFML/Graphics.hpp>
#include "View.hpp"
#include <vector>

class App{
private:
    sf::RenderWindow& window;
    std::vector <View*> views;

public:
    explicit App(sf::RenderWindow&);

    [[nodiscard]] static bool checkViewCenter(float, float, float) ;
    void changeView(const std::string&);
    void run();

    ~App();
};


#endif //OOP_APP_HPP