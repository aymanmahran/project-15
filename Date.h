#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

#include<bits/stdc++.h>

class Date {
  public:
    int year;
    int month;
    int day;
    Date(int _day, int _month, int _year);
    Date();
    bool operator == (const Date &date);
    bool operator != (const Date &date);
    bool operator > (const Date &date);
    bool operator >= (const Date &date);
    bool operator < (const Date &date);
    bool operator <= (const Date &date);

};

#endif
