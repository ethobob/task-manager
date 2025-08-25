#include "date.h"

// -------------------
//    Constructors
// -------------------

Date::Date(const int day, const int month, const int year)
{
	if (day < 0 || day > 31 || month < 0 || month > 12 || year < 1000 || year > 9999)
		throw std::out_of_range("Invalid Date");
	
	m_day = day;
	m_month = month;
	m_year = year;
}

// -------------------
//       Getters
// -------------------

int Date::getDay()const
{
	return m_day;
}

int Date::getMonth()const
{
	return m_month;
}

int Date::getYear()const
{
	return m_year;
}

// -------------------
//       Setters
// -------------------

void Date::setDay(const int day)
{
	m_day = day;
}

void Date::setMonth(const int month)
{
	m_month = month;
}

void Date::setYear(const int year)
{
	m_year = year;
}

// -------------------
//      Operators
// -------------------

bool Date::operator<(const Date& other)
{
	if (m_year != other.m_year)
		return m_year < other.m_year;
	else if (m_month != other.m_month)
		return m_month < other.m_month;
	else
		return m_day < other.m_day;
}