#pragma once

#include "User.h"
#include "Property.h"
#include <fstream>

//[User]

class Realtor : public User
{
private:
	char m_lastName[32];   // Фамилия
	char m_firstName[32];  // Имя
	char m_middleName[32]; // Отчество
	char m_email[32];
	unsigned int m_phoneNumber; // 9 ���� (12) 345-67-89

	std::vector<unsigned int> m_properties;

public:
	Realtor();  
    Realtor(const User &base,
            const std::string &lastName,
            const std::string &firstName,
            const std::string &middleName,
            const std::string &email,
            unsigned int phoneNumber);
    Realtor(const User &user);
    Realtor(const Realtor &other);

	void serialize(std::ofstream &ofs) const;
	void deserialize(std::ifstream &ifs);

	void addProperty(unsigned int id);
	void removeProperty(unsigned int id);

	const char *lastName() const;
	const char *firstName() const;
	const char *middleName() const;
	const char *email() const;
	unsigned int phoneNumber() const;
	const std::vector<unsigned int> &properties() const;

	void setLastName(const std::string &lastName);
	void setFirstName(const std::string &firstName);
	void setMiddleName(const std::string &middleName);
	void setEmail(const std::string &email);
	void setPhoneNumber(unsigned int phoneNumber);
};