#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "task_manager.h"
#include "utils.h"
#include <regex>

using namespace utils;

class UserInterface
{

private:
	TaskManager m_manager;
	static const std::regex m_dateRegex;

	void displayOptions()const;
	int getUserId()const;
	std::string getUserName()const;
	std::string getUserDueDate()const;
	const Task::Priority getUserPriority()const;
	const Task::Status getUserStatus()const;

public:
	UserInterface();
	void init();
	void userAddTask();
	void userRemoveTask();
	void userEditTask();
	void userShowTasks()const;

};

#endif
