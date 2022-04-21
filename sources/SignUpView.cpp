//
// Created by vladi on 4/16/2022.
//

#include "../headers/SignUpView.hpp"
#include "../headers/Button.hpp"
#include "../headers/TextArea.hpp"
#include "../headers/Text.hpp"
#include "../headers/Exceptions.hpp"
#include <utility>
#include <fstream>
#include <iostream>

SignUpView::SignUpView(std::string viewName, bool isDisplayed): View(std::move(viewName), isDisplayed), form({400.f, 185.f}, true){
    sf::Color btnFillColor{127, 135, 38};
    sf::Color btnOutlineColor{66, 69, 19};
    sf::Color taFillColor = sf::Color::White;
    sf::Color taOutlineColor = sf::Color::Black;

    form.addInput("Create Account", "", {130.f, 50.f}, {0.f, 100.f}, sf::Color::Transparent, sf::Color::Transparent, typeid(Text));
    form.addInput("Name", "", {50.f, 150.f}, {500.f, 40.f}, taFillColor, taOutlineColor, typeid(TextArea));
    form.addInput("Username", "", {50.f, 240.f}, {500.f, 40.f}, taFillColor, taOutlineColor, typeid(TextArea));
    form.addInput("Password", "", {50.f, 330.f}, {500.f, 40.f}, taFillColor, taOutlineColor, typeid(TextArea));
    form.addInput("Sign Up", "SignUp", {75.f, 420.f}, {200.f, 60.f}, btnFillColor, btnOutlineColor, typeid(Button));
    form.addInput("Back", "WelcomeView", {325.f, 420.f}, {200.f, 60.f}, btnFillColor, btnOutlineColor, typeid(Button));
}

std::map<std::string, std::string> SignUpView::parseLine(std::string& line){
    std::string value;
    std::vector <std::string> userArr;

    while(line.length()){
        if(line[0] == ','){
            userArr.push_back(value);
            value.clear();
        } else {
            value.push_back(line[0]);
        }
        line.erase(line.begin());
    }
    userArr.push_back(value);

    std::map<std::string, std::string> user;
    user["Name"] = userArr[0];
    user["Username"] = userArr[1];
    user["Password"] = userArr[2];
    return user;
}

void SignUpView::createUser(std::map<std::string, std::string> newUser) {
    if(newUser["Name"].length() == 0 || newUser["Username"].length() == 0 || newUser["Password"].length() == 0)
        throw invalid_input{"Empty fields are not accepted"};

    std::ifstream fin("resources/users.txt");
    for(std::string line; std::getline(fin, line); ){
        std::map<std::string, std::string> user = parseLine(line);
        if(user["Username"] == newUser["Username"] || user["Password"] == newUser["Password"])
            throw bad_account{"Cannot create account"};
    }
    fin.close();

    std::string fileName = "resources/users-info/" + newUser["Username"] + ".txt";
    try{
        std::ofstream fout(fileName);
        fout.close();
    }
    catch(...){
        throw bad_account{"Cannot create user info file"};
    }

    std::ofstream fout("resources/users.txt", std::ios::app);
    fout << newUser["Name"] + "," + newUser["Username"] + "," + newUser["Password"] + "\n";
    fout.close();
}

std::string SignUpView::listen(sf::Event event, sf::Vector2i mousePos){
    std::string message = form.listen(event, mousePos);
    if(message == "SignUp"){
        try{
            createUser(form.collectValues());
            form.clearForm();
            std::cout << "Account created successfully\n";
            return "SignInView";
        }
        catch(input_error& err) {
            form.clearForm();
            std::cout << "\t" << err.what() << "\n";
        }
    } else if(message == "WelcomeView")
        return "WelcomeView";
    return "Waiting";
}

void SignUpView::draw(sf::RenderTarget &target, sf::RenderStates) const {
    if(isDisplayed)
        target.draw(form);
}