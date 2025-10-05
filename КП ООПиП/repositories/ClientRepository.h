#pragma once

#include "../core/User.h"
#include <memory>
#include <vector>

class ClientRepository
{
private:
	std::vector<std::shared_ptr<User>> m_clients;
public:
	ClientRepository() {}

	void addClient(const std::shared_ptr<User>& client) {
		if (!exists(client))
			m_clients.push_back(client);
	}

	const std::vector<std::shared_ptr<User>> getAll() const { return m_clients; }

	const bool exists(const std::string& name) const {
		for (const auto& client : m_clients)
			if (name == client->login())
				return true;
		return false;
	}
	const bool exists(const std::shared_ptr<User>& client)
	{
		for (const auto& c : m_clients)
			if (*c == *client)
				return true;
		return false;
	}
};