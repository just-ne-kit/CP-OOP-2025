#pragma once

#include "User.h"

class Client : public User {

public:
	Client();
	Client(unsigned int id,
		const std::string& login,
		const std::string& hashedPassword);

	virtual Role role() const override;

	void serialize(std::ofstream& ofs) const;
	void deserialize(std::ifstream& ifs);

	virtual std::vector<std::string> to_lines() const override;
};
using ClientPtr = std::shared_ptr<Client>;