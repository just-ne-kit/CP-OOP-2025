#pragma once

#include "Client.h"
#include "Realtor.h"
#include "../repositories/Repository.h"
#include "../security/PasswordHasher.h"
#include "../privileges/Privileges.h"

class Admin : public User, public AdminPriv
{
private:

public:
	Admin();

	virtual Role role() const override;

	virtual void serialize(std::ofstream& ofs) const override;
	virtual void deserialize(std::ifstream& ifs) override;

	virtual std::vector<std::string> to_lines() const override;

	void viewProperties(const Repository<Property>& repo) override;
	void editProperty(Repository<Property>& repo) override;
	void deleteProperty(Repository<Property>& repo) override;
	void report(Repository<Property>& repo) override;

	void viewRealtors(const Repository<Realtor>& default_repo);
	void removeRealtors(Repository<Realtor>& default_repo);
	void viewClients(Repository<Client>& repo);
};

using AdminPtr = std::shared_ptr<Admin>;