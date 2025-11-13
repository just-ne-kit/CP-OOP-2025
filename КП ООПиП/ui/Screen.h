#include <algorithm>

#include "ConsoleInterface.h"
#include "../form/FormBuilder.h"

class Screen
{
private:
	ConsoleInterface gui;

	void run(FieldContext& fc) {
		while (true) {
			gui.drawLines(fc.getLines());

			Field& f = fc.fields[fc.currentY][fc.currentX];

			if (f.type == FieldType::Str || f.type == FieldType::Password) {
				gui.showCursor();

				// вычисляем позицию курсора
				int x = 0;
				int y = fc.currentY;

				for (int i = 0; i < fc.currentX; i++)
					x += fc.fields[y][i].to_str(false).size();

				x += f.left.size() + f.cur.size();

				gui.move_cursor(x, y);
			}
			else if (f.type == FieldType::Int || f.type == FieldType::Float)
			{
				gui.showCursor();

				// вычисляем позицию курсора
				int x = 0;
				int y = fc.currentY;

				for (int i = 0; i < fc.currentX; i++)
					x += fc.fields[y][i].to_str(false).size();

				//x += f.left.size() + f.maxLength - f.cur.size(); // ____|12
				x += f.left.size() + f.cur.size(); // 12|____

				gui.move_cursor(x, y);
			}
			else if (f.type == FieldType::Phone)
			{
				gui.showCursor();

				int x = 0;
				int y = fc.currentY;
				int n = f.cur.size();

				for (int i = 0; i < fc.currentX; i++)
					x += fc.fields[y][i].to_str(false).size();

				x += f.left.size() + std::string("+375 (").size() + std::min(n, 2);

				if (n > 1) x += std::string(") ").size() + std::min(n - 2, 3);
				else if (n > 4) x += 1 + std::min(n - 5, 2);
				else if (n > 5) x += 1 + std::min(n - 7, 2);

				gui.move_cursor(x, y);
			}
			else {
				gui.hideCursor();
			}
			
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
			.row(Str, 20, "Введите новый логин: ", "")
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

	void test_screen() {
		FieldContext fc = FormBuilder()
			.row({ Field(Str, 3, "Введите текст: ", ""), Field(Password, 2, "Введите пароль: ", "") })
			.row({
				Field(Float, 20, "Float1: ", ""),
				Field(Float, 20, "Float2: ", "")
				}
			)
			.row({
	Field(Int, 15, "Int:", ""),
	Field(Phone, 15, " | Phone:", "|right|"),
	Field(Str, 15, "Номер телефона:", "")
				})
			.row(Button, 0, "", "", "[Button1]")
			.build();

		run(fc);
	}
};