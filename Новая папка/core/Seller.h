#pragma once

#include "config.h"
#include <iostream>
#include "../ui/InputReader.h"
#include <string>
#include <vector>

class Seller {
private:
    char name_[common_cfg::NAME_MAX_LEN];
    char email_[common_cfg::EMAIL_MAX_LEN];
    char phone_[common_cfg::PHONE_MAX_LEN];

public:
    Seller()
    {
        name_[0] = '\0';
        email_[0] = '\0';
        phone_[0] = '\0';
    }

    Seller(const std::string& name, const std::string& email, const std::string& phone)
    {
        set_name(name);
        set_email(email);
        set_phone(phone);
    }

    const char* name() const { return  name_; }
    const char* email() const { return email_; }
    const char* phone() const { return phone_; }

    void set_name(const std::string& name) {
        std::strncpy(this->name_, name.c_str(), common_cfg::NAME_MAX_LEN - 1);
        this->name_[common_cfg::NAME_MAX_LEN - 1] = '\0';
    }

    void set_email(const std::string& email) {
        std::strncpy(this->email_, email.c_str(), common_cfg::EMAIL_MAX_LEN - 1);
        this->email_[common_cfg::EMAIL_MAX_LEN - 1] = '\0';
    }

    void set_phone(const std::string& phone) {
        std::strncpy(this->phone_, phone.c_str(), common_cfg::PHONE_MAX_LEN - 1);
        this->phone_[common_cfg::PHONE_MAX_LEN - 1] = '\0';
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
        seller.set_name(read_name());
        seller.set_email(read_email());
        seller.set_phone(read_phone());
        return in;
    }
};