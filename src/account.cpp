#include<iostream>
using namespace std;
#include<string>
#include "AccountException.h"
double double_45(double a)      //四舍五入
{
    return ((int)(a*100+0.5))/100.;
}
vector <AccountRecord> Account:: recordMap;
Accumulator::Accumulator(Date date)
    :lastDate(date.year,date.month,date.day),value(0),sum(0)
    {}

Account::Account(Date date,string id)
    :date(date),id(id),balance(0)
    {}
void Account::show()
    {
        cout<<id<<"\t"<<"Balance: "<<balance;
    }
double Account::getBalance()
    {
        return balance;
    }
double Account::total=0;
double Account::getTotal()
    {
        return total;
    }
void Account::getID()
{
    cout<<id<<"\n";
}
void Account::record(Date date,Account* account,double amount,double balance,string desc="")
{
    AccountRecord a(date,account,amount,balance,desc);
    recordMap.push_back(a);
}
void Account::query(Date date1,Date date2)
{
    int total_balance = 0;
    for(int i=0;i<recordMap.size();i++)
        if(!(recordMap[i].date<date1)&&recordMap[i].date<date2)
            {
                recordMap[i].date.show();
                cout<<"#"<<recordMap[i].account->id<<"\t"<<recordMap[i].amount
                    <<"\t"<<recordMap[i].balance<<endl;
                    total_balance += recordMap[i].amount;
            }
            cout<<"从"<<date1.year<<"\\"<<date1.month<<"\\"<<date1.day<<"\\到"
                <<date2.year<<"\\"<<date2.month<<"\\"<<date2.day<<"\t的收入为：\n"
                <<total_balance<<endl;
}
void Account::search_high_low(Date date1,Date date2)
{
    int size = recordMap.size();
    vector <AccountRecord> record ;
    for(int i=0;i<size;i++)
        if(!(recordMap[i].date<date1)&&recordMap[i].date<date2)
            {
                record.push_back(recordMap[i]);
            }
    int max_index = 0;
    while(record.size()!=0)
    {
        for(int i=0;i<record.size();i++)
        {
            if(record[max_index].amount<record[i].amount)
            max_index = i;
        }
        record[max_index].date.show();
                cout<<"#"<<record[max_index].account->id<<"\t"<<record[max_index].amount
                    <<"\t"<<record[max_index].balance<<endl;
        record.erase(record.begin()+max_index);
        max_index = 0;
    }
    

    return;
}
SavingsAccount::SavingsAccount(Date date,string id,double rate)
    :Account(date,id),accumulation(0),acc(date)
    {
        //Date_copy(acc.lastDate,date);
        if(rate>1)
        throw AccountException(this,"利率过大");
        date.show();
        cout<<"#"<<id<<" created"<<endl;
    }
void SavingsAccount::deposit(Date date0,double money,string a)
{
    accumulation += balance*(Date_down(date0,acc.lastDate));
    balance+=money;
    total+=money;
    record(date0,this,money,balance,a);
    Date_copy(acc.lastDate,date0);
    acc.lastDate.show();
    cout<<"#"<<id<<"\t"<<money<<"\t"<<balance<<"\t"<<a<<endl;
}
void SavingsAccount::withdraw(Date date_new,double money,string a)
{
    if(money>balance)
    throw AccountException(this,"超额取款");
    accumulation += balance*(Date_down(date_new,acc.lastDate));
    balance-=money;
    total -= money;
    record(date_new,this,-money,balance,a);
    Date_copy(acc.lastDate,date_new);
    acc.lastDate.show();
    cout<<"#"<<id<<"\t-"<<money<<"\t"<<balance<<"\t"<<a<<endl;
}
void SavingsAccount::settle(Date lastDate_NEW)
{
    if(balance==0)
    return;
    if(lastDate_NEW.month!=1)
    return;
    accumulation +=balance*(Date_down(lastDate_NEW,acc.lastDate));  //Date_down（Date,Date),返回lastDate_NEW和acc.lastDate相差的天数
    double a = 0;
    if(year_type(acc.lastDate.year))//year_type用于判断是否为闰年，是闰年返回1
        a  = accumulation*0.015/366;
    else
        a  = accumulation*0.015/365;
    balance+=a;
    total +=a;
    record(lastDate_NEW,this,a,balance);
    double amount =((int) (a*100+0.5))/100.;
    Date_copy(acc.lastDate,lastDate_NEW);    //Date_copy用于将第二个参量的日期传给第一个参量，完成日期更新
    acc.lastDate.show();
    cout<<"#"<<id<<"\t"<<amount<<"\t"<<balance<<"\tinterest"<<endl;
}

SavingsAccount:: ~SavingsAccount()
{}




CreditAccount:: CreditAccount(Date date,string id,double credit,double rate,double fee)
    :Account(date,id),credit(credit),rate(rate),fee(fee),acc(date)
    {
        if(rate>1)
        throw AccountException(this,"利率过大");
        //Date_copy()
        date.show();
        cout<<"#"<<id<<" created"<<endl;
    }
void CreditAccount::deposit(Date date0,double money,string a)
    {
            balance+=money;
            total+=money;
            record(date0,this,money,balance,a);
            acc.sum += acc.value*Date_down(date0,acc.lastDate);
            if(balance<0)
            acc.value = balance*rate;
            else
            acc.value = 0;
            Date_copy(acc.lastDate,date0);
            acc.lastDate.show();
            cout<<"#"<<id<<"\t"<<money<<"\t"<<balance<<"\t"<<a<<endl;
    }
void CreditAccount::settle(Date date0)
    {
        acc.sum += acc.value*Date_down(date0,acc.lastDate);
        if(acc.sum<0)
        {
            balance += acc.sum;
            total+= acc.sum;
            record(date0,this,acc.sum,balance);
            double x = acc.sum;
            acc.sum=0;
            Date_copy(acc.lastDate,date0);
            acc.lastDate.show();
            cout<<"#"<<id<<"\t"<<double_45(x)<<"\t"<<balance<<"\t"<<"interest"<<endl;
            acc.value = balance*rate;
        }
        if(date0.year>date.year)
        {
            double x = 50*(date0.year-date.year);
            balance-= x;
            total -= x;
            record(date0,this,x,balance);
            Date_copy(acc.lastDate,date0);
            acc.lastDate.show();
            acc.value= balance*rate;
            cout<<"#"<<id<<"\t-"<<x<<"\t"<<balance<<"\t"<<"annual fee"<<endl;
        }
    }
void CreditAccount::withdraw(Date date0,double money,string a)
    {
        if(balance - money<-credit)
        throw AccountException(this,"取款之后，余额小于信用卡额度");
        if(balance>=money)
            {
                balance -= money;
                record(date0,this,-money,balance);
            }
        else
            {
                acc.sum += acc.value*Date_down(date0,acc.lastDate);
                balance -= money;
                //Account* account = this;
                if(this == nullptr)
                    cout<<"error";
                record(date0,this,-money,balance);
                acc.value = balance*rate;
            }
       total-=money;
        Date_copy(acc.lastDate,date0);
        acc.lastDate.show();
        cout<<"#"<<id<<"\t-"<<money<<"\t"<<balance<<"\t"<<a<<endl;
    }
void CreditAccount::show()
{
    double x = credit+balance;
    cout<<id<<"\t"<<"Balance: "<<balance<<"\t"<<"Available credit:"<<x;
}

