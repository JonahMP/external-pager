//Checks to see that the write_bit is set to 1 when the modBit is 1 after attempting to read.

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

    j[0] = 'm';
    j[1] = 'm';
    j[2] = 'm';

    k[0] = 'a';
    k[1] = 'a';
    k[2] = 'a';

    l[0] = 'p';
    l[1] = 'p';
    l[2] = 'p';

    vm_syslog(k, 3);

    k[3] = 'a';

    vm_syslog(k, 4);

}

