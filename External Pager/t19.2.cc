//Checks that the pager can handle a read at an invalid index.

#include <iostream>
#include "vm_app.h"

using namespace std;

int main()
{
    char *j;
    j = (char *) vm_extend();

    j[0] = 'm';
    j[1] = 'm';
    j[2] = 'm';

    vm_syslog((void*) 600000000000, 3);

}

