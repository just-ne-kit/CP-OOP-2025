#pragma once

#include "../core/Ad.h"
#include "Repository.h"

class AdRepository : public Repository<Ad>
{
public:
	AdRepository(const std::vector<std::shared_ptr<Ad>>& ads)
		: Repository(ads) {}

	bool addAd(const std::shared_ptr<Ad>& ad) {
		return Repository::add(ad, [&](const auto& a) { return a->id() == ad->id(); });
	}

	const std::shared_ptr<Ad> getById(const unsigned int& id) const {
		return Repository::get([&](const auto& ad) { return ad->id() == id; });
	}

	const bool exists(const unsigned int& id) const {
		return Repository::exists([&](const auto& ad) { return ad->id() == id; });
	}
};