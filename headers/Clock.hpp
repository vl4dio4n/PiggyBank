//
// Created by vladi on 5/27/2022.
//
//
#ifndef OOP_CLOCK_HPP
#define OOP_CLOCK_HPP

#include <SFML/System.hpp>
#include <string>

template <typename T>
class Clock{
private:
    T seconds;
    sf::Clock sfClock;
public:
    Clock(){
        seconds = (T)sfClock.restart().asMilliseconds() / (T)1000;
    };
    void updateClock() const{
        (const_cast<Clock<T>*>(this))->seconds = (T)sfClock.getElapsedTime().asMilliseconds() / (T)1000;
    };
    T getSeconds() const{
        return seconds;
    };
};

#endif //OOP_CLOCK_HPP
