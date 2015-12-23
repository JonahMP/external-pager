//Checks for correct functionality of vm_fault.

#include <iostream>
#include "vm_app.h"

using namespace std;

int main()
{
    char *p;
    p = (char *) vm_extend();
    p[0] = 'a';

    vm_syslog(p, 1);

    char *j;
    j = (char *) vm_extend();
    j[0] = 'b';

    vm_syslog(j, 1);

    char *g;
    g = (char *) vm_extend();
    g[0] = 'c';

    vm_syslog(g, 1);

    char *h;
    h = (char *) vm_extend();
    h[0] = 'd';

    vm_syslog(h, 1);

    char *k;
    k = (char *) vm_extend();
    k[0] = 'e';

    vm_syslog(k, 1);

    vm_syslog(p, 1);

    vm_syslog(g, 1);

}

