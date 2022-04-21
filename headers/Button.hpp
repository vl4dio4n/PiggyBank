//
// Created by vladi on 4/14/2022.
//

#ifndef OOP_BUTTON_HPP
#define OOP_BUTTON_HPP

#include <SFML/Graphics.hpp>
#include "Input.hpp"

class Button: public Input{
private:
    sf::RectangleShape rectHovered;
    std::string action;
    bool isHovered;

    sf::Text getTextRect() const override;

public:
    Button(std::string, std::string, sf::Vector2f, sf::Vector2f, sf::Color, sf::Color);

    std::string getAction();

    bool listen(sf::Event, sf::Vector2i) override;
    void draw(sf::RenderTarget&, sf::RenderStates) const override;

    [[nodiscard]] Input* clone() const override;
};


#endif //OOP_BUTTON_HPP