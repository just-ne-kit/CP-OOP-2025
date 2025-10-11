#pragma once

#include <vector>

class UserAds
{
private:
	unsigned int m_id;
	std::vector<unsigned int> m_ads;
public:
	UserAds() {}
	UserAds(unsigned int id)
		: m_id(id) {
	}

	const unsigned int id() const { return m_id; }
	const std::vector<unsigned int> ads() const { return m_ads; }

	void addUserAds(unsigned int ad_id) { if (!exists(ad_id)) m_ads.push_back(ad_id); }
	bool exists(unsigned int ad_id) {
		for (const auto& f : m_ads) {
			if (f == ad_id) return true;
		}
		return false;
	}
};