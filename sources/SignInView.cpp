//
// Created by vladi on 4/17/2022.
//

//
// Created by vladi on 4/16/2022.
//

#include "../headers/SignInView.hpp"
#include "../headers/TextArea.hpp"
#include "../headers/Exceptions.hpp"
#include "../headers/FormFactory.hpp"
#include <utility>
#include <fstream>
#include <iostream>

SignInView::SignInView(std::string viewName, bool isDisplayed): View(std::move(viewName), isDisplayed), form(FormFactory::getSignInForm()){}

std::map <std::string, std::string> SignInView::parseLine(std::string& line){
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
    user["Username"] = userArr[1];
    user["Password"] = userArr[2];
    return user;
}

std::string SignInView::validateUser(std::map<std::string, std::string> autUser) {
    if(autUser["Username"].length() == 0 || autUser["Password"].length() == 0)
        throw invalid_input{"Empty fields are not accepted"};

    bool found = false;
    std::ifstream fin("resources/users.txt");
    for(std::string line; std::getline(fin, line) && !found; ){
        std::map<std::string, std::string> user = parseLine(line);
        if(user["Username"] == autUser["Username"] && user["Password"] == autUser["Password"])
            found = true;
    }
    fin.close();

    if(!found)
        throw missing_account{"Account doesn't exit"};

    return autUser["Username"];
}

std::string SignInView::listen(sf::Event event, sf::Vector2i mousePos){
    std::string message = form.listen(event, mousePos);
    if(message == "SignIn"){
        try{
            std::string user = validateUser(form.collectValues());
            form.clearForm();
            return "MainView/" + user;
        }
        catch(input_error& err){
            form.clearForm();
            std::cout << "\t" << err.what() << "\n";
        }
    } else if(message == "WelcomeView")
        return "WelcomeView";
    return "Waiting";
}

void SignInView::draw(sf::RenderTarget &target, sf::RenderStates) const {
    if(isDisplayed)
        target.draw(form);
}