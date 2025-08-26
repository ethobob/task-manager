#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include "task.h"
#include <vector>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

class TaskManager
{

private:
	std::vector<Task> m_taskList;

	Task& getTaskById(const int id);

public:
	void addTask(const Task& task);
	void removeTask(const int id);

	void editTaskName(const int id, std::string newName);
	void editTaskDueDate(const int id, Date newDueDate);
	void editTaskPriority(const int id, Task::Priority newPriority);
	void editTaskStatus(const int id, Task::Status newStatus);

	void sortByName();
	void sortByDueDate();
	void sortByPriority();
	void sortByStatus();

	void printList()const;
	void printTask(const int id);
	bool isEmpty()const;
	bool doesExist(const int id)const;
	void save()const;
	void load();

};

#endif
