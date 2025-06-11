#include <iostream>
#include <sstream>
#include <string>
using namespace std;
#include "date.h"
Date::Date(int year1 = 2008,int month1 = 1,int day1 = 1)
    :year(year1),month(month1),day(day1)
{
    text();
}
void Date::show()
{
    cout<<year<<"-"<<month<<"-"<<day<<"\t";
}
Date Date::read(string input)
{
    istringstream iss(input);
    string year_s,month_s,day_s;
    getline(iss,year_s,'/');
    getline(iss,month_s,'/');
    getline(iss,day_s,'/');
    Date date0;
    date0.year = stoi(year_s);
    date0.month = stoi(month_s);
    date0.day = stoi(day_s);
    date0.text();
    return date0;

}
void Date_copy(Date& date,Date& date_target)
{
    date.year=date_target.year;
    date.month=date_target.month;
    date.day=date_target.day;
    date.text();
}
bool year_type(int year) 
{
    if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)) {
        return true;
    } else {
        return false;
    }
}
int month_type_day(int month,int year)
{
    if((month<8&&month%2==1)||(month>=8&&month%2==0))
    return 31;
    if(month!=2)
    return 30;
    if(year_type(year))
    return 29;
    return 28;
}
int Date_down(Date date1,Date date2)
{
    int day=0;
    if(date1.year>date2.year)
    {
        for(int i=0;i<date1.year-date2.year;i++)
        if(year_type(date2.year+i)&&date2.month<=2)
            day+=366;
        else
        if(year_type(date2.year+i+1)&&date2.month>=3)
            day+=366;
        else
            day+=365;
    }
    if(date1.month>date2.month)
    {
        for(int i=0;i<date1.month-date2.month;i++)
        {
            day+=month_type_day(date2.month+i,date2.year);
        }
    }
    if(date1.month<date2.month)
    {
        for(int i=0;i<date2.month-date1.month;i++)
        {
            day-=month_type_day(date1.month+i,date1.year);
        }
    }
    day+=date1.day-date2.day;
    return day;
}
int month_down(Date date1,Date date2)
{
    if(date1.year<date2.year)
    month_down(date2,date1);
    int x;
    x = 12*(date1.year - date2.year);
    if(date1.month<date2.month)
        {
            date2.month-=12;
            x+=date1.month-date2.month-12;
        }
    else   
        {
            x+=date1.month-date2.month;
        }
    return x;
}
int Date::getDay()
{
    return day;
}
int Date::getYear()
{
    return year;
}
int Date::getMonth()
{
    return month;
}
int Date::getMaxDay()
{
    switch(month)
    {
        case 1:return 31;
        case 2:
            if(year_type(year))
            return 29;
            return 28;
        case 3:return 31;
        case 4:return 30;
        case 5:return 31;
        case 6:return 30;
        case 7:return 31;
        case 8:return 31;
        case 9:return 30;
        case 10:return 31;
        case 11:return 30;
        case 12:return 31;
        default:return 0;
    }
}
void Date::text()
{
    switch(month)
     {
        case 1:if(day>31)
                throw runtime_error("时间不合法");
                break;
        case 2:
            if(year_type(year))
                {
                    if(day>29)
                    throw runtime_error("时间不合法");
                    break;
                }
            else
                if(day>28||day<=0)
                throw runtime_error("时间不合法");
                break;
        case 3:if(day>31||day<=0)
                throw runtime_error("时间不合法");
                break;
        case 4:if(day>30||day<=0)
                throw runtime_error("时间不合法");
                break;
        case 5:if(day>31||day<=0)
                throw runtime_error("时间不合法");
                break;
        case 6:if(day>30||day<=0)
                throw runtime_error("时间不合法");
                break;
        case 7:if(day>31||day<=0)
                throw runtime_error("时间不合法");
                break;
        case 8:if(day>31||day<=0)
                throw runtime_error("时间不合法");
                break;
        case 9:if(day>30||day<=0)
                throw runtime_error("时间不合法");
                break;
        case 10:if(day>31||day<=0)
                throw runtime_error("时间不合法");
                break;
        case 11:if(day>30||day<=0)
                throw runtime_error("时间不合法");
                break;
        case 12:if(day>31||day<=0)
                throw runtime_error("时间不合法");
                break;
        default:throw runtime_error("时间不合法");
    }
}