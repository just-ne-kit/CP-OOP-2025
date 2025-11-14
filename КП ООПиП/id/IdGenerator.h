#pragma once

#include <string>
#include <iostream>
#include <fstream>

class IdGenerator {
private:
    std::string m_filename;

public:
    explicit IdGenerator(const std::string& filename)
        : m_filename(filename) {}

    unsigned int next() const {
        unsigned int res = 0;

        std::fstream file(m_filename, std::ios::in | std::ios::out | std::ios::binary);

        if (file.is_open()) {
            file.read(reinterpret_cast<char*>(&res), sizeof(res));

            if (!file) {
                res = 0;
                file.clear();
            }

            ++res;

            file.seekp(0, std::ios::beg);
            file.write(reinterpret_cast<const char*>(&res), sizeof(res));
        } else {
            std::ofstream ofs(m_filename, std::ios::binary);
            if (!ofs) {
                std::cerr << "Файл \"" << m_filename << "\" не удалось открыть для записи.\n";
                return 0;
            }
            res = 1;
            ofs.write(reinterpret_cast<const char*>(&res), sizeof(res));
        }

        return res;
    }
};
