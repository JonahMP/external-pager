//Checks to see that the pager can handle an attempt to write to an address beyong the maximum virtual address.

#include <iostream>
#include "vm_app.h"

using namespace std;

int main()
{

    char *k;
    k = (char *) vm_extend();

    k[0] = 'a';
    k[1] = 'a';
    k[2] = 'a';
    k[8195] = 'a';

    vm_syslog(k, 4);

}

