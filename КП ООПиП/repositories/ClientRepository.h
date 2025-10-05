#pragma once

#include "../core/User.h"
#include <memory>
#include <vector>

class ClientRepository
{
private:
	std::vector<std::shared_ptr<User>> m_clients;

	const std::shared_ptr<User> findByLogin(const std::string& login) const {
		for (const auto& client : m_clients)
			if (login == client->login())
				return client;
		return nullptr;
	}
public:
	ClientRepository(const std::vector<std::shared_ptr<User>>& clients)
		: m_clients(clients){}

	//Вернет false если имя занято
	bool addClient(const std::shared_ptr<User>& client) { return !exists(client->login()) ? (m_clients.push_back(client), true) : false; }

	const std::vector<std::shared_ptr<User>> getAll() const { return m_clients; }

	const std::shared_ptr<User> getByLogin(const std::string& login) const { return findByLogin(login); }

	const bool exists(const std::string& name) const { return findByLogin(name) != nullptr; }
};