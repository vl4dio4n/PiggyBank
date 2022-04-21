//
// Created by vladi on 4/19/2022.
//

#include "../headers/MainView.hpp"
#include "../headers/Button.hpp"
#include "../headers/TextArea.hpp"
#include "../headers/Exceptions.hpp"
#include <fstream>
#include <iostream>
#include <utility>
#include <numeric>

MainView::MainView(std::string viewName, bool isDisplayed, std::string sessionUser): View(std::move(viewName), isDisplayed), selectedContainer(-1),
                                                                                     updateForm({400.f, 185.f}, false), btnForm({1050.f, 190.f}, true), addEvidenceForm({400.f, 155.f}, false), filterForm({400.f, 155.f}, false), balanceForm({1050.f, 730.f}, false),
                                                                                     userText("Hi, " + sessionUser + "!", {550.f, 50.f}, {0.f, 100.f}), sessionUser(std::move(sessionUser)){
    userText.setTextRect();
    createContainers();

    sf::Color btnFillColor{127, 135, 38};
    sf::Color btnOutlineColor{66, 69, 19};
    sf::Color taFillColor = sf::Color::White;
    sf::Color taOutlineColor = sf::Color::Black;

    btnForm.addInput("Log Out", "SignOut", {50.f, 50.f}, {200.f, 60.f}, btnFillColor, btnOutlineColor, typeid(Button));
    btnForm.addInput("Add Evidence", "AddEvidenceForm", {50.f, 140.f}, {200.f, 60.f}, btnFillColor, btnOutlineColor, typeid(Button));
    btnForm.addInput("Filter", "FilterEvidenceForm", {50.f, 230.f}, {200.f, 60.f}, btnFillColor, btnOutlineColor, typeid(Button));
    btnForm.addInput("Show All", "ShowAll", {50.f, 320.f}, {200.f, 60.f}, btnFillColor, btnOutlineColor, typeid(Button));
    btnForm.addInput("Get Balance", "Balance", {50.f, 410.f}, {200.f, 60.f}, btnFillColor, btnOutlineColor, typeid(Button));

    addEvidenceForm.addInput("Add Evidence", "", {150.f, 50.f}, {0.f, 100.f}, sf::Color::Transparent, sf::Color::Transparent, typeid(Text));
    addEvidenceForm.addInput("Value", "", {50.f, 130.f}, {500.f, 40.f}, taFillColor, taOutlineColor, typeid(TextArea));
    addEvidenceForm.addInput("Day (1-31)", "", {50.f, 200.f}, {500.f, 40.f}, taFillColor, taOutlineColor, typeid(TextArea));
    addEvidenceForm.addInput("Month (0-11)", "", {50.f, 270.f}, {500.f, 40.f}, taFillColor, taOutlineColor, typeid(TextArea));
    addEvidenceForm.addInput("Year (>1900)", "", {50.f, 340.f}, {500.f, 40.f}, taFillColor, taOutlineColor, typeid(TextArea));
    addEvidenceForm.addInput("Info", "", {50.f, 410.f}, {500.f, 40.f}, taFillColor, taOutlineColor, typeid(TextArea));
    addEvidenceForm.addInput("Create", "AddEvidence", {75.f, 480.f}, {200.f, 60.f}, btnFillColor, btnOutlineColor, typeid(Button));
    addEvidenceForm.addInput("Back", "CloseForm", {325.f, 480.f}, {200.f, 60.f}, btnFillColor, btnOutlineColor, typeid(Button));

    filterForm.addInput("Filter", "", {240.f, 50.f}, {0.f, 100.f}, sf::Color::Transparent, sf::Color::Transparent, typeid(Text));
    filterForm.addInput("Select a single date by typing 'dd/mm/yyyy'", "", {50.f, 130.f}, {0.f, 40.f}, sf::Color::Transparent, sf::Color::Transparent, typeid(Text));
    filterForm.addInput("Select interval dates by typing 'dd/mm/yyyy-dd/mm/yyyy'", "", {50.f, 160.f}, {0.f, 40.f}, sf::Color::Transparent, sf::Color::Transparent, typeid(Text));
    filterForm.addInput("Multiple criteria in a single query are separated by ';'", "", {50.f, 190.f}, {0.f, 40.f}, sf::Color::Transparent, sf::Color::Transparent, typeid(Text));
    filterForm.addInput("Query", "", {50.f, 250.f}, {500.f, 40.f}, taFillColor, taOutlineColor, typeid(TextArea));
    filterForm.addInput("Filter", "Filter", {75.f, 340.f}, {200.f, 60.f}, btnFillColor, btnOutlineColor, typeid(Button));
    filterForm.addInput("Back", "CloseForm", {325.f, 340.f}, {200.f, 60.f}, btnFillColor, btnOutlineColor, typeid(Button));

}

