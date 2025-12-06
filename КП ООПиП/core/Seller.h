#pragma once

#include "config.h"
#include <iostream>
#include "../ui/InputReader.h"
#include <string>
#include <vector>

class Seller {
private:
    char _name[common_cfg::NAME_MAX_LEN];
    char _email[common_cfg::EMAIL_MAX_LEN];
    char _phone[common_cfg::PHONE_MAX_LEN];

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
        std::strncpy(this->_name, name.c_str(), common_cfg::NAME_MAX_LEN - 1);
        this->_name[common_cfg::NAME_MAX_LEN - 1] = '\0';
    }

    void setEmail(const std::string& email) {
        std::strncpy(this->_email, email.c_str(), common_cfg::EMAIL_MAX_LEN - 1);
        this->_email[common_cfg::EMAIL_MAX_LEN - 1] = '\0';
    }

    void setPhone(const std::string& phone) {
        std::strncpy(this->_phone, phone.c_str(), common_cfg::PHONE_MAX_LEN - 1);
        this->_phone[common_cfg::PHONE_MAX_LEN - 1] = '\0';
    }

    static std::string read_name() {
        return InputReader::read<std::string>(
            common_cfg::NAME_MAX_LEN - 1,
            common_cfg::NAME_MSG,
            common_cfg::NAME_ERR_MSG);
    }
    static std::string read_email() {
        return InputReader::read<std::string>(
            common_cfg::EMAIL_MAX_LEN - 1,
            common_cfg::EMAIL_MSG,
            common_cfg::EMAIL_ERR_MSG);
    }
    static std::string read_phone() {
        return InputReader::read<std::string>(
            common_cfg::PHONE_MAX_LEN - 1,
            common_cfg::PHONE_MSG,
            common_cfg::PHONE_ERR_MSG);
    }

    std::vector<std::string> to_lines() const {
        std::vector<std::string> lines;
        lines.reserve(3);

        lines.push_back("Имя продавца: " + std::string(name()));
        lines.push_back("Электронная почта продавца: "  + std::string(email()));
        lines.push_back("Телефонный номер продавца: "  + std::string(phone()));

        return lines;
    }

    std::string to_str() const {
        auto lines = to_lines();
        std::string result;
        result.reserve(512);

        for (const auto& line : lines) {
            result += line;
            if (line.empty() || line.back() != '\n') result += "\n";
        }
        return result;  
    }

    friend std::ostream& operator <<(std::ostream& out, const Seller& seller) {
        return out << seller.to_str();
    }

    friend std::istream& operator >>(std::istream& in, Seller& seller) {
        seller.setName(read_name());
        seller.setEmail(read_email());
        seller.setPhone(read_phone());
        return in;
    }
};