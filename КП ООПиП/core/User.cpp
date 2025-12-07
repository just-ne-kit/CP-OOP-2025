#include "User.h"
#include "../ui/InputReader.h"

User::User(unsigned int id, const std::string &login, const std::string &hashedPassword)
{
	id_ = id;
	strcpy_s(username_, login.c_str());
	strcpy_s(hashed_password_, hashedPassword.c_str());
}
User::User() : User(0, "", "") {}


User::User(const User &user)
	: User(user.id_, user.username_, user.hashed_password_) {}

unsigned int User::id() const
{
	return id_;
}
const char *User::username() const
{
	return username_;
}
const char *User::hashed_password() const
{
	return hashed_password_;
}

bool User::operator==(const User &user)
{
	return this->hashed_password_ == user.hashed_password_ &&
		this->id_ == user.id_ &&
		this->username_ == user.username_;
}

const char* User::name() const { return  _name; }
const char* User::email() const { return _email; }
const char* User::phone() const { return _phone; }

void User::setName(const std::string& name) {
    std::strncpy(this->_name, name.c_str(), common_cfg::NAME_MAX_LEN - 1);
    this->_name[common_cfg::NAME_MAX_LEN - 1] = '\0';
}

void User::setEmail(const std::string& email) {
    std::strncpy(this->_email, email.c_str(), common_cfg::EMAIL_MAX_LEN - 1);
    this->_email[common_cfg::EMAIL_MAX_LEN - 1] = '\0';
}

void User::setPhone(const std::string& phone) {
    std::strncpy(this->_phone, phone.c_str(), common_cfg::PHONE_MAX_LEN - 1);
    this->_phone[common_cfg::PHONE_MAX_LEN - 1] = '\0';
}

std::string User::read_name() {
    return InputReader::read<std::string>(
        common_cfg::NAME_MAX_LEN - 1,
        common_cfg::NAME_MSG,
        common_cfg::NAME_ERR_MSG);
}
std::string User::read_email() {
    return InputReader::read<std::string>(
        common_cfg::EMAIL_MAX_LEN - 1,
        common_cfg::EMAIL_MSG,
        common_cfg::EMAIL_ERR_MSG);
}
std::string User::read_phone() {
    return InputReader::read<std::string>(
        common_cfg::PHONE_MAX_LEN - 1,
        common_cfg::PHONE_MSG,
        common_cfg::PHONE_ERR_MSG);
}

std::vector<std::string> User::to_lines() const {
    std::vector<std::string> lines;
    lines.reserve(3);

    lines.push_back("Имя продавца: " + std::string(name()));
    lines.push_back("Электронная почта продавца: " + std::string(email()));
    lines.push_back("Телефонный номер продавца: " + std::string(phone()));

    return lines;
}

std::string User::to_str() const {
    auto lines = to_lines();
    std::string result;
    result.reserve(512);

    for (const auto& line : lines) {
        result += line;
        if (line.empty() || line.back() != '\n') result += "\n";
    }
    return result;
}

std::ostream& operator <<(std::ostream& out, const User& user) {
    return out << user.to_str();
}

std::istream& operator >>(std::istream& in, User& user) {
    user.setName(User::read_name());
    user.setEmail(User::read_email());
    user.setPhone(User::read_phone());
    return in;
}