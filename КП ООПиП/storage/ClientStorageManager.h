#pragma once

#include "../core/User.h"
#include <memory>
#include <vector>
#include <iostream>

class ClientStorageManager
{
private:
	std::string m_filename;
public:
	ClientStorageManager(std::string filename) : m_filename(filename) {}

	void saveToFile(const std::vector<std::shared_ptr<User>>& clients) {
		FILE* file = fopen(m_filename.c_str(), "wb");
		if (file == nullptr) {
			std::cerr << "Файл \"" << m_filename << "\" не удалось открыть для записи.\n";
			return;
		}
		
		for (const auto& client : clients) {
			if (fwrite(client.get(), sizeof(User), 1, file) != 1) {
				std::cerr << "Ошибка записи клиента с ID " << client->id() << "\n";
			}
		}
		
		fclose(file);
	}
	std::vector<std::shared_ptr<User>> loadFromFile() const
	{
		FILE* file = fopen(m_filename.c_str(), "rb");
		if (file == nullptr) {
			std::cerr << "Файл \"" << m_filename << "\" не удалось открыть для чтения.\n";
			return {};
		}

		User client;
		std::vector<std::shared_ptr<User>> clients;

		while (fread(&client, sizeof(User), 1, file) == 1) {
			clients.push_back(std::make_shared<User>(client));
		}

		fclose(file);
		return clients;
	}
};