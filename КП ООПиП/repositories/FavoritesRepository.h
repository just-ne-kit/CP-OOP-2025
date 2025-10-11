#pragma once

#include "../core/Favorites.h"
#include "Repository.h"

class FavoritesRepository : public Repository<Favorites>
{
public:
	FavoritesRepository(const std::vector<std::shared_ptr<Favorites>>& fs)
		: Repository(fs) {
	}

	bool addFavorites(const std::shared_ptr<Favorites>& f) {
		return Repository::add(f, [&](const auto& a) { return a->id() == f->id(); });
	}

	const std::shared_ptr<Favorites> getById(const unsigned int& id) const {
		return Repository::get([&](const auto& f) { return f->id() == id; });
	}

	const bool exists(const unsigned int& id) const {
		return Repository::exists([&](const auto& f) { return f->id() == id; });
	}
};