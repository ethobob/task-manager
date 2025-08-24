#include "task.h"

int Task::nextID = 100;

// -------------------
//    Constructors
// -------------------

Task::Task()
	: m_id(nextID++), m_title("Unknown"), m_dueDate("Unknown"), m_priority(LOW), m_status(INCOMPLETE)
{ }

Task::Task(const std::string& title, const std::string& dueDate, Priority priority, Status status)
	: m_id(nextID++), m_title(title), m_dueDate(dueDate), m_priority(priority), m_status(status)
{ }

// -------------------
//       Getters
// -------------------

int Task::getID()const
{
	return m_id;
}

const std::string& Task::getTitle()const
{
	return m_title;
}

const std::string& Task::getDueDate()const
{
	return m_dueDate;
}

Task::Priority Task::getPriority()const
{
	return m_priority;
}

Task::Status Task::getStatus()const
{
	return m_status;
}


// -------------------
//       Setters
// -------------------

void Task::setID(int id)
{
	m_id = id;
}

void Task::setTitle(const std::string& title)
{
	m_title = title;
}

void Task::setDueDate(const std::string& dueDate)
{
	m_dueDate = dueDate;
}

void Task::setPriority(Priority priority)
{
	m_priority = priority;
}

void Task::setStatus(Status status)
{
	m_status = status;
}

// -------------------
//      Functions
// -------------------

const std::string Task::priorityAsString(Priority priority)const
{
	switch (priority)
	{
		case Priority::LOW: return "Low";
		case Priority::MEDIUM: return "Medium";
		case Priority::HIGH: return "High";
		default: return "Unknown";
	}
}

const std::string Task::statusAsString(Status status)const
{
	switch (status)
	{
		case Status::INCOMPLETE: return "Incomplete";
		case Status::COMPLETE: return "Complete";
		default: return "Unknown";
	}
}

void Task::printTask()const
{
	fmt::print(fg(m_status == Status::COMPLETE ? COLOR_GREEN : COLOR_INCOMPLETE_RED) | fmt::emphasis::bold,
		"----------------------{0}{1}{2}{3}{4}{5}{6}{7}{8}{9}{10}",
		"\nID: ", m_id,
		"\nTask: ", m_title,
		"\nDue: ", m_dueDate,
		"\nPriority: ", priorityAsString(m_priority),
		"\nStatus: ", statusAsString(m_status),
		"\n----------------------");
}
