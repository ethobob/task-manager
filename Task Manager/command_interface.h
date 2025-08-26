#ifndef COMMAND_INTERFACE_H
#define COMMAND_INTERFACE_H

#include "task_manager.h"
#include "utils.h"
#include <sstream>
#include <unordered_map>
#include <stdexcept>

using namespace utils;

class CommandInterface
{

private:
	TaskManager m_manager;
	std::unordered_map<std::string, std::function<void(const std::string& args)>> m_commandMap;

public:
	CommandInterface(TaskManager& manager);
	void init();
	void userAddCommand(const std::string& args);
	void userRemoveCommand(const std::string& args);
	void userEditCommand(const std::string& args);
	void userSortCommand(const std::string& args);
	void userListCommand(const std::string& args);
	void userHelpCommand()const;

};

#endif
