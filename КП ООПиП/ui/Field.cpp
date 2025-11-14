#include "Field.h"

std::string Field::WrapWithFocus(const std::string& s) const {
    return ">" + s + "<";
}

Field::Field(FieldType type, unsigned int maxLength,
    const std::string& left,
    const std::string& right,
    const std::string& cur)
    : type(type), left(left), right(right), prev(cur), cur(cur), maxLength(maxLength)
{
    if (type == FieldType::Phone) {
        this->maxLength = 9;
    }
}

void Field::commit() {
    prev = cur;
}

void Field::rollback() {
    cur = prev;
}

void Field::append(const char ch) {
    if (type == FieldType::ButtonExit || type == FieldType::ButtonToogle) return;
    if (cur.size() >= maxLength) return;

    std::string str = cur + ch;

    switch (type) {
    case FieldType::Int:
        if (Parser::is_int(str)) cur = str;
        break;
    case FieldType::Float:
        if (Parser::is_float(str)) cur = str;
        break;
    case FieldType::Phone:
        if (Parser::is_digit(ch)) cur += ch;
        break;
    case FieldType::Str:
    case FieldType::Text:
    case FieldType::Password:
        cur = str;
        break;
    default:
        break;
    }
}

void Field::backspace() {
    if (type == FieldType::ButtonExit || type == FieldType::ButtonToogle) return;
    if (!cur.empty()) cur.pop_back();
}

std::string Field::to_str(bool focused) const {
    if (type == FieldType::Int) {
        return left + cur + std::string(maxLength - cur.size(), spaceCh) + right;
    }
    if (type == FieldType::Float) {
        return left + cur + std::string(maxLength - cur.size(), spaceCh) + right;
    }
    if (type == FieldType::Phone) {
        std::string s = cur + std::string(maxLength - cur.size(), phoneCh);
        return left + "+375 (" + s.substr(0, 2) + ") " + s.substr(2, 3) + "-" + s.substr(5, 2) + "-" + s.substr(7, 2) + right;
    }
    if (type == FieldType::Password) {
        return left + std::string(cur.size(), passwordCh) + right;
    }
    else if (type == FieldType::ButtonExit || type == FieldType::ButtonToogle) {
        return left + (focused ? WrapWithFocus(cur) : " " + cur + " ") + right;
    }
    else if (type == FieldType::Str || type == FieldType::Text) {
        return left + cur + right;
    }
    return "";
}

std::string Field::get_cur() const {
    if(type == FieldType::Phone) return "+375 (" + cur.substr(0, 2) + ") " + cur.substr(2, 3) + "-" + cur.substr(5, 2) + "-" + cur.substr(7, 2);

    return cur;
}