//Checks that the pager will return -1 when attempting to extend beyond the arena size.

#include <iostream>
#include "vm_app.h"

using namespace std;

int main()
{
    char *j;

    for (int i = 0; i < 1028; i ++) {
        j = (char *) vm_extend();
    }

    j[0] = 'm';
    j[1] = 'm';
    j[2] = 'm';

    vm_syslog(j, 3 * VM_PAGESIZE);

}

