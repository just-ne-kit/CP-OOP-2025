#pragma once

#include <vector>

class FavoriteAds
{
private:
	unsigned int m_id;
	std::vector<unsigned int> m_favorites;
public:
	FavoriteAds()
		: m_id(0) {}
	FavoriteAds(unsigned int id)
		: m_id(id) {}

	const unsigned int id() const { return m_id; }
	const std::vector<unsigned int> favorites() const { return m_favorites; }

	void addFavorites(unsigned int ad_id) { if (!exists(ad_id)) m_favorites.push_back(ad_id); }
	bool exists(unsigned int ad_id) {
		for (const auto& f : m_favorites) {
			if (f == ad_id) return true;
		}
		return false;
	}
};