float MainView::getViewHeight() const{
    for(int i = (int)containers.size() - 1; i >= 0; i --)
        if(containers[i].second)
            return containers[i].first->getPos().y + containers[i].first->getSize().y + 50.f;
    return 0.f;
}

bool MainView::checkUInt(const std::string& s){
    return std::all_of(s.begin(), s.end(), [](char ch){ return isdigit(ch); });
}

bool MainView::checkInt(std::string s){
    if(s[0] == '-')
        return checkUInt(s.substr(1));
    return checkUInt(s);
}

std::map <std::string, std::string> MainView::parseLine(std::string& line){
    std::string value;
    std::vector <std::string> containerArr;

    while(line.length()){
        if(line[0] == ','){
            containerArr.push_back(value);
            value.clear();
        } else {
            value.push_back(line[0]);
        }
        line.erase(line.begin());
    }
    containerArr.push_back(value);

    std::map<std::string, std::string> container;
    container["value"] = containerArr[0];
    container["date"] = containerArr[1];
    container["info"] = containerArr[2];
    return container;
}

void MainView::createContainers(){
    std::string fileName = "resources/users-info/" + sessionUser + ".txt";
    std::ifstream fin(fileName);

    float spaceBetween = 30;
    sf::Vector2f containerPos{150.f, 150.f};
    for(std::string line; std::getline(fin, line); ){
        std::map <std::string, std::string> containerInfo = parseLine(line);
        containers.emplace_back(std::make_pair(new Container{containerInfo["value"], containerInfo["date"], containerInfo["info"], containerPos}, true));
        sf::Vector2f lastPos = containers[containers.size() - 1].first->getPos();
        sf::Vector2f lastSize = containers[containers.size() - 1].first->getSize();
        containerPos.y = lastPos.y + lastSize.y + spaceBetween;
    }

    fin.close();

    std::sort(containers.begin(), containers.end(), cmp);
    updateContainerPosition();
}

void MainView::showAllContainers(){
    for(auto& container: containers)
        container.second = true;
}

void MainView::updateFile(){
    std::string fileName = "resources/users-info/" + sessionUser + ".txt";
    std::ofstream fout(fileName);

    for(const auto& container: containers){
        Evidence evidence{container.first->getEvidence()};
        fout << evidence.getValue() + "," + evidence.getDate() + "," + evidence.getInfo() + "\n";
    }

    fout.close();
}

void MainView::updateContainerPosition(){
    float spaceBetween = 30;
    sf::Vector2f containerPos{150.f, 150.f};
    for(auto& container: containers){
        container.first->setPos(containerPos);
        containerPos.y += container.first->getSize().y + spaceBetween;
    }
}

