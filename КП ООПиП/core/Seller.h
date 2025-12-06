#pragma once

#include "config.h"
#include <iostream>
#include "../ui/InputReader.h"
#include <string>

class Seller {
private:
    char _name[seller_cfg::NAME_MAX_LEN];
    char _email[seller_cfg::EMAIL_MAX_LEN];
    char _phone[seller_cfg::PHONE_MAX_LEN];

public:
    Seller()
    {
        _name[0] = '\0';
        _email[0] = '\0';
        _phone[0] = '\0';
    }

    Seller(const std::string& name, const std::string& email, const std::string& phone)
    {
        setName(name);
        setEmail(email);
        setPhone(phone);
    }

    const char* name() const { return  _name; }
    const char* email() const { return _email; }
    const char* phone() const { return _phone; }

    void setName(const std::string& name) {
        std::strncpy(this->_name, name.c_str(), seller_cfg::NAME_MAX_LEN - 1);
        this->_name[seller_cfg::NAME_MAX_LEN - 1] = '\0';
    }

    void setEmail(const std::string& email) {
        std::strncpy(this->_email, email.c_str(), seller_cfg::EMAIL_MAX_LEN - 1);
        this->_email[seller_cfg::EMAIL_MAX_LEN - 1] = '\0';
    }

    void setPhone(const std::string& phone) {
        std::strncpy(this->_phone, phone.c_str(), seller_cfg::PHONE_MAX_LEN - 1);
        this->_phone[seller_cfg::PHONE_MAX_LEN - 1] = '\0';
    }

    std::string to_str() const {
        return std::string("Продавец: ") + _name + ", Телефон: " + _phone + ", Email: " + _email;
    }

    friend std::istream& operator >>(std::istream& in, Seller& seller) {
        seller.setName(InputReader::read<std::string>(seller_cfg::NAME_MAX_LEN - 1, seller_cfg::NAME_ERR_MSG));
        seller.setEmail(InputReader::read<std::string>(seller_cfg::EMAIL_MAX_LEN - 1, seller_cfg::EMAIL_ERR_MSG));
        seller.setPhone(InputReader::read<std::string>(seller_cfg::PHONE_MAX_LEN - 1, seller_cfg::PHONE_ERR_MSG));
    }
};