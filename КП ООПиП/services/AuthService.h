#pragma once

#include "../core/Realtor.h"
#include "../core/Admin.h"
#include "../repositories/Repository.h"
#include "../security/PasswordHasher.h"
#include "../id/IdGenerator.h"

enum class AuthResult {
	Success,
	UserNotFound,
	WrongPassword,
	AlreadyExists,
};

class AuthService
{
private:
	Repository<Realtor>& m_realtorRepository;
	IdGenerator m_usersIdGen;
public:
	AuthService(Repository<Realtor>& realtorRepository, const std::string& usersIdGenPath)
		: m_realtorRepository(realtorRepository), m_usersIdGen(usersIdGenPath) { }

	AuthResult login(const std::string& name, const std::string& password, std::shared_ptr<User>& out_user);
	AuthResult registerUser(const std::string& name, const std::string& password);
};