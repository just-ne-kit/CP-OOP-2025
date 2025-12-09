#pragma once

#include <string>
#include <vector>
#include <memory>
#include <fstream>

#include "config.h"

enum Role
{
	AdminRole,
	RealtorRole,
	ClientRole
};

class User
{
protected:
	unsigned int id_;
	char username_[common_cfg::USERNAME_LEN];
	char hashed_password_[common_cfg::HASHED_PASSWORD_LEN];

	char name_[common_cfg::NAME_MAX_LEN];
	char email_[common_cfg::EMAIL_MAX_LEN];
	char phone_[common_cfg::PHONE_MAX_LEN];
public:
	User();
	User(unsigned int id, const std::string &username, const std::string &hashed_password);
	User(unsigned int id, const std::string &username, const std::string &hashed_password,
		const std::string& name, const std::string& email, const std::string& phone);
	User(const User& user);
	
	virtual ~User() = default;
	virtual Role role() const = 0;
    virtual std::vector<std::string> to_lines() const = 0;
	virtual void serialize(std::ofstream& ofs) const;
	virtual void deserialize(std::ifstream& ifs);
	//bool operator==(const User &user); todo delete func

	unsigned int id() const;
	const char *username() const;
	const char *hashed_password() const;

    const char* name() const;
    const char* email() const;
    const char* phone() const;

	void setName(const std::string& name);
	void setEmail(const std::string& email);
	void setPhone(const std::string& phone);

    static std::string read_name();
    static std::string read_email();
    static std::string read_phone();

    std::string to_str() const;
};