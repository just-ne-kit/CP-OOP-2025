#include "User.h"

User::User(unsigned int id, const std::string &login, const std::string &hashedPassword)
{
	m_id = id;
	strcpy_s(m_username, login.c_str());
	strcpy_s(m_hashedPassword, hashedPassword.c_str());
}
User::User() : User(0, "", "") {}


User::User(const User &user)
	: User(user.m_id, user.m_username, user.m_hashedPassword) {}

unsigned int User::id() const
{
	return m_id;
}
const char *User::username() const
{
	return m_username;
}
const char *User::hashedPassword() const
{
	return m_hashedPassword;
}

bool User::operator==(const User &user)
{
	return this->m_hashedPassword == user.m_hashedPassword &&
		this->m_id == user.m_id &&
		this->m_username == user.m_username;
}