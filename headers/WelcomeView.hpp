//
// Created by vladi on 4/16/2022.
//

#ifndef OOP_WELCOMEVIEW_HPP
#define OOP_WELCOMEVIEW_HPP

#include "View.hpp"

class WelcomeView: public View{
private:
    Form form;

public:
    WelcomeView(std::string, bool);

    std::string listen(sf::Event, sf::Vector2i) override;
    void draw(sf::RenderTarget&, sf::RenderStates) const override;

    ~WelcomeView() override = default;
};

#endif //OOP_WELCOMEVIEW_HPP