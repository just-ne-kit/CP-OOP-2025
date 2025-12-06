#include "Client.h"

Client::Client()
{

}
Client::Client(unsigned int id,
	const std::string& login,
	const std::string& hashedPassword)
	: User(id, login, hashedPassword)
{

}

Role Client::role() const {
	return Role::ClientRole;
}

void Client::serialize(std::ofstream& ofs) const {

}
void Client::deserialize(std::ifstream& ifs) {

}