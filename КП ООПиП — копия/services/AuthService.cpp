#include "AuthService.h"

AuthResult AuthService::login(const std::string& name, const std::string& password, std::shared_ptr<User>& out_user)
{
	if (name == "admin")
	{
		out_user = std::make_shared<Admin>();
		if (PasswordHasher::encrypt(password) != out_user->hashedPassword()) return AuthResult::WrongPassword;
	}
	else
	{
		out_user = m_realtorRepository.get([name](const std::shared_ptr<Realtor>& obj) { return name == obj->login(); });
		if (out_user == nullptr) return AuthResult::UserNotFound;
		else if (PasswordHasher::encrypt(password) != out_user->hashedPassword()) return AuthResult::WrongPassword;
	}

	return AuthResult::Success;
}
AuthResult AuthService::registerUser(const std::string& name, const std::string& password)
{
	if (m_realtorRepository.exists([name](const std::shared_ptr<Realtor>& obj) { return name == obj->login(); })) return AuthResult::AlreadyExists;

	unsigned int id = m_usersIdGen.next();

	m_realtorRepository.add(std::make_shared<Realtor>(User(id, name, PasswordHasher::encrypt(password), Role::RealtorRole)), [](const std::shared_ptr<Realtor>& obj) { return false; });

	return AuthResult::Success;
}