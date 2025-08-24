#include "utils.h"

namespace utils
{

	void clearScreen()
	{
		std::cout << "\033[2J\033[H";
	}

	bool isNumber(const std::string& line)
	{
		if (line.empty()) return false;
		for (int i = 0; i < line.size(); i++)
			if (!std::isdigit(line[i]))
				return false;
		return true;
	}

}