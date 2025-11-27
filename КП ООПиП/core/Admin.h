#pragma once

#include "User.h"
#include "../security/PasswordHasher.h"

class Admin : public User
{
private:

public:
	Admin()
	{
		strcpy_s(m_hashedPassword, PasswordHasher::encrypt("1111").c_str());
	}
	Role role() const override {
		return Role::AdminRole;
	}
};