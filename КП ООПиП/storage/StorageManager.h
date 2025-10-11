#pragma once

#include <memory>
#include <vector>
#include <iostream>

template<class T>
class StorageManager
{
protected:
	std::string m_filename;
public:
	StorageManager(std::string filename) : m_filename(filename) {}

	virtual void saveToFile(const std::vector<std::shared_ptr<T>>& objects) {
		FILE* file = fopen(m_filename.c_str(), "wb");
		if (file == nullptr) {
			std::cerr << "Файл \"" << m_filename << "\" не удалось открыть для записи.\n";
			return;
		}

		for (const auto& obj : objects) {
			fwrite(obj.get(), sizeof(T), 1, file);
		}

		fclose(file);
	}
	virtual std::vector<std::shared_ptr<T>> loadFromFile() const
	{
		FILE* file = fopen(m_filename.c_str(), "rb");
		if (file == nullptr) {
			std::cerr << "Файл \"" << m_filename << "\" не удалось открыть для чтения.\n";
			return {};
		}

		T obj;
		std::vector<std::shared_ptr<T>> objects;

		while (fread(&obj, sizeof(T), 1, file) == 1) {
			objects.push_back(std::make_shared<T>(obj));
		}

		fclose(file);
		return objects;
	}
};