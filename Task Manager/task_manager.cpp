#include "task_manager.h"

// -------------------
//       Helpers
// -------------------

Task& TaskManager::getTaskById(const int id)
{
	for (int i = 0; i < m_taskList.size(); i++)
	{
		Task& task = m_taskList.at(i);
		if (task.getID() == id)
		{
			return task;
		}
	}
}

// -------------------
//      Functions
// -------------------

void TaskManager::addTask(const Task& task)
{
	m_taskList.push_back(task);
	save();
}

void TaskManager::removeTask(const int id)
{
	for (int i = 0; i < m_taskList.size(); i++)
		if (m_taskList.at(i).getID() == id)
			m_taskList.erase(m_taskList.begin() + i);
	save();
}

void TaskManager::editTaskName(const int id, std::string newName)
{
	Task& task = getTaskById(id);
	task.setTitle(newName);
	save();
}

void TaskManager::editTaskDueDate(const int id, std::string newDueDate)
{
	Task& task = getTaskById(id);
	task.setDueDate(newDueDate);
	save();
}

void TaskManager::editTaskPriority(const int id, Task::Priority newPriority)
{
	Task& task = getTaskById(id);
	task.setPriority(newPriority);
	save();
}

void TaskManager::editTaskStatus(const int id, Task::Status newStatus)
{
	Task& task = getTaskById(id);
	task.setStatus(newStatus);
	save();
}

void TaskManager::sortByName()
{
	std::sort(m_taskList.begin(), m_taskList.end(), [](Task t1, Task t2)
		{
			return t1.getTitle().compare(t2.getTitle()) == -1 ? true : false;
		});
	save();
}

void TaskManager::sortByDueDate()
{

}

void TaskManager::sortByPriority()
{
	std::sort(m_taskList.begin(), m_taskList.end(), [](Task t1, Task t2)
		{
			return t1.getPriority() > t2.getPriority();
		});
}

void TaskManager::sortByStatus()
{
	std::sort(m_taskList.begin(), m_taskList.end(), [](Task t1, Task t2)
		{
			return t1.getStatus() < t2.getStatus();
		});
}

void TaskManager::printList()const
{
	fmt::print(fg(COLOR_BLUE) | fmt::emphasis::bold | fmt::emphasis::underline, "\n\tTask List\n\n");

	if (m_taskList.empty())
	{
		fmt::print(fg(COLOR_GREEN) | fmt::emphasis::bold, "Empty!\n\n");
		return;
	}

	for (const Task task : m_taskList)
	{
		task.printTask();
		std::cout << "\n\n";
	}
}

void TaskManager::printTask(const int id)
{
	Task& task = getTaskById(id);
	task.printTask();
	std::cout << "\n\n";
}

bool TaskManager::isEmpty()const
{
	return m_taskList.empty();
}

bool TaskManager::doesExist(const int id)const
{
	for (int i = 0; i < m_taskList.size(); i++)
		if (m_taskList.at(i).getID() == id)
			return true;
	return false;
}

// -------------------
//        JSON
// -------------------

void TaskManager::save()const
{
	std::ofstream tasks("tasks.json");
	json tasksAsJson = json::array();
	for (int i = 0; i < m_taskList.size(); i++)
	{
		Task task = m_taskList.at(i);
		json taskAsJson =
		{
			{"title", task.getTitle()},
			{"dueDate", task.getDueDate()},
			{"priority", task.getPriority()},
			{"status", task.getStatus()}
		};
		tasksAsJson.push_back(taskAsJson);
	}
	tasks << tasksAsJson.dump(4);
	tasks.close();
}

void TaskManager::load()
{
	std::ifstream tasks("tasks.json");
	json tasksAsJson = json::array();
	tasks >> tasksAsJson;
	for (int i = 0; i < tasksAsJson.size(); i++)
	{
		json taskAsJson = tasksAsJson.at(i);
		std::string title = taskAsJson.at("title");
		std::string dueDate = taskAsJson.at("dueDate");
		Task::Priority priority = taskAsJson.at("priority") == 1 ? Task::LOW : taskAsJson.at("priority") == 2 ? Task::MEDIUM : Task::HIGH;
		Task::Status status = taskAsJson.at("status") == 1 ? Task::INCOMPLETE : Task::COMPLETE;
		Task task(title, dueDate, priority, status);
		addTask(task);
	}
	tasks.close();
}
