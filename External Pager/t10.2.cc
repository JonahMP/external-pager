//Checks that the pager can read messages on more than 1 pages.

#include <iostream>
#include "vm_app.h"

using namespace std;

int main()
{
    char *j;
    j = (char *) vm_extend();

    char *k;
    k = (char *) vm_extend();

    j[0] = 'm';
    j[1] = 'm';
    j[2] = 'm';

    k[0] = 'a';
    k[1] = 'a';
    k[2] = 'a';

    vm_syslog(j, 2 * VM_PAGESIZE);

}

