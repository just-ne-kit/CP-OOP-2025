#pragma once

#include "User.h"
#include "../security/PasswordHasher.h"

class Admin : public User
{
private:

public:
	Admin() {
		strcpy_s(hashed_password_, PasswordHasher::encrypt(auth_cfg::ADMIN_PASSWORD).c_str());
	}
	Role role() const override {
		return Role::AdminRole;
	}
	virtual std::vector<std::string> to_lines() const override;
};