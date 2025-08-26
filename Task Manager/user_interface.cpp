#include "user_interface.h"

// -------------------
//    Constructors
// -------------------

UserInterface::UserInterface(TaskManager& manager)
	: m_manager(manager)
{ }

// -------------------
//       Helpers
// -------------------

void UserInterface::displayOptions()const
{
	fmt::print(fg(COLOR_BLUE) | fmt::emphasis::bold,
		"Choose one of the following...\n{0}{1}{2}{3}{4}{5}",
		"\n1. Add Task",
		"\n2. Remove Task",
		"\n3. Edit Task",
		"\n4. Sort Tasks",
		"\n5. Show Tasks",
		"\n6. Save and Exit\n\n");
}

int UserInterface::getUserId()const
{
	std::string idAsString;
	bool validNumber = false;
	while (!validNumber)
	{
		std::getline(std::cin, idAsString);

		if (!isNumber(idAsString))
			fmt::print(fg(COLOR_INVALID_RED) | fmt::emphasis::bold, "Invalid input\n");
		else if (!m_manager.doesExist(stoi(idAsString)))
			fmt::print(fg(COLOR_INVALID_RED) | fmt::emphasis::bold, "No tasks exist with that ID\n");
		else
			validNumber = true;

	}
	return stoi(idAsString);
}

std::string UserInterface::getUserName()const
{
	std::string name;
	while (name.empty())
	{
		fmt::print(fg(COLOR_BLUE) | fmt::emphasis::bold, "\nEnter the name of the task: ");
		std::getline(std::cin, name);
		if (name.empty())
			fmt::print(fg(COLOR_INVALID_RED) | fmt::emphasis::bold, "Name cannot be empty\n");
	}
	return name;
}

Date UserInterface::getUserDueDate()const
{
	std::string dueDateAsString;
	while (!std::regex_match(dueDateAsString, Date::DATE_REGEX))
	{
		fmt::print(fg(COLOR_BLUE) | fmt::emphasis::bold, "\nEnter the due date for the task (MM/DD/YYYY): ");
		std::getline(std::cin, dueDateAsString);
		if (!std::regex_match(dueDateAsString, Date::DATE_REGEX))
			fmt::print(fg(COLOR_INVALID_RED) | fmt::emphasis::bold, "Invalid date format\n");
	}

	return Date(dueDateAsString);
}


const Task::Priority UserInterface::getUserPriority()const
{
	Task::Priority priority = Task::PRIORITY_UNKNOWN;
	while (priority == Task::PRIORITY_UNKNOWN)
	{
		fmt::print(fg(COLOR_BLUE) | fmt::emphasis::bold, "\nEnter the priority of the task (1 - Low, 2 - Medium, 3 - High): ");
		std::string priorityAsString;
		std::getline(std::cin, priorityAsString);
		int priorityAsNum = (isNumber(priorityAsString) && priorityAsString.size() == 1) ? (priorityAsString[0] - '0') : -1;

		priority = priorityAsNum == 1 ? Task::LOW :
				   priorityAsNum == 2 ? Task::MEDIUM :
				   priorityAsNum == 3 ? Task::HIGH : Task::PRIORITY_UNKNOWN;
		
		if (priority == Task::PRIORITY_UNKNOWN)
			fmt::print(fg(COLOR_INVALID_RED) | fmt::emphasis::bold, "Invalid input\n");

	}
	return priority;
}

const Task::Status UserInterface::getUserStatus()const
{
	Task::Status status = Task::STATUS_UNKNOWN;
	while (status == Task::STATUS_UNKNOWN)
	{
		fmt::print(fg(COLOR_BLUE) | fmt::emphasis::bold, "\nEnter the status of the task (1 - Incomplete, 2 - Complete): ");
		std::string statusAsString;
		std::getline(std::cin, statusAsString);
		int statusAsNum = (isNumber(statusAsString) && statusAsString.size() == 1) ? (statusAsString[0] - '0') : -1;

		status = statusAsNum == 1 ? Task::INCOMPLETE :
				 statusAsNum == 2 ? Task::COMPLETE : Task::STATUS_UNKNOWN;

		if (status == Task::STATUS_UNKNOWN)
			fmt::print(fg(COLOR_INVALID_RED) | fmt::emphasis::bold, "Invalid input\n");

	}
	return status;
}

