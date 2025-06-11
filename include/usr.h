#include "AccountException.h"

#include <iostream>

#include <vector>

#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

class Usr
{
    public:
        Usr(const char*);
struct deleter
{
    template <class T> void operator () (T* p) { delete p; }
};
Date date;
vector<Account *> accounts;//创建账户数组，元素个数为0
char cmd;
ifstream infile;
string input;
bool read_over = 0;
char* file_name;
void STARTUP();
void END_DELETE();
void MAIN_LOOP();
int main();
};