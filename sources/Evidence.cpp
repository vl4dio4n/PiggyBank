//
// Created by vladi on 4/18/2022.
//

#include "../headers/Evidence.hpp"
#include <ctime>
#include <utility>

Evidence::Evidence(const std::string& _value, std::string _date, std::string _info): value(_value), info{std::move(_info)}{
    val = stringToInt(_value);
    std::vector <int> v = parseDate(std::move(_date));

    time_t rawTime;
    struct tm *tempDate;
    time(&rawTime);
    tempDate = localtime(&rawTime);
    tempDate->tm_mday = v[0];
    tempDate->tm_mon = v[1];
    tempDate->tm_year = v[2] - 1900;
    mktime(tempDate);
    day = tempDate->tm_mday;
    mon = tempDate->tm_mon;
    year = tempDate->tm_year + 1900;
    date = intToString(day) + "/" + intToString(mon) + "/" + intToString(year);
}

std::string Evidence::getValue() const {
    return value;
}

std::string Evidence::getInfo() const {
    return info;
}

std::string Evidence::getDate() const {
    return date;
}

int Evidence::getIntValue() const {
    return val;
}

std::string Evidence::intToString(int num){
    int sign = 1;
    if(num < 0)
        sign = -1;
    std::string res;
    while(num){
        res.push_back(char(num % 10 + 48));
        num /= 10;
    }
    if(sign == -1)
        res.push_back('-');
    std::reverse(res.begin(), res.end());
    return res;
}

int Evidence::stringToInt(const std::string& str){
    int sign = 1, num = 0;
    if(str[0] == '-')
        sign = -1;
    for(const auto& ch: str)
        if(ch != '-')
            num = num * 10 + (int)(ch - '0');
    return num * sign;
}

std::vector<int> Evidence::parseDate(std::string _date) {
    int num = 0;
    std::vector <int> v;

    while(_date.length() > 0){
        if(_date[0] != '/')
            num = num * 10 + (int)(_date[0] - '0');
        else{
            v.emplace_back(num);
            num = 0;
        }
        _date.erase(_date.begin());
    }
    v.emplace_back(num);

    return v;
}

bool operator<(const Evidence& a, const Evidence& b){
    if(a.year == b.year){
        if(a.mon == b.mon)
            return a.day < b.day;
        return a.mon < b.mon;
    }
    return a.year < b.year;
}

bool operator<=(const Evidence& a, const Evidence& b){
    if(a.year == b.year){
        if(a.mon == b.mon)
            return a.day <= b.day;
        return a.mon <= b.mon;
    }
    return a.year <= b.year;
}