// -------------------
//      Functions
// -------------------

void UserInterface::init()
{
	fmt::print(fg(COLOR_BLUE) | fmt::emphasis::bold | fmt::emphasis::underline, "Welcome to the Task Manager!\n\n");

	while (true)
	{
		displayOptions();

		std::string choice;
		std::getline(std::cin, choice);
		int choiceAsNum = isNumber(choice) ? std::stoi(choice) : -1;

		switch (choiceAsNum)
		{
		case 1:
			userAddTask();
			break;
		case 2:
			userRemoveTask();
			break;
		case 3:
			userEditTask();
			break;
		case 4:
			userSortTasks();
			break;
		case 5:
			userShowTasks();
			break;
		case 6:
			m_manager.save();
			return;
		default:
			clearScreen();
			fmt::print(fg(COLOR_INVALID_RED) | fmt::emphasis::bold, "Invalid input\n\n");
			break;
		}

	}
}

void UserInterface::userAddTask()
{
	clearScreen();

	std::string name = getUserName();
	Date dueDate = getUserDueDate();
	Task::Priority priority = getUserPriority();
	Task::Status status = getUserStatus();

	Task task(name, dueDate, priority, status);
	m_manager.addTask(task);

	clearScreen();

}

void UserInterface::userRemoveTask()
{
	userShowTasks();
	if (m_manager.isEmpty()) return;
	fmt::print(fg(COLOR_BLUE) | fmt::emphasis::bold, "Enter the ID of the task you would like to delete: ");
	int id = getUserId();
	m_manager.removeTask(id);
	clearScreen();
}

void UserInterface::userEditTask()
{
	userShowTasks();
	if (m_manager.isEmpty()) return;
	fmt::print(fg(COLOR_BLUE) | fmt::emphasis::bold, "Enter the ID of the task you would like to edit: ");
	int id = getUserId();
	clearScreen();
	m_manager.printTask(id);

	fmt::print(fg(COLOR_BLUE) | fmt::emphasis::bold,
		"What would you like to edit about this task?\n{0}{1}{2}{3}{4}",
		"Choose one of the following...\n\n",
		"1. Name",
		"\n2. Due Date",
		"\n3. Priority",
		"\n4. Status\n\n");

	while (true)
	{
		std::string choice;
		std::getline(std::cin, choice);
		int choiceAsNum = isNumber(choice) ? std::stoi(choice) : -1;

		std::string name;
		Date dueDate;
		Task::Priority priority;
		Task::Status status;

		switch (choiceAsNum)
		{
		case 1:
			name = getUserName();
			m_manager.editTaskName(id, name);
			clearScreen();
			return;
		case 2:
			dueDate = getUserDueDate();
			m_manager.editTaskDueDate(id, dueDate);
			clearScreen();
			return;
		case 3:
			priority = getUserPriority();
			m_manager.editTaskPriority(id, priority);
			clearScreen();
			return;
		case 4:
			status = getUserStatus();
			m_manager.editTaskStatus(id, status);
			clearScreen();
			return;
		default:
			fmt::print(fg(COLOR_INVALID_RED) | fmt::emphasis::bold, "Invalid input\n");
			break;
		}
	}

}

void UserInterface::userSortTasks()
{
	clearScreen();
	fmt::print(fg(COLOR_BLUE) | fmt::emphasis::bold,
		"How would you like to sort your tasks?\n{0}{1}{2}{3}{4}",
		"Choose one of the following...\n\n",
		"1. Name",
		"\n2. Due Date",
		"\n3. Priority",
		"\n4. Status\n\n");

	while (true)
	{
		std::string choice;
		std::getline(std::cin, choice);
		int choiceAsNum = isNumber(choice) ? std::stoi(choice) : -1;

		switch (choiceAsNum)
		{
		case 1:
			m_manager.sortByName();
			clearScreen();
			return;
		case 2:
			m_manager.sortByDueDate();
			clearScreen();
			return;
		case 3:
			m_manager.sortByPriority();
			clearScreen();
			return;
		case 4:
			m_manager.sortByStatus();
			clearScreen();
			return;
		default:
			fmt::print(fg(COLOR_INVALID_RED) | fmt::emphasis::bold, "Invalid input\n");
			break;
		}
	}
}

void UserInterface::userShowTasks()const
{
	clearScreen();
	m_manager.printList();
}