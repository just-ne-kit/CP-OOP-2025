#include "ConsoleInterface.h"
#include "InputReader.h"

enum FieldType {
	Input,
	Password,
	Button
};

class Field {
public:
	std::string prev;
	std::string cur;
	unsigned int maxLength;

	Field(std::string cur, unsigned int maxLength) : prev(cur), cur(cur), maxLength(maxLength) {}

	void commit() { prev = cur; }
	void rollback() { cur = prev; }

	std::string to_str()
	{
		return cur + std::string(maxLength - cur.size(), ' ') + "<" + std::to_string(cur.size()) + "/" + std::to_string(maxLength) + " >";
	}
};

class FieldContext
{
public:
	unsigned int count;
	unsigned int current; //index [0, ... , count - 1]
	std::vector<Field> fields;

	FieldContext(std::vector<Field> fields) : current(0), fields(fields) {
		count = fields.size();
	}

	void up() { current = (current + 1) % count; }
	void down() { current = (current + count - 1) % count; }

	void commitAll() {
		for (unsigned int i = 0; i < count; i++) fields[i].commit();
	}
};

class Screen
{
private:
	ConsoleInterface gui;
	
	std::string buffer;

	void UpdateBuffer()
	{

	}
public:
	Screen(){}

	/*
	 @brief Введите новый логин: login
	 @brief Введите новый пароль: password_1
	 @brief Повторите пароль: password_2
	*/
	int auth_1(std::string& outLogin, std::string& outPassword) {

		FieldContext fc({
			{"", 10},
			{"", 10},
			{"", 10},
			{" ", 0}
		});

		while(true){
			std::vector<std::string> lines = {
				"Введите новый логин: "  + fc.fields[0].to_str(),
				"Введите новый пароль: " + fc.fields[1].to_str(),
				"Повторите пароль: "	 + fc.fields[2].to_str(),
				"Регистрация [" + fc.fields[3].cur + "]"
			};

			gui.drawLines(lines);

			//input
			char ch = _getch();

			std::string& s = fc.fields[fc.current].cur;

			if (ch == '\r') fc.fields[fc.current].commit();
			else if (ch == '\b' && !s.empty()) s.pop_back();
			else if (ch == 27) fc.fields[fc.current].rollback();
			else if (ch == 72) fc.up();
			else if (ch == 80) fc.down();
			else s += ch;
		}

		outLogin = fc.fields[0].cur;
		outPassword = fc.fields[1].cur;
		
		//заглушка
		return 0;
	}
};