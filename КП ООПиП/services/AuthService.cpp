#include "AuthService.h"

AuthResult AuthService::login(const std::string& name, const std::string& password)
{
	auto client = m_clientRepository.getByLogin(name);

	if (client == nullptr) return AuthResult::UserNotFound;
	else if (PasswordHasher::encrypt(password) != client->hashedPassword()) return AuthResult::WrongPassword;

	return AuthResult::Success;
}
AuthResult AuthService::registerUser(const std::string& name, const std::string& password)
{
	return m_clientRepository.addClient(std::make_shared<User>(
		m_clientsIdGen.next(),
		name,
		PasswordHasher::encrypt(password),
		Role::Client
	)) ? AuthResult::Success : AuthResult::AlreadyExists;
}