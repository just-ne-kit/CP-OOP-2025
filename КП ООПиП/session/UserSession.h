#pragma once

#include "../core/User.h"
#include "../core/FavoriteAds.h"
#include <memory>

class UserSession
{
private:
	std::shared_ptr<User> m_user;
	std::shared_ptr<FavoriteAds> m_favorites;
public:
	UserSession(std::shared_ptr<User> user, std::shared_ptr <FavoriteAds> favorites)
		:m_user(user), m_favorites(favorites) {
	}

	bool IsLoggedIn() const {
		return m_user != nullptr;
	}
	void Logout() {

	}
	void Initialize(std::shared_ptr<User> user, std::shared_ptr<FavoriteAds> favorites) {
		Logout();
		m_user = user;
		m_favorites = favorites;
	}
	const std::shared_ptr<User> user() const { return m_user; }
};