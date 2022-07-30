#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

#include<bits/stdc++.h>
using namespace std;

class Date {
  public:
    int year;
    int month;
    int day;
    Date(int _day, int _month, int _year);
    Date();
    Date(string date);
    string toString();
    bool operator == (const Date &date);
    bool operator != (const Date &date);
    bool operator > (const Date &date);
    bool operator >= (const Date &date);
    bool operator < (const Date &date);
    bool operator <= (const Date &date);

};


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

Date::Date(string date) {
    string sub;
    int nums[3];
    int i = 0;
    while(sub != date){
      sub = date.substr(0, date.find_first_of("-"));
      date = date.substr(date.find_first_of("-") + 1);
      nums[i] = stoi(sub);
      i++;
    }
    day = nums[0];
    month = nums[1];
    year = nums[2];
}

string Date::toString() {
    return to_string(day) + "-" + to_string(month) + "-" + to_string(year);
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

#endif
