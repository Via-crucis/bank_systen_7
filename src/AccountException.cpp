#include "AccountException.h"
#include <string>
#include <iostream>
using namespace std;
AccountException::AccountException(Account *a,string msg)
    :a(a),runtime_error(msg)
    {

    }

void AccountException::getID()
{
    a->getID();
    //a是Account*，getID可以输出所指ID，即做到了发生异常时输出账户id。
}