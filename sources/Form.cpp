//
// Created by vladi on 4/15/2022.
//

#include <iostream>
#include "../headers/Form.hpp"
#include "../headers/Button.hpp"
#include "../headers/TextArea.hpp"
#include "../headers/Text.hpp"

sf::Vector2u Form::margin = {50, 50};

Form::Form(sf::Vector2f pos, bool isDisplayed): pos{pos}, isDisplayed{isDisplayed}{}

Form::Form(const Form& other){
    isDisplayed = other.isDisplayed;
    pos = other.pos;
    size = other.size;
    for(const auto& input: other.inputs)
        inputs.emplace_back(input->clone());
}

void swap(Form& a, Form& b){
    using std::swap;
    swap(a.inputs, b.inputs);
}

Form& Form::operator=(const Form& other){
    auto copy{other};
    swap(copy, *this);
    return *this;
}

void Form::setPosition(sf::Vector2f _pos) {
    pos = _pos;
}

void Form::setIsDisplayed(bool displayed) {
    isDisplayed = displayed;
}

bool Form::getIsDisplayed() const {
    return isDisplayed;
}

void Form::move(sf::Vector2f offset){
    pos += offset;
}

void Form::addInput(const std::string& _label, const std::string& action, sf::Vector2f _pos, sf::Vector2f _size, sf::Color fillColor, sf::Color outlineColor, const std::type_info& t) {
    if(t == typeid(Button))
        inputs.emplace_back(new Button(_label, action, _pos, _size, fillColor, outlineColor));
    else if(t == typeid(TextArea))
        inputs.emplace_back(new TextArea(_label, _pos, _size, fillColor, outlineColor));
    else if(t == typeid(Text)) {
        Text *text = new Text{_label, _pos, _size};
        text->setTextRect();
        inputs.emplace_back(text);
        _size = text->getSize();
    }
    if (inputs.size() == 1)
        size = _pos + _size;
    else {
        size.x = std::max(_pos.x + _size.x, size.x);
        size.y = std::max(_pos.y + _size.y, size.y);
    }
}

std::map <std::string, std::string> Form::collectValues(){
    std::map<std::string, std::string> values;
    for(const auto& input: inputs)
        if(typeid(*input) == typeid(TextArea)) {
            auto *textArea = dynamic_cast<TextArea*>(input);
            values[input->getLabel()] = textArea->getValue();
        }
    return values;
}

std::vector <std::string> Form::collectValuesOrLabels(){
    std::vector <std::string> values;
    for(const auto& input: inputs)
        if(typeid(*input) == typeid(TextArea)) {
            auto *textArea = dynamic_cast<TextArea*>(input);
            if(textArea->getValue().length() == 0)
                values.push_back(input->getLabel());
            else
                values.push_back(textArea->getValue());
        }
    return values;
}

void Form::clearForm() {
    for(const auto& input: inputs)
        if(typeid(*input) == typeid(TextArea)){
            auto *textArea = dynamic_cast<TextArea*>(input);
            textArea->setValue();
        }
}

void Form::emptyForm() {
    inputs.clear();
}

std::string Form::listen(sf::Event event, sf::Vector2i mousePos){
    auto input = std::find_if(inputs.begin(), inputs.end(), [&](auto& input){
        return (input->listen(event, mousePos - sf::Vector2i{(int)pos.x, (int)pos.y}) && typeid(*input) == typeid(Button));
    });
    if(input != inputs.end()) {
        std::cout << (*input)->getLabel() << " button was pressed\n";
        auto *btn = dynamic_cast<Button *>(*input);
        return btn->getAction();
    }
//    for(const auto& input: inputs)
//        if (input->listen(event, mousePos - sf::Vector2i{(int)pos.x, (int)pos.y}) && typeid(*input) == typeid(Button)) {
//            std::cout << input << " " << input->getLabel() << " button was pressed\n";
//            auto *btn = dynamic_cast<Button*>(input);
//            return btn->getAction();
//        }
    return "Waiting";
}

void Form::getFormTexture(sf::Texture& texture) const{
    sf::RenderTexture formTexture;
    formTexture.create((unsigned int)size.x + margin.x, (unsigned int)size.y + margin.y);
    formTexture.clear(sf::Color {153, 161, 0});
    for(const auto &input: inputs)
        formTexture.draw(*input);
    formTexture.display();
    texture = formTexture.getTexture();
}

void Form::draw(sf::RenderTarget& target, sf::RenderStates) const{
    if(isDisplayed) {
        sf::Texture formTexture;
        getFormTexture(formTexture);
        sf::Sprite formSprite;
        formSprite.setTexture(formTexture);
        formSprite.setPosition(pos);
        target.draw(formSprite);
    }
}

Form::~Form(){
    if(isDisplayed)
        for(auto& input: inputs)
            delete input;
}