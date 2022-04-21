//
// Created by vladi on 4/15/2022.
//

#ifndef OOP_FORM_HPP
#define OOP_FORM_HPP

#include <vector>
#include <map>
#include <typeinfo>
#include <SFML/Graphics.hpp>
#include "Input.hpp"

class Form: public sf::Drawable{
private:
    std::vector <Input*> inputs;
    sf::Vector2f size;
    sf::Vector2f pos;
    bool isDisplayed;

    static sf::Vector2u margin;

public:
    Form(sf::Vector2f, bool);

    Form(const Form& other);
    Form& operator=(const Form& other);
    friend void swap(Form&, Form &);

    void setPosition(sf::Vector2f);

    void addInput(const std::string&, const std::string&, sf::Vector2f, sf::Vector2f, sf::Color, sf::Color, const std::type_info&);
    std::string listen(sf::Event, sf::Vector2i);
    std::map<std::string, std::string> collectValues();
    std::vector <std::string> collectValuesOrLabels();

    void clearForm();
    void emptyForm();

    void move(sf::Vector2f);

    void setIsDisplayed(bool);
    [[nodiscard]] bool getIsDisplayed() const;

    void getFormTexture(sf::Texture&) const;
    void draw(sf::RenderTarget&, sf::RenderStates) const override;

    ~Form() override;
};

#endif //OOP_FORM_HPP