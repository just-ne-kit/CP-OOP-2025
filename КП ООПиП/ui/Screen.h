#include "ConsoleInterface.h"

#include <conio.h>

enum FieldType {
	Input,
	Password,
	Button
};

class Field {
private:
	const char fillCh = ' ';
	const char passwordCh = '*';
	std::string WrapWithFocus(const std::string& s) const { return ">" + s + "<"; }
public:
	FieldType type;

	std::string left;
	std::string right;

	std::string prev;
	std::string cur;
	unsigned int maxLength;

	Field(
		FieldType type,
		unsigned int maxLength,
		const std::string& left,
		const std::string& cur,
		const std::string& right = ""
	){
		this->type = type;
		this->left = left;
		this->right = right;
		this->prev = cur;
		this->cur = cur;
		this->maxLength = maxLength;
	}

	void commit() { prev = cur; }
	void rollback() { cur = prev; }

	void append(const char ch) {
		if (type == FieldType::Button) return;
		if (cur.size() < maxLength) cur += ch;
	}
	void backspace() {
		if (type == FieldType::Button) return;
		if (!cur.empty()) cur.pop_back();
	}

	std::string to_str(bool focused) const
	{
		if (type == FieldType::Password) {
			std::string size = std::string(maxLength - cur.size(), fillCh) + "<" + std::to_string(cur.size()) + "/" + std::to_string(maxLength) + ">";
			return left + std::string(cur.size(), passwordCh) + size + right;
		}
		else if (type == FieldType::Button) {
			return left + (focused ? WrapWithFocus(cur) : cur) + right;
		}
		else if (type == FieldType::Input) {
			std::string size = std::string(maxLength - cur.size(), fillCh) + "<" + std::to_string(cur.size()) + "/" + std::to_string(maxLength) + ">";
			return left + cur + size + right;
		}
		return "";
	}
};

class FieldContext
{
public:
	unsigned int count;
	unsigned int currentY; //index [0, ... , count - 1]
	unsigned int currentX;
	std::vector<std::vector<Field>> fields;

	FieldContext(std::vector<std::vector<Field>> fields) : currentY(0), fields(fields) {
		count = fields.size();
	}

	void handleInput() {
		int ch = _getch();

		// спец-клавиши: стрелки и т.п.
		if (ch == 0 || ch == 224) {
			ch = _getch(); // второй байт

			Field& f = fields[currentY][currentX];
			f.commit();

			switch (ch) {
			case 72: up(); break;
			case 80: down(); break;
			case 75: left(); break;
			case 77: right(); break;
			}
			return; // ← ВАЖНО: не продолжаем дальше!
		}

		// обычные клавиши
		Field& f = fields[currentY][currentX];

		switch (ch) {
		case '\r': f.commit(); break;
		case '\b': f.backspace(); break;
		case 27:   f.rollback(); break;
		default:   f.append(static_cast<char>(ch)); break;
		}
	}

	void down() {
		currentY = (currentY + 1) % count; 
		if (currentX > fields[currentY].size()) currentX = fields[currentY].size() - 1;
	}
	void up() {
		currentY = (currentY + count - 1) % count;
		if (currentX > fields[currentY].size()) currentX = fields[currentY].size() - 1;
	}
	void left() {
		currentX = (currentX + fields[currentY].size() - 1) % fields[currentY].size();
	}
	void right() {
		currentX = (currentX + 1) % fields[currentY].size();
	}

	void commitAll() {
		for (unsigned int i = 0; i < count; i++)
			for (unsigned int j = 0; j < fields[i].size(); j++)
				fields[i][j].commit();
	}

	std::vector<std::string> getLines()
	{
		std::vector<std::string> res;
		
		for (unsigned int i = 0; i < count; i++) {
			res.push_back("");
			for (unsigned int j = 0; j < fields[i].size(); j++) {
				res[i] += fields[i][j].to_str(i == currentY && j == currentX);
			}
		}

		return res;
	}
};

class FormBuilder {
private:
	std::vector<std::vector<Field>> rows;

public:
	FormBuilder& row(FieldType type, unsigned int maxLength, const std::string& left, const std::string& cur, const std::string& right = "") {
		rows.push_back({ Field(type, maxLength, left, cur, right) });
		return *this;
	}

	FormBuilder& row(std::vector<Field> fieldsInRow) {
		rows.push_back(std::move(fieldsInRow));
		return *this;
	}

	FieldContext build() {
		return FieldContext(rows);
	}
};


class Screen
{
private:
	ConsoleInterface gui;

	void run(FieldContext& fc) {
		while (true) {
			gui.drawLines(fc.getLines());
			fc.handleInput();
		}
	}
public:
	Screen(){}

	/*
	 @brief Введите новый логин: login
	 @brief Введите новый пароль: password_1
	 @brief Повторите пароль: password_2
	*/
	int auth_1(std::string& outLogin, std::string& outPassword) {

		FieldContext fc = FormBuilder()
			.row(Input, 20, "Введите новый логин: ", "")
			.row(Password, 20, "Введите новый пароль: ", "")
			.row(Password, 20, "Повторите пароль: ", "")
			.row(Button, 0, "", "[Регистрация]")
			.build();

		run(fc);

		//outLogin = fc.fields[0][0].cur;
		//outPassword = fc.fields[1][0].cur;
		
		//заглушка
		return 0;
	}
};