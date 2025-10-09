#pragma once

#include <string>

class Ad
{
private:
	unsigned int m_id;
	unsigned int ownerId;
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
	Ad(const unsigned int id)
		: m_id(id) { }

	const unsigned int id() const { return m_id; }
};