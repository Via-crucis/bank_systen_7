//step5.cpp

#include "usr.h"

#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

Usr::Usr(const char* name)
        :date(2008, 11, 1),infile(name)
        {
             file_name = new char [strlen(name)+1];
             strcpy(file_name,name);
            if(infile.fail())
            {
                ofstream create_file(name);
                create_file.close();
            }
        }
void Usr::STARTUP()
{
    cout << "(a)add account (d)deposit (w)withdraw (s)show (c)change day (n)next month (q)query (e)exit" << endl;
}
void Usr::END_DELETE()
{
    //for_each(accounts.begin(), accounts.end(), deleter());
}
void Usr::MAIN_LOOP()
{
    
        do {
      try
    {     

//显示日期和总金额



    getline(infile,input);
    if(input=="")
        {
            read_over=1; 
        }
    if(read_over == 1)
        {
            for(int i=0;i<accounts.size();i++)
            {
                if(accounts[i]->balance<0)
                {
                    cout<<"警告，你的账户"<<accounts[i]->id<<"还有欠款\t"<<"欠款金额为："<<accounts[i]->balance<<endl;
                }
            }
            date.show();
            cout << "Total: " << Account::getTotal() << "\tcommand> ";
            getline(cin,input);
            if(input =="")
            getline(cin,input);
        }
    else
    {
        date.show();
        cout << "Total: " << Account::getTotal() << "\tcommand> ";
        cout<<"\t"<<input<<endl;
    }
    istringstream iss(input);
char type;

int index, day;

double amount, credit, rate, fee;

string id, desc;

Account* account;

Date date1(2008,10,1), date2(2008,10,1);


iss >> cmd;
string input1,input2;
T1:switch (cmd) {

    case 'a'://增加账户
            iss >> type >> id;
        if (type == 's') 
        {      //s为SavingsAccount;
            iss >> rate;
            account = new SavingsAccount(date, id, rate);
        }
        else
        {
            iss >> credit >> rate >> fee;
            account = new CreditAccount(date, id, credit, rate, fee);
        }
        accounts.push_back(account);
        break;

    case 'd'://存入现金
        iss >> index >> amount;
        getline(iss, desc);
        accounts[index]->deposit(date, amount, desc);
        break;

    case 'w'://取出现金
        iss >> index >> amount;
        getline(iss, desc);
        accounts[index]->withdraw(date, amount, desc);
        break;

    case 's'://查询各账户信息
        for (size_t i = 0; i < accounts.size(); i++)
        {
            cout << "[" << i << "] ";
            accounts[i]->show();
            cout << endl;
        }
        break;

    case 'c'://改变日期
        iss >> day;
        if (day < date.getDay())
             cout << "You cannot specify a previous day";
            else if (day > date.getMaxDay())
            cout << "Invalid day";
        else
            date = Date(date.getYear(), date.getMonth(), day);
        break;

    case 'n'://进入下个月
        if (date.getMonth() == 12)
            date = Date(date.getYear() + 1, 1, 1);
        else
            date = Date(date.getYear(), date.getMonth() + 1, 1);
        for (vector<Account*>::iterator iter = accounts.begin(); iter != accounts.end(); ++iter)
            (*iter)->settle(date);
        break;
    case 'h':
        iss >> input1 >>input2;
        date1 = Date::read(input1);
        date2 = Date::read(input2);
        Account:: search_high_low(date1,date2);
        break;
    case 'q'://查询一段时间内的账目
        iss >> input1 >>input2;
        date1 = Date::read(input1);
        date2 = Date::read(input2);
        Account::query(date1, date2);
        break;
    defualt:
        cout<<"非法指令，请重试\n";
        goto T1;
}
    if(read_over == 1)
    {    
        ofstream outfile(file_name,ios_base::app); 
        if(input!="e")
        outfile<<input<<endl;
        outfile.close();
    }
}   
    catch(AccountException& e)
    {
        cerr<<"你进行了一些非法操作,账户ID:"<<endl;;
        e.getID();
        cerr<<"具体的操作为:\n"<<e.what()<<endl;
    }
    catch(const runtime_error& e)
    {
        cerr<<"你进行了一些非法操作："<<e.what()<<endl;
        continue;
    }
} while (cmd != 'e');
}
int Usr::main() {
STARTUP();
MAIN_LOOP();
END_DELETE();
return 0;
}
