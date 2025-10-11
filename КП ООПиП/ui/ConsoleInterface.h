#pragma once

#include <iostream>
#include <iomanip>
#include "../session/UserSession.h"

using namespace std;

class ConsoleInterface
{
private:
	std::shared_ptr<UserSession> m_session;
	const unsigned int width = 156;
	const unsigned int height = 41;
public:
	ConsoleInterface(){}
	ConsoleInterface(std::shared_ptr<UserSession> session)
		: m_session(session) { }

	void RenderMainScreen()
	{
		cout << '+' << std::setfill('-') << std::setw(width - 1) << '+' << std::endl << std::setfill(' ');
		cout << left << setw(width / 2) << "|user" << right << setw(width / 2) << "settigs|";
		cout << left << setw(width / 2) << "|Мои объявления" << right << setw(width / 2) << "Избранное|";

		cout << '+' << std::setfill('-') << std::setw(width - 1) << '+' << std::endl << std::setfill(' ');

		//cout << '+' << std::setfill('-') << std::setw(width - 1) << '+' << std::endl << std::setfill(' ');
	}
};