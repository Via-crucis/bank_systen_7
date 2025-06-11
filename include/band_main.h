#include "usr.h"
struct usr_ifm
{
    int usr_index;              //用户的真实索引
    string passwd;              //密码
    string id;                  //用户名
    string file_name;
};
vector<usr_ifm> ifm;            //用户信息数组
vector <Usr> usr;               //用户的主函数
void regist();
void STARTUP();
void login();