void MainView::addEvidence(std::map<std::string, std::string> newEvidence) {
    if(newEvidence["Value"].length() == 0 || newEvidence["Day (1-31)"].length() == 0 || newEvidence["Month (0-11)"].length() == 0 ||
       newEvidence["Year (>1900)"].length() == 0 || newEvidence["Info"].length() == 0)
        throw invalid_input{"Empty fields are not accepted"};
    if(!checkInt(newEvidence["Value"]) || !checkUInt(newEvidence["Day (1-31)"]) || !checkUInt(newEvidence["Month (0-11)"]) || !checkUInt(newEvidence["Year (>1900)"]))
        throw invalid_input("Some fields don't respect the specified format");

    std::string date = newEvidence["Day (1-31)"] + "/" + newEvidence["Month (0-11)"] + "/" + newEvidence["Year (>1900)"];
    sf::Vector2f containerPos{150.f, 150.f};
    if(!containers.empty()) {
        containerPos = containers[containers.size() - 1].first->getPos();
        containerPos.y += containers[containers.size() - 1].first->getSize().y + 30.f;
    }
    containers.emplace_back(std::make_pair(new Container{newEvidence["Value"], date, newEvidence["Info"], containerPos}, true));

    showAllContainers();
    std::sort(containers.begin(), containers.end(), cmp);
    updateContainerPosition();
}

bool MainView::checkValidDate(std::string date) {
    std::string value;
    std::vector <std::string> values;
    while(date.length()){
        if(date[0] == '/'){
            if(value.length() == 0)
                return false;
            values.push_back(value);
            value.clear();
        } else {
            if(!isdigit(date[0]))
                return false;
            value.push_back(date[0]);
        }
        date.erase(date.begin());
    }
    if(value.length() > 0)
        values.push_back(value);
    return values.size() == 3;
}

std::pair<std::string, std::string> MainView::parseInterval(std::string rawDate) {
    for(int i = 0; i < (int)rawDate.length(); ++ i)
        if(rawDate[i] == '-'){
            std::string date1 = rawDate.substr(0, i);
            std::string date2 = rawDate.substr(i + 1);
            if(!checkValidDate(date1) || !checkValidDate(date2))
                throw invalid_input{"Some dates don't respect the specified format"};
            return std::make_pair(date1, date2);
        }
    if(!checkValidDate(rawDate))
        throw invalid_input{"Some dates don't respect the specified format"};
    return std::make_pair(rawDate, rawDate);
}

std::vector <std::pair<std::string, std::string>> MainView::parseQueryLine(std::string line){
    std::string value;
    std::vector <std::string> rawDates;

    while(line.length()){
        if(line[0] == ';'){
            rawDates.push_back(value);
            value.clear();
        } else {
            value.push_back(line[0]);
        }
        line.erase(line.begin());
    }
    if(value.length() > 0)
        rawDates.push_back(value);

    std::vector <std::pair <std::string, std::string> > intervals;
    for(const auto& rawDate: rawDates){
        try{
            intervals.push_back(parseInterval(rawDate));
        }
        catch (input_error&){
            throw;
        }
    }
    return intervals;
}

void MainView::filterEvidence(std::map <std::string, std::string> query){
    try {
        std::vector<std::pair<std::string, std::string> > intervals = parseQueryLine(query["Query"]);
//        for(const auto& interval: intervals)
//            std::cout << interval.first << " " << interval.second << "\n";
//        std::cout << "\n";
        for(auto& container: containers)
            if(container.second) {
                container.second = false;
                Evidence evidence = (container.first)->getEvidence();
                for (const auto &interval: intervals) {
                    Evidence left = Evidence{"0", interval.first, "nothing"};
                    Evidence right = Evidence{"0", interval.second, "nothing"};
                    if (right < left)
                        std::swap(left, right);
                    container.second = container.second || (left <= evidence && evidence <= right);
                }
            }
        std::sort(containers.begin(), containers.end(), cmp);
        updateContainerPosition();
    }
    catch(input_error &){
        throw;
    }
}

std::string MainView::intToString(int num) {
    bool sign = false;
    if(num < 0){
        sign = true;
        num = -num;
    }
    std::string numStr;
    if(num == 0)
        numStr.push_back('0');
    while(num){
        numStr.push_back(char(num % 10 + 48));
        num /= 10;
    }
    if(sign)
        numStr.push_back('-');
    std::reverse(numStr.begin(), numStr.end());
    return numStr;
}

int sum(int x, const std::pair <std::shared_ptr<Container>, bool>& container){
    return x + (container.first)->getEvidence().getIntValue();
}

