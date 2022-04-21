//
// Created by vladi on 4/17/2022.
//

#ifndef OOP_SIGNINVIEW_HPP
#define OOP_SIGNINVIEW_HPP

#include "View.hpp"
#include "Form.hpp"
#include "Button.hpp"

class SignInView: public View{
private:
    Form form;

public:
    SignInView(std::string, bool);

    static std::map<std::string, std::string> parseLine(std::string&);
    static std::string validateUser(std::map <std::string, std::string>);

    std::string listen(sf::Event event, sf::Vector2i) override;
    void draw(sf::RenderTarget&, sf::RenderStates) const override;

    ~SignInView() override = default;
};

#endif //OOP_SIGNINVIEW_HPP