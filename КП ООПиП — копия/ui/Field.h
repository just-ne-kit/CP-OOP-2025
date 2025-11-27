#pragma once

#include <string>
#include "../utils/Parser.h"

enum FieldType {
    Str,
    Int,
    Float,
    Text,
    Password,
    ButtonExit,
    ButtonToogle,
    Phone,
    Incrementer,
    Decrementer
};

class Field {
private:
    const char fillCh = ' ';
    const char passwordCh = '*';
    const char spaceCh = '_';
    const char phoneCh = 'X';

    std::string WrapWithFocus(const std::string& s) const;

public:
    FieldType type;

    std::string left;
    std::string right;

    std::string prev;
    std::string cur;
    unsigned int maxLength;

    bool isActivated = false;

    Field(FieldType type, unsigned int maxLength,
        const std::string& left,
        const std::string& right = "",
        const std::string& cur = "");

    void commit();
    void rollback();
    void append(const char ch);
    void backspace();
    std::string to_str(bool focused) const;
    std::string get_cur() const;
};
