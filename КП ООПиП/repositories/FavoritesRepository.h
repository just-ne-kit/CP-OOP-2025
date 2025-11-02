#pragma once

#include "../core/FavoriteAds.h"
#include "Repository.h"

class FavoritesRepository : public Repository<FavoriteAds>
{
public:
	FavoritesRepository(const std::vector<std::shared_ptr<FavoriteAds>>& fs)
		: Repository(fs) {
	}

	bool addFavorites(const std::shared_ptr<FavoriteAds>& f) {
		return Repository::add(f, [&](const auto& a) { return a->id() == f->id(); });
	}

	const std::shared_ptr<FavoriteAds> getById(const unsigned int& id) const {
		return Repository::get([&](const auto& f) { return f->id() == id; });
	}

	const bool exists(const unsigned int& id) const {
		return Repository::exists([&](const auto& f) { return f->id() == id; });
	}
};