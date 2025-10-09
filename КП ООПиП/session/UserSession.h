#pragma once

#include "../core/User.h"
#include "../repositories/AdRepository.h"
#include <memory>

class UserSession
{
private:
	std::shared_ptr<User> m_user;
	std::shared_ptr<AdRepository> m_favoritesRepo;
	std::shared_ptr<AdRepository> m_myAdsRepo;
public:

};