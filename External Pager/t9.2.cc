//Checks that the pager can read messages on more than 1 pages.

#include <iostream>
#include "vm_app.h"

using namespace std;

int main()
{
    char *j;
    char *k;

    j = (char *) vm_extend();
    k = (char *) vm_extend();

    j[0] = 'a';
    j[4080] = 'a';

    k[0] = 'a';
    k[4080] = 'a';

    vm_syslog(j, 2 * VM_PAGESIZE);

}

