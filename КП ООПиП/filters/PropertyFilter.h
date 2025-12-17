#pragma once

#include "../core/Property.h"
#include "../repositories/Repository.h"
#include "../ui/ConsoleUI.h"

template<typename T>
bool between(const T& a, const std::pair<T, T>& pair) {
	return pair.first <= a && a <= pair.second;
}

class PropertyFilter {
private:
	std::pair<float, float> priceRange{ prop_cfg::PRICE_MIN, prop_cfg::PRICE_MAX };
	std::pair<float, float> areaRange{ prop_cfg::AREA_TOTAL_MIN, prop_cfg::AREA_TOTAL_MAX };
	std::pair<unsigned int, unsigned int> roomsRange{ prop_cfg::ROOMS_MIN, prop_cfg::ROOMS_MAX };
	std::pair<unsigned int, unsigned int> floorRange{ prop_cfg::FLOORS_TOTAL_MIN, prop_cfg::FLOORS_TOTAL_MAX };
	Status statusValue{};

	template<typename T>
	std::pair<T, T> set_pair(const T& min, const T& max, const std::string& msg1, const std::string& msg2, const std::string& errMsg = "")
	{
		std::pair<T, T> p;

		ConsoleUI::ConsoleUI::clear();
		p.first = InputReader::read<T>(min, max, msg1, errMsg);
		p.second = InputReader::read<T>(min, max, msg2, errMsg);
		ConsoleUI::ConsoleUI::clear();

		if (p.first > p.second)
		{
			T temp = p.first;
			p.first = p.second;
			p.second = temp;
		}

		return p;
	}

public:
	bool price = false;
	bool area = false;
	bool rooms = false;
	bool floor = false;
	bool status = false;

	void default_filters() {
		price = area = rooms = floor = status = false;
		priceRange = { prop_cfg::PRICE_MIN, prop_cfg::PRICE_MAX };
		areaRange = { prop_cfg::AREA_TOTAL_MIN, prop_cfg::AREA_TOTAL_MAX };
		roomsRange = { prop_cfg::ROOMS_MIN, prop_cfg::ROOMS_MAX };
		floorRange = { prop_cfg::FLOORS_TOTAL_MIN, prop_cfg::FLOORS_TOTAL_MAX };
		statusValue = Status{};
	}

	void flip_price() { price = !price; }
	void flip_area() { area = !area; }
	void flip_rooms() { rooms = !rooms; }
	void flip_floor() { floor = !floor; }
	void flip_status() { status = !status; }

	void set_price_range() {
		priceRange = set_pair<float>(
			prop_cfg::PRICE_MIN,
			prop_cfg::PRICE_MAX,
			prop_cfg::PRICE_MIN_MSG,
			prop_cfg::PRICE_MAX_MSG,
			prop_cfg::PRICE_ERR_MSG);
	}

	void set_area_range() {
		areaRange = set_pair<float>(
			prop_cfg::AREA_TOTAL_MIN,
			prop_cfg::AREA_TOTAL_MAX,
			prop_cfg::AREA_TOTAL_MIN_MSG,
			prop_cfg::AREA_TOTAL_MAX_MSG,
			prop_cfg::AREA_TOTAL_ERR_MSG);
	}

	void set_rooms_range() {
		roomsRange = set_pair<unsigned int>(
			prop_cfg::ROOMS_MIN,
			prop_cfg::ROOMS_MAX,
			prop_cfg::ROOMS_MIN_MSG,
			prop_cfg::ROOMS_MAX_MSG,
			prop_cfg::ROOMS_ERR_MSG);
	}

	void set_floor_range() {
		floorRange = set_pair<unsigned int>(
			prop_cfg::FLOOR_MIN,
			prop_cfg::FLOOR_MAX,
			prop_cfg::FLOOR_MIN_MSG,
			prop_cfg::FLOOR_MAX_MSG,
			prop_cfg::FLOOR_ERR_MSG);
	}

	void set_status() {
		statusValue = Property::read_status();
	}

	void apply_filters(Repository<Property>& repo) {
		if (price)  repo.remove([&](const auto& a) { return !between(a->price(), priceRange); });
		if (area)   repo.remove([&](const auto& a) { return !between(a->area_total(), areaRange); });
		if (rooms)  repo.remove([&](const auto& a) { return !between(a->rooms(), roomsRange); });
		if (floor)  repo.remove([&](const auto& a) { return !between(a->floor(), floorRange); });
		if (status) repo.remove([&](const auto& a) { return a->status() != statusValue; });
	}
};