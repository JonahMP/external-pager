//Checks the functionality of vm_fault.

#include <iostream>
#include "vm_app.h"

using namespace std;

int main()
{
    char *j;
    j = (char *) vm_extend();

    j[0] = 'm';

    char *h;
    h = (char *) vm_extend();

    h[0] = 'm';

    char *k;
    k = (char *) vm_extend();

    k[0] = 'm';

    vm_syslog(j, 1);

    char *l;
    l = (char *) vm_extend();

    l[0] = 'm';

    vm_syslog(j, 1);

    h[0] = 'a';

    vm_syslog(k, 1);

    char *q;
    q = (char *) vm_extend();

    l[0] = 'a';

    vm_syslog(h, 1);

    q[0] = 'm';

    vm_syslog(q, 1);

    char *w;
    w = (char *) vm_extend();

    vm_syslog(q, 1);

    q[0] = 'a';

    vm_syslog(q, 1);

    w[0] = 'm';

    vm_syslog(q, 1);

    vm_syslog(l, 1);

    j[0] = 'a';

    vm_syslog(w, 1);

    char *r;
    r = (char *) vm_extend();

    vm_syslog(r, 1);

    r[0] = 'm';

    vm_syslog(r, 1);

    vm_syslog(q, 1);

}

