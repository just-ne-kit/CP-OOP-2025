#pragma once

#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <stdexcept>

template<class T>
class StorageManager {
    std::string m_filename;

public:
    StorageManager(const std::string& filename);

    void save(const std::vector<std::shared_ptr<T>>& objects) const;
    std::vector<std::shared_ptr<T>> load() const;
};

template<class T>
StorageManager<T>::StorageManager(const std::string& filename)
    : m_filename(filename) {
}

template<class T>
void StorageManager<T>::save(const std::vector<std::shared_ptr<T>>& objects) const {
    std::ofstream ofs(m_filename, std::ios::binary);
    if (!ofs) throw std::runtime_error("Не удалось открыть файл для записи");

    for (const auto& obj : objects) {
        obj->serialize(ofs);
        if (!ofs) throw std::runtime_error("Ошибка при записи объекта в файл");
    }
}

template<class T>
std::vector<std::shared_ptr<T>> StorageManager<T>::load() const {
    std::ifstream ifs(m_filename, std::ios::binary);
    if (!ifs) throw std::runtime_error("Не удалось открыть файл для чтения");

    std::vector<std::shared_ptr<T>> objects;

    while (true) {
        if (ifs.peek() == EOF) break;

        auto obj = std::make_shared<T>();
        obj->deserialize(ifs);

        if (!ifs) break;
        objects.push_back(obj);
    }

    return objects;
}

