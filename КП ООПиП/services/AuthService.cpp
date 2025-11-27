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
		out_user = m_realtorRepository.get([name](const std::shared_ptr<Realtor>& obj) { return name == obj->username(); });
		if (out_user == nullptr) return AuthResult::UserNotFound;
		else if (PasswordHasher::encrypt(password) != out_user->hashedPassword()) return AuthResult::WrongPassword;
	}

	return AuthResult::Success;
}
AuthResult AuthService::registerUser(const std::string& name, const std::string& password)
{
	if (m_realtorRepository.exists([name](const std::shared_ptr<Realtor>& obj) { return name == obj->username(); })) return AuthResult::AlreadyExists;

	unsigned int id = m_usersIdGen.next();

	std::shared_ptr<Realtor> new_user = std::make_shared<Realtor>(id, name, PasswordHasher::encrypt(password), "", "", "", "", 0);

	m_realtorRepository.add(new_user, [](const std::shared_ptr<Realtor>& obj) { return false; });

	return AuthResult::Success;
}