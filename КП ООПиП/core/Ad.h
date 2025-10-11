#pragma once

#include <string>

class Ad
{
private:
	unsigned int m_id;
	unsigned int m_ownerId;
	float price;
	char m_title[32];
	char m_description[256];

	unsigned int rooms;
	unsigned int floor;
	float area;
	bool hasBalcony;
	bool isNewBuilding;
	char address[64];
public:
	Ad(){}
	Ad(const unsigned int id, const unsigned int ownerId, const std::string& title)
		: m_id(id), m_ownerId(ownerId)
	{
		strcpy_s(m_title, title.c_str());
	}

	const unsigned int id() const { return m_id; }
	const unsigned int ownerId() const { return m_ownerId; }
	const std::string title() const { return m_title; }
};