#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "task_manager.h"
#include "utils.h"

using namespace utils;

class UserInterface
{

private:
	TaskManager m_manager;

	void displayOptions()const;
	int getUserId()const;
	std::string getUserName()const;
	Date getUserDueDate()const;
	const Task::Priority getUserPriority()const;
	const Task::Status getUserStatus()const;

public:
	UserInterface(TaskManager& manager);
	void init();
	void userAddTask();
	void userRemoveTask();
	void userEditTask();
	void userSortTasks();
	void userShowTasks()const;

};

#endif