int MainView::getBalance() const{
//    int balance = 0;
//    for(const auto& container: containers)
//        if(container.second)
//            balance += (container.first)->getEvidence().getIntValue();
    auto balance = std::accumulate(containers.begin(), containers.end(), 0, sum);
    return balance;
}

std::string MainView::listen(sf::Event event, sf::Vector2i mousePos){
    std::string message;
    if(updateForm.getIsDisplayed()) {
        message = updateForm.listen(event, mousePos);
        if(message == "CloseForm"){
            updateForm.clearForm();
            updateForm.setIsDisplayed(false);
        } else if(message == "UpdateEvidence"){
            try{
                updateEvidence(updateForm.collectValuesOrLabels());
                updateForm.clearForm();
                updateForm.setIsDisplayed(false);
                balanceForm.setIsDisplayed(false);
                std::cout << "Evidence was edited successfully\n";
            }
            catch(input_error& err){
                updateForm.clearForm();
                std::cout << "\t" << err.what() << "\n";
            }
        } else if(message == "DeleteEvidence"){
            updateForm.clearForm();
            updateForm.setIsDisplayed(false);
            balanceForm.setIsDisplayed(false);
            containers.erase(containers.begin() + selectedContainer);
            showAllContainers();
            std::sort(containers.begin(), containers.end(), cmp);
            updateContainerPosition();
            std::cout << "Evidence was deleted successfully\n";
        }
    }
    else if(addEvidenceForm.getIsDisplayed()){
        message = addEvidenceForm.listen(event, mousePos);
        if(message == "CloseForm"){
            addEvidenceForm.clearForm();
            addEvidenceForm.setIsDisplayed(false);
        } else if(message == "AddEvidence"){
            try{
                addEvidence(addEvidenceForm.collectValues());
                addEvidenceForm.clearForm();
                addEvidenceForm.setIsDisplayed(false);
                balanceForm.setIsDisplayed(false);
                std::cout << "Evidence added successfully\n";
            }
            catch(input_error& err){
                addEvidenceForm.clearForm();
                std::cout << "\t" << err.what() << "\n";
            }
        }
    } else if(filterForm.getIsDisplayed()){
        message = filterForm.listen(event, mousePos);
        if(message == "CloseForm"){
            filterForm.clearForm();
            filterForm.setIsDisplayed(false);
        } else if(message == "Filter"){
            try{
                filterEvidence(filterForm.collectValues());
                filterForm.clearForm();
                filterForm.setIsDisplayed(false);
                std::cout << "Filter process ended successfully\n";
                resetFormPosition();
                balanceForm.setIsDisplayed(false);
                return "ResetViewCenter";
            }
            catch(input_error& err){
                filterForm.clearForm();
                std::cout << "\t" << err.what() << "\n";
            }
        }
    } else{
        message = btnForm.listen(event, mousePos);
        if(message == "AddEvidenceForm")
            addEvidenceForm.setIsDisplayed(true);
        else if(message == "FilterEvidenceForm")
            filterForm.setIsDisplayed(true);
        else if(message == "ShowAll"){
            showAllContainers();
            balanceForm.setIsDisplayed(false);
            std::sort(containers.begin(), containers.end(), cmp);
            updateContainerPosition();
        } else if(message == "Balance"){
            balanceForm.setIsDisplayed(true);
            balanceForm.emptyForm();
            balanceForm.addInput("Balance: " + intToString(getBalance()), "", {50.f, 30.f}, {0.f, 60.f}, sf::Color::Transparent, sf::Color::Transparent, typeid(Text));
        }
        else if(message == "SignOut"){
            updateFile();
            return "WelcomeView";
        } else {
            int index = 0;
            for (const auto &container: containers) {
                if (container.second && container.first->listen(event, mousePos)) {
                    createUpdateForm(*(container.first));
                    selectedContainer = index;
                }
                ++ index;
            }
        }
    }
    return "Waiting";
}

