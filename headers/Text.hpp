//
// Created by vladi on 4/15/2022.
//

#ifndef OOP_TEXT_HPP
#define OOP_TEXT_HPP

#include <SFML/Graphics.hpp>
#include "Input.hpp"

class Text: public Input{
private:
    sf::Text textRect;

public:
    Text(std::string, sf::Vector2f, sf::Vector2f, sf::Color = sf::Color::Transparent, sf::Color = sf::Color::Transparent);
    sf::Text getTextRect() const override;
    void setTextRect();

    sf::Vector2f getSize() const;

    bool listen(sf::Event, sf::Vector2i) override;
    void draw(sf::RenderTarget&, sf::RenderStates) const override;

    [[nodiscard]] Input* clone() const override;

};

#endif //OOP_TEXT_HPP