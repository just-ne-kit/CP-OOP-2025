#pragma once

#include "../repositories/ClientRepository.h"
#include "../security/PasswordHasher.h"

class AuthService
{
private:
	ClientRepository& m_clientRepository;
public:
	AuthService(ClientRepository clientRepository)
		: m_clientRepository(clientRepository) {}

	bool login(const std::string& name, const std::string& password);
	bool registerUser(const std::string& name, const std::string& password);
};