//
// Created by vladi on 4/14/2022.
//

#ifndef OOP_INPUT_HPP
#define OOP_INPUT_HPP

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

class Input: public sf::Drawable{
protected:
    std::string label;
    sf::RectangleShape rect;
    sf::Font font;
    unsigned int characterSize;

    static sf::Color setOpacity(sf::Color, unsigned int);

    bool checkInsideBox(sf::Vector2i);
    virtual sf::Text getTextRect() const = 0;

    Input(const Input&) = default;
    Input& operator = (const Input&) = default;

public:
    Input(std::string, sf::Vector2f, sf::Vector2f, sf::Color, sf::Color);

    void draw(sf::RenderTarget&, sf::RenderStates) const override = 0;
    virtual bool listen(sf::Event, sf::Vector2i) = 0;

    std::string getLabel();

    virtual Input* clone() const = 0;
};

#endif //OOP_INPUT_HPP
