//
// Created by vladi on 4/18/2022.
//

#include "../headers/FormFactory.hpp"

sf::Color FormFactory::btnFillColor;
sf::Color FormFactory::btnOutlineColor;
sf::Color FormFactory::taFillColor;
sf::Color FormFactory::taOutlineColor;

void FormFactory::init(){
    btnFillColor = {127, 135, 38};
    btnOutlineColor = {66, 69, 19};
    taFillColor = sf::Color::White;
    taOutlineColor = sf::Color::Black;
}

Form FormFactory::getSignUpForm() {
    Form signUpForm({400.f, 185.f}, true);
    signUpForm.addInput("Create Account", "", {130.f, 50.f}, {0.f, 100.f}, sf::Color::Transparent, sf::Color::Transparent, typeid(Text));
    signUpForm.addInput("Name", "", {50.f, 150.f}, {500.f, 40.f}, taFillColor, taOutlineColor, typeid(TextArea));
    signUpForm.addInput("Username", "", {50.f, 240.f}, {500.f, 40.f}, taFillColor, taOutlineColor, typeid(TextArea));
    signUpForm.addInput("Password", "", {50.f, 330.f}, {500.f, 40.f}, taFillColor, taOutlineColor, typeid(TextArea));
    signUpForm.addInput("Sign Up", "SignUp", {75.f, 420.f}, {200.f, 60.f}, btnFillColor, btnOutlineColor, typeid(Button));
    signUpForm.addInput("Back", "WelcomeView", {325.f, 420.f}, {200.f, 60.f}, btnFillColor, btnOutlineColor, typeid(Button));

    return signUpForm;
}

Form FormFactory::getSignInForm() {
    Form signInForm({{400.f, 185.f}, true});
    signInForm.addInput("Sign In", "", {220.f, 50.f}, {0.f, 100.f}, sf::Color::Transparent, sf::Color::Transparent, typeid(Text));
    signInForm.addInput("Username", "", {50.f, 150.f}, {500.f, 40.f}, taFillColor, taOutlineColor, typeid(TextArea));
    signInForm.addInput("Password", "", {50.f, 240.f}, {500.f, 40.f}, taFillColor, taOutlineColor, typeid(TextArea));
    signInForm.addInput("Sign In", "SignIn", {200.f, 330.f}, {200.f, 60.f}, btnFillColor, btnOutlineColor, typeid(Button));
    signInForm.addInput("Back", "WelcomeView", {200.f, 420.f}, {200.f, 60.f}, btnFillColor, btnOutlineColor, typeid(Button));

    return signInForm;
}

Form FormFactory::getAddEvidenceForm() {
    Form addEvidenceForm({400.f, 155.f}, false);
    addEvidenceForm.addInput("Add Evidence", "", {150.f, 50.f}, {0.f, 100.f}, sf::Color::Transparent, sf::Color::Transparent, typeid(Text));
    addEvidenceForm.addInput("Value", "", {50.f, 130.f}, {500.f, 40.f}, taFillColor, taOutlineColor, typeid(TextArea));
    addEvidenceForm.addInput("Day (1-31)", "", {50.f, 200.f}, {500.f, 40.f}, taFillColor, taOutlineColor, typeid(TextArea));
    addEvidenceForm.addInput("Month (0-11)", "", {50.f, 270.f}, {500.f, 40.f}, taFillColor, taOutlineColor, typeid(TextArea));
    addEvidenceForm.addInput("Year (>1900)", "", {50.f, 340.f}, {500.f, 40.f}, taFillColor, taOutlineColor, typeid(TextArea));
    addEvidenceForm.addInput("Info", "", {50.f, 410.f}, {500.f, 40.f}, taFillColor, taOutlineColor, typeid(TextArea));
    addEvidenceForm.addInput("Create", "AddEvidence", {75.f, 480.f}, {200.f, 60.f}, btnFillColor, btnOutlineColor, typeid(Button));
    addEvidenceForm.addInput("Back", "CloseForm", {325.f, 480.f}, {200.f, 60.f}, btnFillColor, btnOutlineColor, typeid(Button));

    return addEvidenceForm;
}

Form FormFactory::getBtnForm(){
    Form btnForm({1050.f, 190.f}, true);
    btnForm.addInput("Log Out", "SignOut", {50.f, 50.f}, {200.f, 60.f}, btnFillColor, btnOutlineColor, typeid(Button));
    btnForm.addInput("Add Evidence", "AddEvidenceForm", {50.f, 140.f}, {200.f, 60.f}, btnFillColor, btnOutlineColor, typeid(Button));
    btnForm.addInput("Filter", "FilterEvidenceForm", {50.f, 230.f}, {200.f, 60.f}, btnFillColor, btnOutlineColor, typeid(Button));
    btnForm.addInput("Show All", "ShowAll", {50.f, 320.f}, {200.f, 60.f}, btnFillColor, btnOutlineColor, typeid(Button));
    btnForm.addInput("Get Balance", "Balance", {50.f, 410.f}, {200.f, 60.f}, btnFillColor, btnOutlineColor, typeid(Button));

    return btnForm;
}

Form FormFactory::getFilterForm() {
    Form filterForm({400.f, 155.f}, false);
    filterForm.addInput("Filter", "", {240.f, 50.f}, {0.f, 100.f}, sf::Color::Transparent, sf::Color::Transparent, typeid(Text));
    filterForm.addInput("Select a single date by typing 'dd/mm/yyyy'", "", {50.f, 130.f}, {0.f, 40.f}, sf::Color::Transparent, sf::Color::Transparent, typeid(Text));
    filterForm.addInput("Select interval dates by typing 'dd/mm/yyyy-dd/mm/yyyy'", "", {50.f, 160.f}, {0.f, 40.f}, sf::Color::Transparent, sf::Color::Transparent, typeid(Text));
    filterForm.addInput("Multiple criteria in a single query are separated by ';'", "", {50.f, 190.f}, {0.f, 40.f}, sf::Color::Transparent, sf::Color::Transparent, typeid(Text));
    filterForm.addInput("Query", "", {50.f, 250.f}, {500.f, 40.f}, taFillColor, taOutlineColor, typeid(TextArea));
    filterForm.addInput("Filter", "Filter", {75.f, 340.f}, {200.f, 60.f}, btnFillColor, btnOutlineColor, typeid(Button));
    filterForm.addInput("Back", "CloseForm", {325.f, 340.f}, {200.f, 60.f}, btnFillColor, btnOutlineColor, typeid(Button));

    return filterForm;
}

Form FormFactory::getUpdateForm() {
    Form updateForm({400.f, 185.f}, false);
    return updateForm;
}

Form FormFactory::getBalanceForm() {
    Form balanceForm({1050.f, 730.f}, false);
    return balanceForm;
}