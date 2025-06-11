#include "account.h"
#include <stdexcept>
#include <string>
using namespace std;
class AccountException:public runtime_error
{
    public:
        AccountException(Account *a,string msg);
        //初始化报错信息字符串，出错的Account指针。
        void getID();
        //获取用户ID;
    private:
        Account *a;
};