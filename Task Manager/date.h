#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <regex>

class Date
{

private:
	int m_month;
	int m_day;
	int m_year;

public:

	static const std::regex DATE_REGEX;

	// constructors
	Date();
	Date(const std::string& dateAsString);
	Date(const int day, const int month, const int year);

	// getters
	int getDay()const;
	int getMonth()const;
	int getYear()const;

	// setters
	void setDay(const int day);
	void setMonth(const int month);
	void setYear(const int year);

	// functions
	std::string toString()const;

	// operators
	bool operator<(const Date& other)const;

};

#endif
