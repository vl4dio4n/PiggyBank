//
// Created by vladi on 4/19/2022.
//

#ifndef OOP_MAINVIEW_HPP
#define OOP_MAINVIEW_HPP

#include "View.hpp"
#include "Form.hpp"
#include "Container.hpp"
#include "Text.hpp"
#include "Clock.hpp"

class MainView: public View{
private:
    int selectedContainer;
    std::vector <std::pair< std::shared_ptr <Container>, bool> > containers;
    Form updateForm;
    Form btnForm;
    Form addEvidenceForm;
    Form filterForm;
    Form balanceForm;
    Text userText;
    std::string sessionUser;
    Clock<int> clockI;
    Clock<float> clockF;
public:
    MainView(std::string, bool, std::string);

    float getViewHeight() const;

    static std::map<std::string, std::string> parseLine(std::string&);
    void createContainers();

    void showAllContainers();

    static bool checkInt(std::string);
    static bool checkUInt(const std::string&);

    static std::string intToString(int);
    static std::string floatToString(float);
    int getBalance() const;

    static bool checkValidDate(std::string);
    static std::pair <std::string, std::string> parseInterval(std::string);
    static std::vector <std::pair <std::string, std::string> > parseQueryLine(std::string);
    void filterEvidence(std::map <std::string, std::string>);

    void addEvidence(std::map <std::string, std::string>);
    void updateFile();
    void updateContainerPosition();

    void createUpdateForm(const Container&);
    void updateEvidence(std::vector <std::string>);

    void moveForms(sf::Vector2f);
    void resetFormPosition();

    void updateTime() const;

    std::string listen(sf::Event event, sf::Vector2i) override;
    void draw(sf::RenderTarget&, sf::RenderStates) const override;

    static bool cmp(const std::pair< std::shared_ptr <Container>, bool>& a, const std::pair< std::shared_ptr <Container>, bool>& b);

    ~MainView() override = default;
};

#endif //OOP_MAINVIEW_HPP