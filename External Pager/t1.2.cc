//  Checks vm_syslog when the lengths are unusual.

#include <iostream>
#include "vm_app.h"

using namespace std;

int main()
{
    
    //When the message p does not have anything written in it and the length passed > 0
    char *p;
    
    p = (char*) vm_extend();
    
    vm_syslog(p,10);
    
    cerr<< "passed first test" <<endl<<endl<<endl;
    
    //When the message p is passed and the length passed = 0
    
    char *t;
    
    t = (char*) vm_extend();
    
    t[0] = 'h';
    t[1] = 'e';
    t[2] = 'l';
    t[3] = 'l';
    t[4] = 'o';
    vm_syslog(p,0);
    
    cerr<< "passed second test" <<endl<<endl<<endl;

    
}

