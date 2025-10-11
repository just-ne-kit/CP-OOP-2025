#pragma once

#include "../core/UserAds.h"
#include "Repository.h"

class UserAdsRepository : public Repository<UserAds>
{
public:
	UserAdsRepository(const std::vector<std::shared_ptr<UserAds>>& fs)
		: Repository(fs) {
	}

	bool addUserAds(const std::shared_ptr<UserAds>& f) {
		return Repository::add(f, [&](const auto& a) { return a->id() == f->id(); });
	}

	const std::shared_ptr<UserAds> getById(const unsigned int& id) const {
		return Repository::get([&](const auto& f) { return f->id() == id; });
	}

	const bool exists(const unsigned int& id) const {
		return Repository::exists([&](const auto& f) { return f->id() == id; });
	}
};