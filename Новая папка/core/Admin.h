#pragma once

#include "Client.h"
#include "Realtor.h"
#include "../repositories/Repository.h"

class Admin : public User
{
public:
	Admin();

	virtual Role role() const override;

	virtual void serialize(std::ofstream& ofs) const override;
	virtual void deserialize(std::ifstream& ifs) override;

	virtual std::vector<std::string> to_lines() const override;

	void viewProperties(const Repository<Property>& repo);
	void editProperty(Repository<Property>& repo);
	void deleteProperty(Repository<Property>& repo);
	void report(Repository<Property>& repo);

	void viewRealtors(const Repository<Realtor>& default_repo);
	void removeRealtors(Repository<Realtor>& default_repo);
	void viewClients(Repository<Client>& repo);
};

using AdminPtr = std::shared_ptr<Admin>;