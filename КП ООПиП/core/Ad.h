#pragma once

#include <string>

class Ad
{
private:
	unsigned int m_id;
	unsigned int m_ownerId;

	char m_title[32];
	char m_description[256];

	float m_price;
	
	unsigned int m_floor;
	unsigned int m_rooms;
	float m_area;
	bool m_hasBalcony;
	bool m_isNewBuilding;
	
	char m_address[64];
public:
	Ad()
	{
		m_id = 0;
		m_ownerId = 0;

		strcpy_s(m_title, "no set");
		strcpy_s(m_description, "no set");

		m_price = 0;

		m_floor = 0;
		m_rooms = 0;
		m_area = 0;
		m_hasBalcony = 0;
		m_isNewBuilding = 0;

		strcpy_s(m_address, "no set");
	}
	Ad( const unsigned int id,
		const unsigned int ownerId,
		const std::string& title,
		const std::string& description,
		const float price,
		const unsigned int floor,
		const unsigned int rooms,
		const float area,
		const bool hasBalcony,
		const bool isNewBuilding,
		const std::string& address )
	{
		m_id = id;
		m_ownerId = ownerId;

		strcpy_s(m_title, title.c_str());
		strcpy_s(m_description, description.c_str());

		m_price = price;

		m_floor = floor;
		m_rooms = rooms;
		m_area = area;
		m_hasBalcony = hasBalcony;
		m_isNewBuilding = isNewBuilding;

		strcpy_s(m_address, address.c_str());
	}

	unsigned int id() const noexcept { return m_id; }
	unsigned int ownerId() const noexcept { return m_ownerId; }
	float price() const noexcept { return m_price; }
	const char* title() const noexcept { return m_title; }
	const char* description() const noexcept { return m_description; }

	unsigned int rooms() const noexcept { return m_rooms; }
	unsigned int floor() const noexcept { return m_floor; }
	float area() const noexcept { return m_area; }
	bool hasBalcony() const noexcept { return m_hasBalcony; }
	bool isNewBuilding() const noexcept { return m_isNewBuilding; }
	const char* address() const noexcept { return m_address; }
};