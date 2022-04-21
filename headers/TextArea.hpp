//
// Created by vladi on 4/14/2022.
//

#ifndef OOP_TEXTAREA_HPP
#define OOP_TEXTAREA_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include "Input.hpp"

class TextArea: public Input{
private:
    sf::RectangleShape rectSelected;
    std::string value;
    unsigned int maxLength;
    bool isSelected;

    void insertChar(char);
    void deleteChar();
    static bool checkValidChar(unsigned int);

    sf::Text getTextRect() const override;

public:
    TextArea(std::string, sf::Vector2f, sf::Vector2f, sf::Color, sf::Color);

    void setValue(std::string = "");
    std::string getValue() const;

    void draw(sf::RenderTarget&, sf::RenderStates) const override;
    bool listen(sf::Event, sf::Vector2i) override;

    [[nodiscard]] Input* clone() const override;
};

#endif //OOP_TEXTAREA_HPP