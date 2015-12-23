//Checks that the pager can handle an attempt to read before a write.

#include <iostream>
#include "vm_app.h"

using namespace std;

int main()
{
    char *j;
    j = (char *) vm_extend();

    vm_syslog(j, 1);

    j[0] = 'm';

    vm_syslog(j, 1);

}

