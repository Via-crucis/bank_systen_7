#include <string>
#include <stdexcept>
#include <iostream>
using namespace std;
class Date
{
    public:
        Date(int,int,int);             //初始化
        void show();                   //展示时间
        friend void Date_copy(Date &previous,Date &new_);   //previous = new;
        friend int Date_down(Date date1,Date date2);        //date1 - date2。日期1减日期2，返回相差的天数。
        friend int month_type_day(int month,int year);      //输入为某年某月，输出为这个月份的天数。例如：f(2,2020) = 29
        friend int month_down(Date date1,Date date2);       //输入为两个日期，返回date1和date2之间相差的月份数（date1>date2)
        static Date read(string);                           //输入为字符串，返回为日期。例：read(2008/10/1) = date_(date_.year == 2008;date_.month == 10.date_.day == 1)
        int getYear();                                      //返回this->year
        int getMonth();                                     //返回this->month
        int getDay();                                       //返回this->day
        int getMaxDay();                                    
        int year;
        int month;
        int day;
        bool operator < (const Date& date) const 
        {
                if(year<date.year)
                return 1;
                if(month<date.month)
                return 1;
                if(day<date.day)
                return 1;
                return 0;
        }
        void text();
};
bool year_type(int year);                   //判断是否为闰年
