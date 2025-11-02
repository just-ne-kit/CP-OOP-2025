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
	ClientRepository& m_clientRepository;
	FavoritesRepository& m_favoritesRepository;
	UserAdsRepository& m_userAdsRepository;
	IdGenerator m_clientsIdGen;
public:
	AuthService(ClientRepository& clientRepository, FavoritesRepository& favoritesRepository, UserAdsRepository& userAdsRepository, const std::string& clientsIdGenPath)
		: m_clientRepository(clientRepository), m_favoritesRepository(favoritesRepository), m_userAdsRepository(userAdsRepository), m_clientsIdGen(clientsIdGenPath) { }

	AuthResult login(const std::string& name, const std::string& password, std::shared_ptr<User>& out_user);
	AuthResult registerUser(const std::string& name, const std::string& password);
};