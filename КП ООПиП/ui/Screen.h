#pragma once

#include "ConsoleInterface.h"
#include "../form/FormBuilder.h"

class Screen
{
private:
	ConsoleInterface gui;

	void run(FieldContext &fc)
	{
		while (true)
		{
			gui.drawLines(fc.getLines());

			Field &f = fc.fields[fc.currentY][fc.currentX];

			if (f.type == FieldType::Str || f.type == FieldType::Password)
			{
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

				// x += f.left.size() + f.maxLength - f.cur.size(); // ____|12
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

				x += f.left.size() + std::string("+375 (").size() + min(n, 2);

				auto Min = [](int a, int b) { return a < b ? a : b; };

				if (n > 1)
					x += std::string(") ").size() + Min(n - 2, 3);
				else if (n > 4)
					x += 1 + Min(n - 5, 2);
				else if (n > 5)
					x += 1 + Min(n - 7, 2);

				gui.move_cursor(x, y);
			}
			else if (f.type == FieldType::ButtonExit && f.isActivated)
			{
				break;
			}
			else
			{
				gui.hideCursor();
			}

			fc.handleInput();
		}
	}

public:
	Screen() {}

	int auth(std::string &outLogin, std::string &outPassword)
	{

		FieldContext fc = FormBuilder()
							  .row(Str, 20, "Введите логин: ")
							  .row(Password, 20, "Введите пароль: ")
							  .row(ButtonExit, 0, "", "", "[Вход]")
							  .row(ButtonExit, 0, "", "", "[Завершение программы]")
							  .build();

		run(fc);

		outLogin = fc.fields[0][0].cur;
		outPassword = fc.fields[1][0].cur;

		int res = 0;
		if (fc.fields[2][0].isActivated) res = 1;
		if (fc.fields[3][0].isActivated) res = 2;

		return res;
	}

	void auth_error()
	{
		FieldContext fc = FormBuilder()
							  .row(Text, 20, "Неверный логин или пароль.")
							  .row(ButtonExit, 0, "", "", "[Продолжить]")
							  .build();

		run(fc);
	}

	int admin_main()
	{
		FieldContext fc = FormBuilder()
			.row(ButtonExit, 0, "", "", "[Создать риэлтора]")
			.row(ButtonExit, 0, "", "", "[Выход]")
			.build();

		run(fc);

		int res = 0;
		if (fc.fields[0][0].isActivated) res = 1;
		if (fc.fields[1][0].isActivated) res = 2;

		return res;
	}

	int admin_create_realtor(std::string& login, std::string& p1, std::string& p2)
	{
		FieldContext fc = FormBuilder()
			.row(Str, 20, "Введите логин: ")
			.row(Password, 20, "Введите пароль: ")
			.row(Password, 20, "Повторите пароль: ")
			.row(ButtonExit, 0, "", "", "[Продолжить]")
			.row(ButtonExit, 0, "", "", "[Выход]")
			.build();

		run(fc);

		login = fc.fields[0][0].cur;
		p1 = fc.fields[1][0].cur;
		p2 = fc.fields[2][0].cur;

		return fc.fields[2][0].isActivated ? 1 : 0;
	}
	void admin_create_realtor_failed_login()
	{
		FieldContext fc = FormBuilder()
			.row(Text, 20, "Такой пользователь уже существует.")
			.row(ButtonExit, 0, "", "", "[Продолжить]")
			.build();

		run(fc);
	}
	void admin_create_realtor_failed_password()
	{
		FieldContext fc = FormBuilder()
			.row(Text, 20, "Повторный пароль введен неверно.")
			.row(ButtonExit, 0, "", "", "[Продолжить]")
			.build();

		run(fc);
	}
	void admin_create_realtor_success()
	{
		FieldContext fc = FormBuilder()
			.row(Text, 20, "Новый риэлтор добавлен.")
			.row(ButtonExit, 0, "", "", "[Продолжить]")
			.build();

		run(fc);
	}
	
	void realtor_main(const std::string& fullName)
	{
		FieldContext fc = FormBuilder()
							  .row(ButtonExit, 0, "", "", "[" + fullName + "]")
							  .row(ButtonExit, 0, "", "", "[Мои]")
							  .row({
								{Decrementer, 0, "", "", "[ <- ]"},
								{ButtonExit, 0, "", "", "[Подробнее]" },
								{Incrementer, 0, "", "", "[ -> ]"}})
							  .build();
		run(fc);
	}
};