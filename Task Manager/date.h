#ifndef DATE_H
#define DATE_H

#include <ostream>
#include <stdexcept>

class Date
{

private:
	int m_day;
	int m_month;
	int m_year;

public:

	// constructors
	Date(const int day, const int month, const int year);

	// getters
	int getDay()const;
	int getMonth()const;
	int getYear()const;

	// setters
	void setDay(const int day);
	void setMonth(const int month);
	void setYear(const int year);

	// operators
	bool operator<(const Date& other);
	friend std::ostream& operator<<(std::ostream& os, const Date& date);

};

std::ostream& operator<<(std::ostream& os, const Date& date)
{
	os  << (date.m_month < 10 ? "0" : "") << date.m_month
		<< (date.m_day < 10 ? "0" : "") << date.m_day
		<< date.m_year;
	return os;
}

#endif
