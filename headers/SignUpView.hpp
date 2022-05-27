//
// Created by vladi on 4/16/2022.
//

#ifndef OOP_SIGNUPVIEW_HPP
#define OOP_SIGNUPVIEW_HPP

#include "View.hpp"
#include "Form.hpp"

class SignUpView: public View{
private:
    Form form;
public:
    SignUpView(std::string, bool);

    static std::map<std::string, std::string> parseLine(std::string&);
    static void createUser(std::map<std::string, std::string>);

    std::string listen(sf::Event event, sf::Vector2i) override;
    void draw(sf::RenderTarget&, sf::RenderStates) const override;

    ~SignUpView() override = default;
};

#endif //OOP_SIGNUPVIEW_HPP