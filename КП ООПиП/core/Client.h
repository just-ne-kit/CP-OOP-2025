#pragma once

#include "User.h"
#include "Request.h"
#include "Property.h"
#include "../repositories/Repository.h"

class Client : public User
{
public:
	Client();
	Client(unsigned int id, const std::string& username, const std::string& hashed_password);
	Client(unsigned int id,
		const std::string& username,
		const std::string& hashed_password,
		const std::string& name,
		const std::string& email,
		const std::string& phoneNumber);
	Client(const Client& client);

	virtual Role role() const override;

	virtual std::vector<std::string> to_lines() const;
	void viewProperties(const Repository<Property>& repo);
	void viewRequests(const Repository<Property>& repo, const Repository<Request>& request_repo);
	void viewBought(const Repository<Property>& repo, const Repository<Request>& request_repo);
	void discard(Repository<Request>& request_repo);
	void add(Repository<Property>& repo, Repository<Request>& request_repo);
	void edit();

	std::string to_row(const std::vector<size_t>& sizes) const;
};
using ClientPtr = std::shared_ptr<Client>;