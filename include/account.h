#include "date.h"
#include <string>
#include <vector>
using namespace std;
class Accumulator
{
    public:
        Accumulator(Date date);                      
        Date lastDate;
        double value;
        double sum;
};
class AccountRecord;



class Account
{
    public:
        Account(Date date, string id);       //初始化id
        double getBalance();                 //获取余额
        virtual void show();                 //展示信息
        virtual void deposit(Date date,double money,string) = 0;    //存款，输入为date：取款日期，money：取款金额,以及string类的取款原因。
        virtual void withdraw(Date date,double money,string) = 0;   //取款  类似存款
        virtual void settle(Date date)= 0;                          //结算  输入结算日期
        Date date;                                                  //最新操作的更新时间
        string id;                                                  //id
        double balance;                                              //余额 
        static double total;                                         //银行金库总额                 
        static double getTotal();                                   //获取金库总额
        static void record(Date date,Account* account,double amount,double balance,string desc);//记录操作
        static vector <AccountRecord> recordMap;                    //操作记录   
        static void query(Date date1,Date date2);                   //查询date1到date2之间的操作记录（date1<date2）
        void getID();
        static void search_high_low(Date date1,Date date2);
};



class AccountRecord
{
    public:
        AccountRecord(Date date,Account *account,double amount,double balance,string desc)
            :date(date),account(account),amount(amount),balance(balance),desc(desc)
            {}
        Date date;
        const Account *account;
        double amount;
        double balance;
        string desc;
};




class SavingsAccount:public Account
{
    public:
        SavingsAccount(Date date,string id,double rate);
        void deposit(Date date,double money,string);    //存款
        void withdraw(Date date,double money,string);   //取款
        void settle(Date lastDate_NEW);                 //结算利息                                  
        ~SavingsAccount();
    private:
        double rate;                                    //年利率
        double accumulation;                            //利息
        Accumulator acc;
};
class CreditAccount:public Account
{
    public:
        CreditAccount(Date date,string id,double credit,double rate,double fee);
       void deposit(Date date0,double money,string);
       void withdraw(Date date,double money,string);   //取款
       void settle(Date lastDate_NEW);
       void show();
    private:
        double fee;        //年费 
        double rate;        //年利率
        double credit;      //信用卡额度。
        Accumulator acc;

};

