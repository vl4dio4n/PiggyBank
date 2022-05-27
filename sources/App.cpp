//
// Created by vladi on 4/12/2022.
//

#include <iostream>
#include "../headers/App.hpp"
#include "../headers/Button.hpp"
#include "../headers/Text.hpp"
#include "../headers/WelcomeView.hpp"
#include "../headers/SignUpView.hpp"
#include "../headers/SignInView.hpp"
#include "../headers/MainView.hpp"
#include "../headers/FormFactory.hpp"

App& App::getApp(sf::RenderWindow &_window) {
    static App app(_window);
    return app;
}

App::App(sf::RenderWindow& window): window(window){
    FormFactory::init();
    views.emplace_back(new WelcomeView{"WelcomeView", true});
    views.emplace_back(new SignUpView{"SignUpView", false});
    views.emplace_back(new SignInView{"SignInView", false});
}

bool App::checkViewCenter(float min, float max, float pos) {
    return pos >= min && pos <= max;
}

void App::changeView(const std::string& message) {
    std::string user;
    std::string viewName = message.substr(0, 8);
    if (viewName == "MainView") {
        user = message.substr(9);
        views.emplace_back(new MainView{"MainView", true, user});
        return;
    }
    if (message == "WelcomeView" && views.size() == 4){
        delete views[3];
        views.pop_back();
    }

//    for(auto& view: views)
//        if(view->getViewName() == message){
//            view->setIsDisplayed(true);
//            return;
//        }

    auto view = std::find_if(views.begin(), views.end(), [&](auto& view){
        return view->getViewName() == message;
    });
    if(view != views.end()) {
        (*view)->setIsDisplayed(true);
        return;
    }
}

void App::run(){
    std::string message;
    sf::View windowView = window.getDefaultView();
    sf::Vector2i delta{0, 0};

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                window.close();
            else if(views.size() == 4 && views[3]->getIsDisplayed() && event.type == sf::Event::MouseWheelMoved){
                auto *mainView = dynamic_cast<MainView*>(views[3]);
                sf::Vector2f offset = -(float)event.mouseWheel.delta * sf::Vector2f {0, 20.f};
                if( checkViewCenter(window.getDefaultView().getCenter().y, mainView->getViewHeight() - (float)(window.getSize().y) / 2 + 50.f, windowView.getCenter().y + offset.y)){
                    windowView.move(offset);
                    mainView->moveForms(offset);
                    delta = delta - event.mouseWheel.delta * sf::Vector2i {0, 20};
                }
            }

            for(const auto& view: views)
                if(view->getIsDisplayed()){
                    message = view->listen(event, sf::Mouse::getPosition(window) + delta);
                    if(message != "Waiting" && message != "ResetViewCenter"){
                        view->setIsDisplayed(false);
                        changeView(message);
                        windowView = window.getDefaultView();
                        delta = sf::Vector2i{0, 0};
                    } else if(message == "ResetViewCenter"){
                        windowView = window.getDefaultView();
                        delta = sf::Vector2i{0, 0};
                    }
                }
        }
        window.clear(sf::Color {25, 117, 29});

        window.setView(windowView);
        for(const auto& view: views)
            window.draw(*view);

        window.display();
    }

}

App::~App(){
    for(auto& view: views)
        delete view;
}