#pragma once

#include "../core/User.h"
#include "Repository.h"

class ClientRepository : public Repository<User>
{
public:
	ClientRepository(const std::vector<std::shared_ptr<User>>& clients)
		: Repository(clients) {
	}

	//Вернет false если имя занято
	bool addClient(const std::shared_ptr<User>& client) {
		return Repository::add(client, [&](const auto& user) { return user->login() == client->login(); });
	}

	const std::shared_ptr<User> getByLogin(const std::string& login) const {
		return Repository::get([&](const auto& client) { return client->login() == login; });
	}

	const bool exists(const std::string& login) const {
		return Repository::exists([&](const auto& client) { return client->login() == login; });
	}
};