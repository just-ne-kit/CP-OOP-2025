#include "AuthService.h"

AuthResult AuthService::login(const std::string& name, const std::string& password, std::shared_ptr<User>& out_user)
{
	out_user = m_clientRepository.getByLogin(name);

	if (out_user == nullptr) return AuthResult::UserNotFound;
	else if (PasswordHasher::encrypt(password) != out_user->hashedPassword()) return AuthResult::WrongPassword;

	return AuthResult::Success;
}
AuthResult AuthService::registerUser(const std::string& name, const std::string& password)
{
	if (m_clientRepository.exists(name)) return AuthResult::AlreadyExists;

	unsigned int id = m_clientsIdGen.next();

	m_clientRepository.addClient(std::make_shared<User>(
		id,
		name,
		PasswordHasher::encrypt(password),
		Role::Client
	));

	m_favoritesRepository.addFavorites(std::make_shared<FavoriteAds>(FavoriteAds(id)));
	m_userAdsRepository.addUserAds(std::make_shared<UserAds>(UserAds(id)));

	return AuthResult::Success;
}