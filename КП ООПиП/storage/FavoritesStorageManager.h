#pragma once

#include "../core/Favorites.h"
#include "StorageManager.h"

class FavoritesStorageManager : public StorageManager<Favorites>
{
public:
	FavoritesStorageManager(std::string filename) : StorageManager(filename) {}

	void saveToFile(const std::vector<std::shared_ptr<Favorites>>& objects) override {
		FILE* file = fopen(m_filename.c_str(), "wb");
		if (file == nullptr) {
			std::cerr << "Файл \"" << m_filename << "\" не удалось открыть для записи.\n";
			return;
		}

		for (const auto& obj : objects) {
			unsigned int id = obj->id();
			fwrite(&id, sizeof(unsigned int), 1, file);
			unsigned int size = obj->favorites().size();
			fwrite(&size, sizeof(unsigned int), 1, file);
			for (unsigned int i = 0; i < size; i++)
			{
				unsigned int ad_id = obj->favorites()[i];
				fwrite(&ad_id, sizeof(unsigned int), 1, file);
				std::cout << "fsm working\n";
			}
		}

		fclose(file);
	}
	std::vector<std::shared_ptr<Favorites>> loadFromFile() const 
	{
		FILE* file = fopen(m_filename.c_str(), "rb");
		if (file == nullptr) {
			std::cerr << "Файл \"" << m_filename << "\" не удалось открыть для чтения.\n";
			return {};
		}

		std::vector<std::shared_ptr<Favorites>> objects;

		unsigned int id;
		unsigned int size;
		unsigned int ad_id;

		while (fread(&id, sizeof(unsigned int), 1, file) == 1) {
			Favorites f{ id };
			fread(&size, sizeof(unsigned int), 1, file);
			for (unsigned int i = 0; i < size; i++)
			{
				fread(&ad_id, sizeof(unsigned int), 1, file);
				f.addFavorites(ad_id);
			}
			objects.push_back(std::make_shared<Favorites>(f));
		}

		fclose(file);
		return objects;
	}
};