void MainView::createUpdateForm(const Container& container) {
    sf::Color btnFillColor{127, 135, 38};
    sf::Color btnOutlineColor{66, 69, 19};
    sf::Color taFillColor = sf::Color::White;
    sf::Color taOutlineColor = sf::Color::Black;

    updateForm.setIsDisplayed(true);
    updateForm.emptyForm();
    updateForm.addInput("Edit", "", {260.f, 50.f}, {0.f, 100.f}, sf::Color::Transparent, sf::Color::Transparent, typeid(Text));
    updateForm.addInput("Edit value:", "", {50.f, 130.f}, {0.f, 40.f}, sf::Color::Transparent, sf::Color::Transparent, typeid(Text));
    updateForm.addInput(container.getEvidence().getValue(), "", {50.f, 170.f}, {500.f, 40.f}, taFillColor, taOutlineColor, typeid(TextArea));
    updateForm.addInput("Edit date in format 'dd/mm/yyyy': ", "", {50.f, 230.f}, {0.f, 40.f}, sf::Color::Transparent, sf::Color::Transparent, typeid(Text));
    updateForm.addInput(container.getEvidence().getDate(), "", {50.f, 270.f}, {500.f, 40.f}, taFillColor, taOutlineColor, typeid(TextArea));
    updateForm.addInput("Edit info:", "", {50.f, 330.f}, {0.f, 40.f}, sf::Color::Transparent, sf::Color::Transparent, typeid(Text));
    updateForm.addInput(container.getEvidence().getInfo(), "", {50.f, 370.f}, {500.f, 40.f}, taFillColor, taOutlineColor, typeid(TextArea));
    updateForm.addInput("Update", "UpdateEvidence", {75.f, 430.f}, {200.f, 60.f}, btnFillColor, btnOutlineColor, typeid(Button));
    updateForm.addInput("Back", "CloseForm", {325.f, 430.f}, {200.f, 60.f}, btnFillColor, btnOutlineColor, typeid(Button));
    updateForm.addInput("Delete", "DeleteEvidence", {200.f, 510.f}, {200.f, 60.f}, btnFillColor, btnOutlineColor, typeid(Button));
}

void MainView::updateEvidence(std::vector<std::string> values) {
    if(!checkInt(values[0]) || !checkValidDate(values[1]))
        throw invalid_input("Some fields don't respect the specified format");

    sf::Vector2f containerPos{150.f, 150.f};
    if(!containers.empty()) {
        containerPos = containers[containers.size() - 1].first->getPos();
        containerPos.y += containers[containers.size() - 1].first->getSize().y + 30.f;
    }
    containers.emplace_back(std::make_pair(new Container{values[0], values[1], values[2], containerPos}, true));
    containers.erase(containers.begin() + selectedContainer);

    showAllContainers();
    std::sort(containers.begin(), containers.end(), cmp);
    updateContainerPosition();
}

void MainView::moveForms(sf::Vector2f offset){
    addEvidenceForm.move(offset);
    btnForm.move(offset);
    updateForm.move(offset);
    filterForm.move(offset);
    balanceForm.move(offset);
}

void MainView::resetFormPosition(){
    addEvidenceForm.setPosition(sf::Vector2f{400.f, 155.f});
    btnForm.setPosition(sf::Vector2f{1050.f, 190.f});
    updateForm.setPosition(sf::Vector2f{400.f, 185.f});
    filterForm.setPosition(sf::Vector2f{400.f, 155.f});
    balanceForm.setPosition(sf::Vector2f{1050.f, 730.f});
}

void MainView::draw(sf::RenderTarget& target, sf::RenderStates) const{
    if(isDisplayed) {
        target.draw(userText);
        target.draw(btnForm);
        for (auto &container: containers)
            if(container.second)
                target.draw(*(container.first));
        target.draw(updateForm);
        target.draw(addEvidenceForm);
        target.draw(filterForm);
        target.draw(balanceForm);
    }
}

bool MainView::cmp(const std::pair <std::shared_ptr<Container>, bool>& a, const std::pair <std::shared_ptr<Container>, bool>& b){
    if(a.second == b.second)
        return *(a.first) < *(b.first);
    return a.second > b.second;
}