//Checks the functionality of vm_fault.

#include <iostream>
#include "vm_app.h"

using namespace std;


int main()
{
    char *p;
    char *d;
    char *e;
    char *f;
    char *r;

    f = (char *) vm_extend();
    d = (char *) vm_extend();
    e = (char *) vm_extend();
    p = (char *) vm_extend();
    r = (char *) vm_extend();


    for(int i = 0; i < 4; i++){

    vm_syslog(r, 2);

    p[3] = 'l';

    d[1] = 'l';

    f[0] = 'o';

    e[2] = '!';

    vm_syslog(p, 3);

    vm_syslog(d, -2);

    vm_syslog(f, 5);

    vm_syslog(e, 1);

    }
}

