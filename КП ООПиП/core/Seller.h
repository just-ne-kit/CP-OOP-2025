#pragma once

#include "config.h"

class Seller {
private:
    std::string name;
    std::string email;
    unsigned int phone;
public:
    Seller(const std::string& name,
        const std::string& email,
        unsigned int phone)
        : name(name), phone(phone), email(email) {
    }

    std::string to_str() const {
        return "Продавец: " + name + ", Телефон: " + std::to_string(phone) + ", Email: " + email;
    }
};