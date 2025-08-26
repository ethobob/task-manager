#ifndef TASK_H
#define TASK_H

#define FMT_HEADER_ONLY
#include <fmt/base.h>
#include "colors.h"

#include <iostream>
#include <string>
#include "date.h"

class Task
{
	
public:
	enum Priority { PRIORITY_UNKNOWN = 0, LOW = 1, MEDIUM = 2, HIGH = 3 };
	enum Status { STATUS_UNKNOWN = 0, INCOMPLETE = 1, COMPLETE = 2 };

private:
	int m_id;
	std::string m_title;
	Date m_dueDate;
	Priority m_priority;
	Status m_status;

	static int nextID;

	const std::string priorityAsString(Priority priority)const;
	const std::string statusAsString(Status status)const;

public:

	// constructors
	Task();
	Task(const std::string title);
	Task(const std::string& title, const Date& dueDate, Priority priority, Status status);

	// getters
	int getID()const;
	const std::string& getTitle()const;
	const Date& getDueDate()const;
	std::string getDueDateString()const;
	Priority getPriority()const;
	Status getStatus()const;

	// setters
	void setID(int id);
	void setTitle(const std::string& title);
	void setDueDate(const Date& dueDate);
	void setPriority(Priority priority);
	void setStatus(Status status);

	// functions
	void printTask()const;

};

#endif
