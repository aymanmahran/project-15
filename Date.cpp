#include "Date.h"

Date::Date(int _day, int _month, int _year){
  day = _day;
  month = _month;
  year = _year;
}

Date::Date(){
  day = 0;
  month = 0;
  year = 0;
}

bool Date::operator == (const Date &date) {
  if (year == date.year &&
      month == date.month &&
      day == date.day)
      return true;
  else
    return false;
}

bool Date::operator != (const Date &date) {
  if (year != date.year ||
      month != date.month ||
      day != date.day)
      return true;
  else
    return false;
}

bool Date::operator < (const Date &date) {
  if (year < date.year)
    return true;
  else if (year == date.year &&
            month < date.month)
    return true;
  else if (year == date.year &&
            month == date.month &&
            day < date.day)
    return true;
  else
    return false;
}

bool Date::operator <= (const Date &date) {
  if (year < date.year)
    return true;
  else if (year == date.year &&
            month < date.month)
    return true;
  else if (year == date.year &&
            month == date.month &&
            day <= date.day)
    return true;
  else
    return false;
}

bool Date::operator > (const Date &date) {
  if (year > date.year)
    return true;
  else if (year == date.year &&
            month > date.month)
    return true;
  else if (year == date.year &&
            month == date.month &&
            day > date.day)
    return true;
  else
    return false;
}

bool Date::operator >= (const Date &date) {
  if (year > date.year)
    return true;
  else if (year == date.year &&
            month > date.month)
    return true;
  else if (year == date.year &&
            month == date.month &&
            day >= date.day)
    return true;
  else
    return false;
}
