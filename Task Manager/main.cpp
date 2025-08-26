#include "user_interface.h"
#include "command_interface.h"

int main()
{

	TaskManager manager;
	manager.load();

	fmt::print(fg(COLOR_BLUE) | fmt::emphasis::bold | fmt::emphasis::underline, "Welcome to the Task Manager\n\n");
	fmt::print(fg(COLOR_BLUE) | fmt::emphasis::bold, "Choose one of the following modes...{0}{1}{2}",
													 "\n1. Basic",
													 "\n2. Advanced",
													 "\n3. Exit\n\n");

	int choiceAsNum = -1;
	while (choiceAsNum == -1)
	{
		std::string choice;
		std::getline(std::cin, choice);
		choiceAsNum = isNumber(choice) ? std::stoi(choice) : -1;

		switch (choiceAsNum)
		{
		case 1:
		{
			clearScreen();
			UserInterface UI(manager);
			UI.init();
			break;
		}
		case 2:
		{
			clearScreen();
			CommandInterface CI(manager);
			CI.init();
			break;
		}
		case 3:
			break;
		default:
			fmt::print(fg(COLOR_INVALID_RED) | fmt::emphasis::bold, "Invalid input\n");
			break;
		}
	}

	return 0;
}
