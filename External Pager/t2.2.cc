//Checks for correct functionality (correct eviction, assigning of bits, etc.) of the fault function.

#include <iostream>
#include "vm_app.h"

using namespace std;

int main()
{
    char *j;
    j = (char *) vm_extend();
    char *k;
    k = (char *) vm_extend();
    char *l;
    l = (char *) vm_extend();
    char *o;
    o = (char *) vm_extend();
    char *y;
    y = (char *) vm_extend();
    char *q;
    q = (char *) vm_extend();
    char *w;
    w = (char *) vm_extend();

    j[0] = 'm';
    j[1] = 'm';
    j[2] = 'm';

    vm_syslog(j, 3);

    k[0] = 'a';
    k[1] = 'a';
    k[2] = 'a';

    vm_syslog(j, 3);

    vm_syslog(k, 3);

    l[0] = 'p';
    l[1] = 'p';
    l[2] = 'p';

    vm_syslog(k, 3);

    o[0] = 'm';
    o[1] = 'm';
    o[2] = 'm';

    vm_syslog(j, 3);

    vm_syslog(l, 3);

    y[0] = 'm';
    y[1] = 'm';
    y[2] = 'm';

    q[0] = 'm';
    q[1] = 'm';
    q[2] = 'm';

    w[0] = 'm';
    w[1] = 'm';
    w[2] = 'm';

    vm_syslog(k, 3);

    vm_syslog(l, 3);

    vm_syslog(y, 3);

    vm_syslog(q, 3);

    vm_syslog(w, 3);

}

