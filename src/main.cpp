#include "band_main.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;



void regist()
{
        int i = ifm.size();
        usr_ifm uif;
        uif.usr_index = i;
            while(1)
                {
        
                     cout<<"输入你的id"<<endl;
                    cin>>uif.id;
                    int j=0;
                    for(;j<ifm.size();j++)
                        {
                            if(uif.id == ifm[j].id)
                            {
                                cout<<"ID与已有用户重复，重新取一个吧。";
                                break;
                            }
                        } 
                    if(j == ifm.size())
                    break;
                }
            cout<<"输入你的密码"<<endl;
            cin>>uif.passwd;
            //输入密码
            ofstream outfile("../src/register.txt",ios_base::app);
            string input = uif.id+" "+uif.passwd;
            outfile<<input<<endl;
            //记录用户ID密码。
            string file_index = to_string(ifm.size());
            string a = file_index+".txt";
            uif.file_name ="../src/data"+a;
            //cout<<uif.file_name;
            //构造文件名，data(n).txt
            ifm.push_back(uif);
            Usr u(uif.file_name.c_str());
            //用户对应用户文件名。
            usr.push_back(move(u));
}
void STARTUP()
{
    ifstream infile("../src/register.txt");       
         //读取历史文件
        string input;
        //读入的字符串
        getline(infile,input);
        while (input!="")
        {
            //读入
        //判断是否读入结束，结束即为1，初始为0；
            int i = ifm.size();
            usr_ifm uif;
            uif.usr_index = i;
            istringstream iss(input);
            iss>>uif.id>>uif.passwd;
            string file_index = to_string(ifm.size());
            string a = file_index+".txt";
            uif.file_name ="../src/data"+a;
            //cout<<uif.file_name;
        //构造文件名，data(n).txt
            ifm.push_back(uif);
            Usr u(uif.file_name.c_str());
            //用户对应用户文件名。
            usr.push_back(move(u));
            getline(infile,input);
        }
        
}
void login()
{
    string id;
    string passwd;
    while(1)
    {
        cout<<"输入ID:";
        cin>>id;
        for(int i=0;i<ifm.size();i++)
        {
            if(id == ifm[i].id)
                {
                   cout<<"输入密码:";
                    cin>>passwd;
                    if(passwd == ifm[i].passwd)
                        {
                            cout<<"登录成功"<<endl;
                            cin.ignore();
                            usr[ifm[i].usr_index].main();
                            return ;
                        }
                }
        
        }
        cout<<"输入的id有误,请重试。"<<endl;
    }
}
int main()
{
    STARTUP();//初始化用户信息
    int cmd;
    while(1)
    {
        cout<<"登录扣1,注册扣2,退出扣3"<<endl;
        cin>>cmd;
        switch(cmd)
        {
            case 1:
                login();
                break;
            case 2:
                regist();
                break;
            case 3:
                return 0;
            default:
                continue;
        }     
    }
    
}