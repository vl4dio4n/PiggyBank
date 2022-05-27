//
// Created by vladi on 4/18/2022.
//

#ifndef OOP_FORMFACTORY_HPP
#define OOP_FORMFACTORY_HPP

#include "Form.hpp"
#include "../headers/Button.hpp"
#include "../headers/TextArea.hpp"
#include "../headers/Text.hpp"

class FormFactory{
private:
    static sf::Color btnFillColor;
    static sf::Color btnOutlineColor;
    static sf::Color taFillColor;
    static sf::Color taOutlineColor;
public:
    static void init();
    static Form getSignUpForm();
    static Form getSignInForm();
    static Form getUpdateForm();
    static Form getBtnForm();
    static Form getAddEvidenceForm();
    static Form getFilterForm();
    static Form getBalanceForm();
};

#endif //OOP_FORMFACTORY_HPP
