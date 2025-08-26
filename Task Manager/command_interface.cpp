#include "command_interface.h"

CommandInterface::CommandInterface(TaskManager& manager)
	: m_manager(manager)
{

	m_commandMap = {
		{"list", [this](const std::string& args) { userListCommand(args); } },
		{"add", [this](const std::string& args) { userAddCommand(args); } },
		{"remove", [this](const std::string& args) { userRemoveCommand(args); } },
		{"edit", [this](const std::string& args) { userEditCommand(args); } },
		{"sort", [this](const std::string& args) { userSortCommand(args); } }
	};

}

void CommandInterface::init()
{
	while (true)
	{
		std::string line;
		getline(std::cin, line);

		if (line.compare("todo exit") == 0)
		{
			m_manager.save();
			break;
		}

		if (line.compare("todo clear") == 0)
		{
			clearScreen();
			continue;
		}

		if (line.compare("todo help") == 0)
		{
			clearScreen();
			userHelpCommand();
			continue;
		}

		std::istringstream iss(line);

		std::string starter, command, args;

		if (!(iss >> starter) || starter.compare("todo") != 0 || !(iss >> command))
		{
			fmt::print(fg(COLOR_INVALID_RED) | fmt::emphasis::bold, "Invalid Command, type \"todo help\" for a list of commands\n");
			continue;
		}

		getline(iss >> std::ws, args);

		try
		{
			m_commandMap.at(command)(args);
		}
		catch (const std::invalid_argument& ia)
		{
			fmt::print(fg(COLOR_INVALID_RED) | fmt::emphasis::bold, "Invalid Arguments\n");
		}
		catch (const std::exception& e)
		{
			fmt::print(fg(COLOR_INVALID_RED) | fmt::emphasis::bold, "Invalid Command, type \"todo help\" for a list of commands\n");
		}

	}
}

void CommandInterface::userAddCommand(const std::string& args)
{
	if (args.empty())
		throw std::invalid_argument("Invalid Arguments");

	Task task(args);
	m_manager.addTask(task);
	fmt::print(fg(COLOR_GREEN) | fmt::emphasis::bold, "Task created with ID: {0}\n", task.getID());
}

void CommandInterface::userRemoveCommand(const std::string& args)
{
	if (args.empty() || !isNumber(args) || !m_manager.doesExist(stoi(args)))
		throw std::invalid_argument("Invalid Arguments");

	m_manager.removeTask(stoi(args));
	fmt::print(fg(COLOR_GREEN) | fmt::emphasis::bold, "Task removed\n");
}

void CommandInterface::userEditCommand(const std::string& args)
{
	std::string id, variable, newValue;
	std::istringstream iss(args);

	if (args.empty() || !(iss >> id) || !isNumber(id) || !m_manager.doesExist(stoi(id)))
		throw std::invalid_argument("Invalid Arguments");

	if (!(iss >> variable))
		throw std::invalid_argument("Invalid Arguments");

	getline(iss >> std::ws, newValue);

	if (variable.compare("name") == 0 || variable.compare("title") == 0)
	{
		m_manager.editTaskName(stoi(id), newValue);
		fmt::print(fg(COLOR_GREEN) | fmt::emphasis::bold, "Task name changed\n");
		return;
	}

	if (variable.compare("duedate") == 0 || variable.compare("date") == 0)
	{
		if (!std::regex_match(newValue, Date::DATE_REGEX))
			throw std::invalid_argument("Invalid Arguments");
		m_manager.editTaskDueDate(stoi(id), Date(newValue));
		fmt::print(fg(COLOR_GREEN) | fmt::emphasis::bold, "Task due date changed\n");
		return;
	}

	if (variable.compare("priority") == 0)
	{
		if (newValue.compare("low") == 0)
			m_manager.editTaskPriority(stoi(id), Task::LOW);
		else if (newValue.compare("medium") == 0)
			m_manager.editTaskPriority(stoi(id), Task::MEDIUM);
		else if (newValue.compare("high") == 0)
			m_manager.editTaskPriority(stoi(id), Task::HIGH);
		else
			throw std::invalid_argument("Invalid Arguments");
		fmt::print(fg(COLOR_GREEN) | fmt::emphasis::bold, "Task priority changed\n");
		return;
	}

	if (variable.compare("status") == 0)
	{
		if (newValue.compare("incomplete") == 0)
			m_manager.editTaskStatus(stoi(id), Task::INCOMPLETE);
		else if (newValue.compare("complete") == 0)
			m_manager.editTaskStatus(stoi(id), Task::COMPLETE);
		else
			throw std::invalid_argument("Invalid Arguments");
		fmt::print(fg(COLOR_GREEN) | fmt::emphasis::bold, "Task status changed\n");
		return;
	}

	throw std::invalid_argument("Invalid Arguments");
}

void CommandInterface::userSortCommand(const std::string& args)
{
	if (args.compare("name") == 0 || args.compare("title") == 0)
		m_manager.sortByName();
	else if (args.compare("duedate") == 0 || args.compare("date") == 0)
		m_manager.sortByDueDate();
	else if (args.compare("priority") == 0)
		m_manager.sortByPriority();
	else if (args.compare("status") == 0)
		m_manager.sortByStatus();
	else
		throw std::invalid_argument("Invalid Arguments");
	fmt::print(fg(COLOR_GREEN) | fmt::emphasis::bold, "Sorted\n");
}

void CommandInterface::userListCommand(const std::string& args)
{
	clearScreen();
	m_manager.printList();
}

void CommandInterface::userHelpCommand()const
{
	fmt::print(fg(COLOR_BLUE) | fmt::emphasis::bold,
		"\"todo clear\" - clears the screen\n{0}{1}{2}{3}{4}{5}",
		"\"todo add (name)\" - adds a task to the list\n",
		"\"todo remove (id)\" - removes a task from the list\n",
		"\"todo edit (id) (characteristic) (new value)\" - changes a value from a task\n",
		"\"todo sort (characteristic)\" - sorts tasks by characteristic\n",
		"\"todo list\" - lists all tasks\n",
		"\"todo exit\" - exits the program\n");
}