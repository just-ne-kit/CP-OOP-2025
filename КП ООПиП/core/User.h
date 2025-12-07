#pragma once

#include <cstring>
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

	char _name[common_cfg::NAME_MAX_LEN];
	char _email[common_cfg::EMAIL_MAX_LEN];
	char _phone[common_cfg::PHONE_MAX_LEN];
public:
	User();
	User(unsigned int id, const std::string &login, const std::string &hashedPassword);
	User(const User& user);
	virtual ~User() = default;
	
	unsigned int id() const;
	const char *username() const;
	const char *hashed_password() const;
	virtual Role role() const = 0;

    const char* name() const;
    const char* email() const;
    const char* phone() const;

	void setName(const std::string& name);
	void setEmail(const std::string& email);
	void setPhone(const std::string& phone);

    static std::string read_name();
    static std::string read_email();
    static std::string read_phone();

    virtual std::vector<std::string> to_lines() const = 0;
    std::string to_str() const;

    friend std::ostream& operator <<(std::ostream& out, const User& seller);
    friend std::istream& operator >>(std::istream& in, User& seller);

	bool operator==(const User &user);
};