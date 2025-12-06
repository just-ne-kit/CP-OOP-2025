#pragma once

#include "User.h"
#include "../security/PasswordHasher.h"

class Admin : public User
{
private:

public:
	Admin() {
		strcpy_s(m_hashedPassword, PasswordHasher::encrypt(auth_cfg::ADMIN_PASSWORD).c_str());
	}
	Role role() const override {
		return Role::AdminRole;
	}
};