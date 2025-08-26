#include "date.h"

const std::regex Date::DATE_REGEX("^(0[1-9]|1[1-2])/([0-2][1-9]|3[0-1])/[0-9]{4}");

// -------------------
//    Constructors
// -------------------

Date::Date()
	: m_month(1), m_day(1), m_year(2000)
{ }

Date::Date(const std::string& dateAsString)
{
	if (!std::regex_match(dateAsString, Date::DATE_REGEX))
	{
		throw std::invalid_argument("Invalid date");
	}

	const int indexFirstSlash = dateAsString.find("/");
	const int indexLastSlash = dateAsString.rfind("/");

	m_month = stoi(dateAsString.substr(0, indexFirstSlash));
	m_day = stoi(dateAsString.substr(indexFirstSlash + 1, indexLastSlash - 3));
	m_year = stoi(dateAsString.substr(indexLastSlash + 1, dateAsString.size()));
}

Date::Date(const int month, const int day, const int year)
	: m_month(month), m_day(day), m_year(year)
{
	if (day < 0 || day > 31 || month < 0 || month > 12 || year < 1000 || year > 9999)
		throw std::invalid_argument("Invalid Date");
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
//      Functions
// -------------------

std::string Date::toString()const
{
	std::string date = (m_month < 10 ? "0" : "") + std::to_string(m_month)
			   + "/" + (m_day < 10 ? "0" : "") + std::to_string(m_day)
			   + "/" + std::to_string(m_year);
	return date;
}

// -------------------
//      Operators
// -------------------

bool Date::operator<(const Date& other)const
{
	if (m_year != other.m_year)
		return m_year < other.m_year;
	else if (m_month != other.m_month)
		return m_month < other.m_month;
	else
		return m_day < other.m_day;
}