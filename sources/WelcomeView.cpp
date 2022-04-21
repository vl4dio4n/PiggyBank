//
// Created by vladi on 4/16/2022.
//

#include "../headers/WelcomeView.hpp"

#include <utility>
#include "../headers/Button.hpp"
#include "../headers/Text.hpp"

WelcomeView::WelcomeView(std::string viewName, bool isDisplayed): View(std::move(viewName), isDisplayed), form({400.f, 320.f}, true) {
    sf::Color btnFillColor{127, 135, 38};
    sf::Color btnOutlineColor{66, 69, 19};
    form.addInput("Welcome!", "", {190.f, 50.f}, {0.f, 100.f}, sf::Color::Transparent, sf::Color::Transparent, typeid(Text));
    form.addInput("Sign In", "SignInView", {50.f, 150.f}, {200.f, 60.f}, btnFillColor, btnOutlineColor, typeid(Button));
    form.addInput("Sign Up", "SignUpView", {350.f, 150.f}, {200.f, 60.f}, btnFillColor, btnOutlineColor, typeid(Button));
}

std::string WelcomeView::listen(sf::Event event, sf::Vector2i mousePos){
    return form.listen(event, mousePos);
}

void WelcomeView::draw(sf::RenderTarget &target, sf::RenderStates) const {
    if(isDisplayed)
        target.draw(form);
}