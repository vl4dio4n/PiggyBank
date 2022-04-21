//
// Created by vladi on 4/16/2022.
//

#include "../headers/View.hpp"

#include <utility>

View::View(std::string viewName, bool isDisplayed): viewName(std::move(viewName)), isDisplayed(isDisplayed){}

std::string View::getViewName() {
    return viewName;
}

bool View::getIsDisplayed() const {
    return isDisplayed;
}

void View::setIsDisplayed(bool displayed) {
    isDisplayed = displayed;
}