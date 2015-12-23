//Checks to correct functionality of vm_fault.

#include <iostream>
#include "vm_app.h"

using namespace std;

int main()
{
    char *p;
    char *z;
    char *n;

	n = (char *) vm_extend();
    z = (char *) vm_extend();
    p = (char *) vm_extend();

/*					*/


    vm_syslog(p, -1);
    vm_syslog(z, -1);
    vm_syslog(n, -1);

    vm_syslog(p, 0);
    vm_syslog(z, 0);
    vm_syslog(n, 0);

    vm_syslog(p, 30);
    vm_syslog(z, 30);
    vm_syslog(n, 30);

/*					*/

    vm_syslog(p, -1);
    vm_syslog(z, -1);
    vm_syslog(n, -1);
    
    vm_syslog(p, 0);
    vm_syslog(z, 0);
    vm_syslog(n, 0);

    vm_syslog(p, 30);
    vm_syslog(z, 30);
    vm_syslog(n, 30);


/*					*/
    p[0] = 'h';
    vm_syslog(z, -1);
    vm_syslog(n, -1);
    vm_syslog(p, -1);
    
    z[0] = 'h';
    vm_syslog(n, 0);
    vm_syslog(p, 0);
    vm_syslog(z, 0);

    n[0] = 'h';   

    vm_syslog(p, 30);
    vm_syslog(z, 30);
    vm_syslog(n, 30);

/*					*/
	p[1] = 'e';
	vm_syslog(z, -1);
	vm_syslog(n, -1);
    vm_syslog(p, -1);

	z[1] = 'e';
    vm_syslog(n, 1);
    vm_syslog(p, 1);
    vm_syslog(z, 1);

    n[1] = 'e';
    vm_syslog(p, 30);
    vm_syslog(z, 30);
    vm_syslog(n, 30);

    
    


/*					*/

	p[2] = 'l';
	vm_syslog(z, -1);
    vm_syslog(n, -1);
    vm_syslog(p, -1);

    z[2] = 'l';
	vm_syslog(n, 2);
    vm_syslog(p, 2);
    vm_syslog(z, 2);
	
	n[2] = 'l';
    vm_syslog(p, 30);
    vm_syslog(z, 30);
    vm_syslog(n, 30);
    

/*					*/
    p[3] = 'l';
    vm_syslog(z, -1);
    vm_syslog(n, -1);
    vm_syslog(p, -1);

    z[3] = 'l';
    vm_syslog(n, 3);
    vm_syslog(p, 3);
    vm_syslog(z, 3);
    
    n[3] = 'l';
    vm_syslog(p, 30);
    vm_syslog(z, 30);
    vm_syslog(n, 30);

/*					*/

   	p[4] = 'o';
   	vm_syslog(z, -1);
   	vm_syslog(n, -1);
   	vm_syslog(p, -1);

    z[4] = 'o';                

    vm_syslog(p, 3);
    vm_syslog(z, 3);

    n[4] = 'o';
    vm_syslog(p, 20);
    vm_syslog(z, 30);
	vm_syslog(n, 20);




}

