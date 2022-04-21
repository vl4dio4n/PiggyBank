//
// Created by vladi on 4/18/2022.
//

#ifndef OOP_EVIDENCE_HPP
#define OOP_EVIDENCE_HPP

#include <string>
#include <vector>

class Evidence{
private:
    std::string value;
    std::string info;
    std::string date;
    int val;
    int day;
    int mon;
    int year;
public:
    Evidence(const std::string&, std::string, std::string); // day/mon/year

    [[nodiscard]] std::string getValue() const;
    [[nodiscard]] std::string getInfo() const;
    [[nodiscard]] std::string getDate() const;
    [[nodiscard]] int getIntValue() const;

    static std::vector<int> parseDate(std::string);
    static std::string intToString(int);
    static int stringToInt(const std::string&);

    friend bool operator<(const Evidence& a, const Evidence& b);
    friend bool operator<=(const Evidence& a, const Evidence& b);
};

#endif //OOP_EVIDENCE_HPP