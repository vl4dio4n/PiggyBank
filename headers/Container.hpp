//
// Created by vladi on 4/18/2022.
//

#ifndef OOP_CONTAINER_HPP
#define OOP_CONTAINER_HPP

#include <string>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Text.hpp"
#include "Evidence.hpp"

class Container: public sf::Drawable{
private:
    bool isHovered;
    sf::Vector2f pos;
    sf::Vector2f size;
    sf::Clock clickClock;
    std::shared_ptr <Text> textDate;
    std::shared_ptr <Text> textValue;
    std::vector <std::shared_ptr<Text>> textInfo;
    std::shared_ptr <Evidence> evidence;

    static int maxLength;
    static sf::Vector2i margin;

public:
    Container(const std::string& value, const std::string& date, const std::string& info, sf::Vector2f);

    void setPos(sf::Vector2f);
    [[nodiscard]] sf::Vector2f getPos() const;
    [[nodiscard]] sf::Vector2f getSize() const;
    [[nodiscard]] Evidence getEvidence() const;

    [[nodiscard]] bool checkInsideBox(sf::Vector2i) const;
    bool checkDoubleClick();
    bool listen(sf::Event, sf::Vector2i);
    void getContainerTexture(sf::Texture&) const;

    void draw(sf::RenderTarget&, sf::RenderStates) const override;

    friend bool operator<(const Container& a, const Container& b);
};

#endif //OOP_CONTAINER_HPP