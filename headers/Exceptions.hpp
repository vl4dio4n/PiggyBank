//
// Created by vladi on 4/17/2022.
//

#ifndef OOP_EXCEPTIONS_HPP
#define OOP_EXCEPTIONS_HPP

#include <exception>
#include <string>
#include <utility>
#include <cstring>

class input_error: public std::exception{
protected:
    std::string message;
public:
    explicit input_error(std::string message): message(std::move(message)){}
    [[nodiscard]] const char * what() const noexcept override{
        return message.c_str();
    }
};

class bad_account: public input_error{
public:
    explicit bad_account(const std::string& message): input_error("bad_account: " + message){}
};

class missing_account: public input_error{
public:
    explicit missing_account(const std::string& message): input_error("missing_account: " + message){}
};

class invalid_input: public input_error{
public:
    explicit invalid_input(const std::string& message): input_error("invalid_input: " + message){}
};

#endif //OOP_EXCEPTIONS_HPP