#pragma once

#include <cstring>
#include <vector>
#include <memory>
#include <fstream>

#include "config.h"

enum Role
{
	AdminRole,
	RealtorRole
};

class User
{
protected:
	unsigned int m_id;
	char m_username[user_config::USERNAME];
	char m_hashedPassword[user_config::HASHED_PASSWORD];
public:
	User(unsigned int id,
		 const std::string &login,
		 const std::string &hashedPassword);
	User();
	User(const User& user);
	virtual ~User() = default;
	
	unsigned int id() const;
	const char *username() const;
	const char *hashedPassword() const;
	virtual Role role() const = 0;

	bool operator==(const User &user);
};