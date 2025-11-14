#pragma once

#include <cstring>
#include <vector>
#include <memory>
#include <fstream>

enum Role
{
	NoneRole,
	AdminRole,
	RealtorRole
};

class User
{
protected:
	unsigned int m_id;
	char m_login[32];
	char m_hashedPassword[32];
	Role m_role;

public:
	User(unsigned int id,
		 const std::string &login,
		 const std::string &hashedPassword,
		 Role role);
	User();
	User(const User& user);
	
	const unsigned int id() const;
	const char *login() const;
	const char *hashedPassword() const;
	const Role role() const;

	bool operator==(const User &user);
};