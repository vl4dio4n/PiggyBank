//
// Created by vladi on 4/16/2022.
//

#ifndef OOP_VIEW_HPP
#define OOP_VIEW_HPP

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Form.hpp"

class View: public sf::Drawable{
protected:
    std::string viewName;
    bool isDisplayed;

public:
    View(std::string, bool);

    std::string getViewName();
    [[nodiscard]] bool getIsDisplayed() const;
    void setIsDisplayed(bool);

    virtual std::string listen(sf::Event, sf::Vector2i) = 0;
    void draw(sf::RenderTarget&, sf::RenderStates) const override = 0;

    ~View() override = default;
};

#endif //OOP_VIEW_HPP