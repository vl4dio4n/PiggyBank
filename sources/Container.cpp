//
// Created by vladi on 4/18/2022.
//

#include "../headers/Container.hpp"
#include <memory>

int Container::maxLength = 60;
sf::Vector2i Container::margin = {30, 30};

Container::Container(const std::string& value, const std::string& date, const std::string& info, sf::Vector2f pos):
        isHovered(false),
        pos(pos),
        textDate{new Text{"Date: " + date, sf::Vector2f {50.f, 30.f}, sf::Vector2f {0.f, 60.f}}},
        textValue{new Text{"Value: " + value, sf::Vector2f {600.f, 30.f}, sf::Vector2f {0.f, 60.f}}},
        evidence{new Evidence{value, date, info}}{
    clickClock.restart();
    textDate->setTextRect();
    textValue->setTextRect();
    for(int i = 0; i * maxLength < (int)info.length(); ++ i){
        std::string temp = info.substr(i * maxLength, maxLength);
        textInfo.emplace_back(new Text{temp, sf::Vector2f {50.f, 80.f + (float)i * 35.f}, sf::Vector2f {0.f, 50.f}});
        textInfo[textInfo.size() - 1]->setTextRect();
    }
    size = {800.f + (float)margin.x, 60.f + (float)textInfo.size() * 45.f + (float)margin.y};
}

void Container::setPos(sf::Vector2f newPos){
    pos = newPos;
}

sf::Vector2f Container::getPos() const{
    return pos;
}

sf::Vector2f Container::getSize() const{
    return size;
}

Evidence Container::getEvidence() const {
    return *evidence;
}

bool Container::checkInsideBox(sf::Vector2i mousePos) const{
    sf::Vector2i topLeft = sf::Vector2i {(int)pos.x, (int)pos.y};
    sf::Vector2i bottomRight = sf::Vector2i{(int)(pos.x + size.x), (int)(pos.y + size.y)} + margin;
    return
            mousePos.x >= topLeft.x && mousePos.x <= bottomRight.x &&
            topLeft.y <= mousePos.y && mousePos.y <= bottomRight.y;
}

bool Container::checkDoubleClick(){
    bool isDoubleClicked = clickClock.getElapsedTime().asMilliseconds() <= 500;
    clickClock.restart();
    return isDoubleClicked;
}

bool Container::listen(sf::Event event, sf::Vector2i mousePos) {
    isHovered = checkInsideBox(mousePos);
    int isDoubleClicked = false;
    if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        isDoubleClicked  = checkDoubleClick();
    return isHovered && isDoubleClicked;
}

void Container::getContainerTexture(sf::Texture &texture) const {
    int borderThickness = 4;
    sf::Vector2f rectSize{size.x - (float)(2 * borderThickness), size.y - (float)(2 * borderThickness)};
    sf::Vector2i textureSize = {(int) size.x, (int) size.y};

    sf::RenderTexture containerTexture;
    containerTexture.create(textureSize.x, textureSize.y);
    containerTexture.clear();

    sf::RectangleShape rect{rectSize};
    rect.setOutlineColor(sf::Color {66, 69, 19});
    rect.setOutlineThickness((float)borderThickness);
    rect.setPosition(sf::Vector2f {(float)borderThickness, (float)borderThickness});
    if(!isHovered)
        rect.setFillColor(sf::Color {153, 161, 0});
    else
        rect.setFillColor(sf::Color {153, 161, 0, 192});

    containerTexture.draw(rect);
    containerTexture.draw(*textDate);
    containerTexture.draw(*textValue);
    for(const auto &textInfoRow: textInfo)
        containerTexture.draw(*textInfoRow);
    containerTexture.display();
    texture = containerTexture.getTexture();
}

void Container::draw(sf::RenderTarget& target, sf::RenderStates) const{
    sf::Texture containerTexture;
    getContainerTexture(containerTexture);
    sf::Sprite containerSprite;
    containerSprite.setTexture(containerTexture);
    containerSprite.setPosition(pos);
    target.draw(containerSprite);
}

bool operator<(const Container& a, const Container& b){
    return *a.evidence < *b.evidence;
}