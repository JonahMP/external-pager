//Checks for the correct functionality of vm_fault.

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


    vm_syslog(q, 1);

    vm_syslog(z, 1);

    vm_syslog(p, 1);

    vm_syslog(d, 1);

    vm_syslog(f, 1);

    vm_syslog(e, 1);

    q[5] = 'h';

    z[4] = 'e';

    p[3] = 'l';

    d[1] = 'l';

    f[0] = 'o';

    e[2] = '!';

    vm_syslog(q, 5);

    vm_syslog(z, 3);

    vm_syslog(p, 3);

    vm_syslog(d, -2);

    vm_syslog(f, 5);

    vm_syslog(e, 1);

    q[5] = 'H';

    z[4] = 'E';

    p[3] = 'L';

    vm_syslog(q, 5);
    q[5] = 'L';

    d[1] = 'L';

    f[0] = 'O';

    e[2] = '!';

     q[5] = 'h';

    z[4] = 'e';

    p[3] = 'l';

    d[1] = 'l';

    f[0] = 'o';

    e[2] = '!';

    vm_syslog(q, 5);

    vm_syslog(z, 3);

    vm_syslog(p, 3);

    vm_syslog(d, -2);

    vm_syslog(f, 5);

    vm_syslog(e, 1);

    q[5] = 'H';

    z[4] = 'E';

    p[3] = 'L';

    vm_syslog(q, 5);
    q[5] = 'L';

    d[1] = 'L';

    f[0] = 'O';

    e[2] = '!';

     q[5] = 'h';

    z[4] = 'e';

    p[3] = 'l';

    d[1] = 'l';

    f[0] = 'o';

    e[2] = '!';

    vm_syslog(q, 5);

    vm_syslog(z, 3);

    vm_syslog(p, 3);

    vm_syslog(d, -2);

    vm_syslog(f, 5);

    vm_syslog(e, 1);

    q[5] = 'H';

    z[4] = 'E';

    p[3] = 'L';

    vm_syslog(q, 5);
    q[5] = 'L';

    d[1] = 'L';

    f[0] = 'O';

    e[2] = '!';

     q[5] = 'h';

    z[4] = 'e';

    p[3] = 'l';

    d[1] = 'l';

    f[0] = 'o';

    e[2] = '!';

    char *m;

    m = (char *) vm_extend();
    vm_syslog(m, 15);
    m = (char *) vm_extend();
    m[4] = '9';
    m = (char *) vm_extend();
    m = (char *) vm_extend();
    m = (char *) vm_extend();


    vm_syslog(q, 5);

    vm_syslog(z, 3);

    vm_syslog(p, 3);

    vm_syslog(d, -2);

    vm_syslog(f, 5);

    vm_syslog(e, 1);

    q[5] = 'H';

    m[20] = '9';


    z[4] = 'E';

    m[4] = '9';

    p[3] = 'L';

    vm_syslog(q, 5);
    q[5] = 'L';

    d[1] = 'L';

    f[0] = 'O';
    vm_syslog(m, 15);

    e[2] = '!';

}

