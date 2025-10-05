#pragma once

#include "../core/User.h"
#include <memory>
#include <vector>

class ClientRepository
{
private:
	std::vector<std::shared_ptr<User>> m_clients;
public:
	const std::vector<std::shared_ptr<User>> getAll() const { return m_clients; }
	
	void addClient(const std::shared_ptr<User>& client) { m_clients.push_back(client); }


};