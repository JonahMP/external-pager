//Checks for correct functionality of vm_fault.

#include <iostream>
#include "vm_app.h"

using namespace std;

int main()
{

    char *q;
    q = (char *) vm_extend();

    char *w;
    w = (char *) vm_extend();

    char *r;
    r = (char *) vm_extend();

    char *t;
    t = (char *) vm_extend();

    char *e;
    e = (char *) vm_extend();

    char *y;
    y = (char *) vm_extend();

    char *u;
    u = (char *) vm_extend();

    char *i;
    i = (char *) vm_extend();

    char *o;
    o = (char *) vm_extend();

    char *p;
    p = (char *) vm_extend();

    q[0] = 'm';
    w[0] = 'm';
    e[0] = 'm';
    r[0] = 'm';
    t[0] = 'm';
    y[0] = 'm';
    u[0] = 'm';
    i[0] = 'm';
    o[0] = 'm';
    p[0] = 'm';

    vm_syslog(q, 1);
    vm_syslog(w, 1);
    vm_syslog(e, 1);
    vm_syslog(r, 1);
    vm_syslog(t, 1);
    vm_syslog(y, 1);
    vm_syslog(u, 1);
    vm_syslog(i, 1);
    vm_syslog(o, 1);
    vm_syslog(p, 1);

}

