#pragma once

#include "../repositories/ClientRepository.h"
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
	ClientRepository& m_clientRepository;
	IdGenerator m_clientsIdGen;
public:
	AuthService(ClientRepository& clientRepository, const std::string& clientsIdGenPath)
		: m_clientRepository(clientRepository), m_clientsIdGen(clientsIdGenPath) { }

	AuthResult login(const std::string& name, const std::string& password);
	AuthResult registerUser(const std::string& name, const std::string& password);
};