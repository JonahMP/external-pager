//This extends 6 char arrays and then everything causes a fault

#include <iostream>
#include "vm_app.h"

using namespace std;

int main()
{
    char *p;
    char *d;
    char *e;
    char *f;
    char *z;
    char *q;

    f = (char *) vm_extend();
    d = (char *) vm_extend();
    e = (char *) vm_extend();
    p = (char *) vm_extend();
    z = (char *) vm_extend();
    q = (char *) vm_extend();

    f[0] = 'h';
    d[1] = 'e';
    vm_syslog(q, 1);

    vm_syslog(z, 1);

    e[2] = 'l';
    vm_syslog(p, 1);

    z[4] = 'l';
    vm_syslog(d, 1);

    q[5] = 'o';

    p[3] = '!';
    vm_syslog(f, 1);

    vm_syslog(e, 1);

}

