#pragma once

#include "User.h"
#include "Ad.h"
#include <fstream>

//[User]

class Client : public User
{
private:
	char m_name[32];
	unsigned int m_phoneNumber; // 9 цифр (12) 345-67-89 
	char m_email[32];

	std::vector<int> m_ads;
	std::vector<int> m_liked;
public:
	Client();
	//Client(const User& base, const std::string& name, unsigned int phoneNumber, const std::string& email);

	void serialize(const std::string& filename) const;
	void deserialize(const std::string& filename);

	void addAd(unsigned int id);
	void removeAd(unsigned int id);

	void likeAd(unsigned int id);
	void unlikeAd(unsigned int id);




	const char* getName() const;
	void setName(const std::string& name);

	unsigned int getPhoneNumber() const;
	void setPhoneNumber(unsigned int phone);

	const char* getEmail() const;
	void setEmail(const std::string& email);

	const std::vector<int>& getAds() const;

	const std::vector<int>& getLiked() const;
};