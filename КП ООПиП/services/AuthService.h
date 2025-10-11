#pragma once

#include "../repositories/ClientRepository.h"
#include "../repositories/FavoritesRepository.h"
#include "../repositories/UserAdsRepository.h"
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
	std::shared_ptr<ClientRepository> m_clientRepository;
	std::shared_ptr<FavoritesRepository> m_favoritesRepository;
	std::shared_ptr<UserAdsRepository> m_userAdsRepository;
	IdGenerator m_clientsIdGen;
public:
	AuthService(std::shared_ptr<ClientRepository> clientRepository, std::shared_ptr<FavoritesRepository> favoritesRepository, std::shared_ptr<UserAdsRepository> userAdsRepository, const std::string& clientsIdGenPath)
		: m_clientRepository(clientRepository), m_favoritesRepository(favoritesRepository), m_userAdsRepository(userAdsRepository), m_clientsIdGen(clientsIdGenPath) { }

	AuthResult login(const std::string& name, const std::string& password, std::shared_ptr<User>& out_user);
	AuthResult registerUser(const std::string& name, const std::string& password);
};