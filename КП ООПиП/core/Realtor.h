#pragma once

#include "User.h"
#include "Property.h"
#include "Request.h"
#include "Client.h"
#include <fstream>
#include <memory>
#include "../privileges/Privileges.h"

class Realtor : public User, public RealtorPriv
{
private:
	Repository<Property> ownProperties(const Repository<Property>& repo) const;
public:
	Realtor();  
	Realtor(unsigned int id, const std::string& username, const std::string& hashed_password);
    Realtor(unsigned int id,
			const std::string& username,
			const std::string& hashed_password,
            const std::string &name,
            const std::string &email,
			const std::string& phoneNumber);
    Realtor(const Realtor &realtor);

	virtual Role role() const override;
	virtual std::vector<std::string> to_lines() const override;

	void viewAllProperties(Repository<Property>& repo);
	void viewProperties(const Repository<Property>& repo) override ;
	void addProperty(IdGenerator& id_gen, Repository<Property>& repo) override ;
	void editProperty(Repository<Property>& repo) override ;
	void deleteProperty(Repository<Property>& repo) override ;
	void report(Repository<Property>& repo) override ;

	void viewRequests(Repository<Request>& request_repo,
		Repository<Property>& property_repo,
		Repository<Client>& client_repo);
};

using RealtorPtr = std::shared_ptr<Realtor>;