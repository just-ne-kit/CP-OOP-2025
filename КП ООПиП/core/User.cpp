#include "User.h"
#include "../ui/InputReader.h"

User::User(unsigned int id, const std::string& username, const std::string& hashed_password,
    const std::string& name, const std::string& email, const std::string& phone)
{
    id_ = id;
    strcpy_s(username_, username.c_str());
    strcpy_s(hashed_password_, hashed_password.c_str());

    strcpy_s(name_, name.c_str());
    strcpy_s(email_, email.c_str());
    strcpy_s(phone_, phone.c_str());
}
User::User() : User(0, "", "", "", "", "") {}

User::User(unsigned int id, const std::string &username, const std::string &hashed_password)
    : User(id, username, hashed_password, "", "", "") {}

User::User(const User &user)
	: User(user.id_, user.username_, user.hashed_password_, user.name_, user.email_, user.phone_) {}

void User::serialize(std::ofstream& ofs) const
{
    ofs.write(reinterpret_cast<const char*>(&id_), sizeof(id_));
    ofs.write(reinterpret_cast<const char*>(username_), sizeof(username_));
    ofs.write(reinterpret_cast<const char*>(hashed_password_), sizeof(hashed_password_));

    ofs.write(reinterpret_cast<const char*>(name_), sizeof(name_));
    ofs.write(reinterpret_cast<const char*>(email_), sizeof(email_));
    ofs.write(reinterpret_cast<const char*>(phone_), sizeof(phone_));
}
void User::deserialize(std::ifstream& ifs) {
    ifs.read(reinterpret_cast<char*>(&id_), sizeof(id_));
    ifs.read(reinterpret_cast<char*>(username_), sizeof(username_));
    ifs.read(reinterpret_cast<char*>(hashed_password_), sizeof(hashed_password_));

    ifs.read(reinterpret_cast<char*>(name_), sizeof(name_));
    ifs.read(reinterpret_cast<char*>(email_), sizeof(email_));
    ifs.read(reinterpret_cast<char*>(phone_), sizeof(phone_));
}

//bool User::operator==(const User &user)
//{
//	return this->hashed_password_ == user.hashed_password_ &&
//		this->id_ == user.id_ &&
//		this->username_ == user.username_;
//}

unsigned int User::id() const { return id_; }
const char * User::username() const { return username_; }
const char * User::hashed_password() const { return hashed_password_; }

const char * User::name() const { return  name_; }
const char * User::email() const { return email_; }
const char * User::phone() const { return phone_; }

void User::setName(const std::string& name) {
    std::strncpy(this->name_, name.c_str(), common_cfg::NAME_MAX_LEN - 1);
    this->name_[common_cfg::NAME_MAX_LEN - 1] = '\0';
}
void User::setEmail(const std::string& email) {
    std::strncpy(this->email_, email.c_str(), common_cfg::EMAIL_MAX_LEN - 1);
    this->email_[common_cfg::EMAIL_MAX_LEN - 1] = '\0';
}
void User::setPhone(const std::string& phone) {
    std::strncpy(this->phone_, phone.c_str(), common_cfg::PHONE_MAX_LEN - 1);
    this->phone_[common_cfg::PHONE_MAX_LEN - 1] = '\0';
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