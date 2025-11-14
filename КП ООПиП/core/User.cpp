#include "User.h"

User::User() : User(0, "", "", NoneRole) {}
User::User(unsigned int id, const std::string &login, const std::string &hashedPassword, Role role)
{
	m_id = id;
	strcpy_s(m_login, login.c_str());
	strcpy_s(m_hashedPassword, hashedPassword.c_str());
	m_role = role;
}


User::User(const User &user)
	: User(user.m_id, user.m_login, user.m_hashedPassword, user.m_role) {}

const unsigned int User::id() const
{
	return m_id;
}
const char *User::login() const
{
	return m_login;
}
const char *User::hashedPassword() const
{
	return m_hashedPassword;
}
const Role User::role() const
{
	return m_role;
}

bool User::operator==(const User &user)
{
	return this->m_hashedPassword == user.m_hashedPassword &&
		   this->m_id == user.m_id &&
		   this->m_login == user.m_login &&
		   this->m_role == user.m_role;
}