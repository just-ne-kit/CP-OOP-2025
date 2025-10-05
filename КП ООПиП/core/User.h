#pragma once

#include <string>

enum Role { None, Admin, Client };

class User
{
protected:
	unsigned int m_id;
	char m_login[32];
	char m_hashedPassword[32];
	Role m_role;
public:
	User() : User(0, "", "", None){}
	User(unsigned int id, std::string login, std::string hashedPassword, Role role)
	{
		m_id = id;
		strcpy_s(m_login, login.c_str());
		strcpy_s(m_hashedPassword, hashedPassword.c_str());
		m_role = role;
	}
	const unsigned int id() const { return m_id; }
};