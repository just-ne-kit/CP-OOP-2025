#pragma once

#include <string>
#include <iostream>

class IdGenerator
{
private:
	std::string m_filename;
public:
	explicit IdGenerator(std::string filename)
		: m_filename(filename) { }

	//Вернет 0 в случае ошибки
	const unsigned int next() const
	{
		FILE* file = fopen(m_filename.c_str(), "rb+");
		
		unsigned int res = 0;

		if (file != nullptr) {
			//Считываем текущий максимальный id
			fread(&res, sizeof(res), 1, file);
			res++;
			fseek(file, 0, SEEK_SET);
			fwrite(&res, sizeof(res), 1, file);
			fclose(file);
		}
		else {
			std::cerr << "Файл \"" << m_filename << "\" не удалось открыть для чтения.\n";
		}

		return res;
	}
};