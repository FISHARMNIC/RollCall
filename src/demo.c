#include <stdlib.h>
#include <stdio.h>

#include "lib/rollcall.h"

void test() 
{
    rc_create(char*, allocation1, 10, FALSE);
    rc_create(int*,  allocation2, 10, FALSE);
}

int main()
{
    /*
     * "test" doesn't run the collector function
     * However, since "allocation1" and "allocation2" exist on the stack, at the end of their function,
       their data (which is not really theirs anymove) will be overriden soon enough. This will result in
       allocations being cleaned up regardless.
    */

    test();
    test();

    /* 
     * Normally, the collector should not be run in the middle of a function, but this example
       serves to show that if a function doesn't run the collector, the data still hasn't fully leaked yet
     * Depending on the computer, less than four discards may appear
        This is because the old stack variables inside of the "test" function may not have been overwritten yet
    */
    rc_collect();

    rc_create(char*, allocation1, 100, FALSE);
    rc_create(int*,  allocation2, 10, TRUE);

    /* 
     * Here, the pointers are being focefully altered in order to trigger the garbage collector 
    */
    allocation1 = (char*) 00;
    /*
     * Depending on the compiler, more than one discard may appear
     * This is because running the "test" function twice caused 4 leaks
    */
    rc_collect();

    // Enabling this line will trigger an error since allocation2 is restricted
    //rc_requestOwnership(allocation1, allocation2, char*);

    // This can be run to just delete everything
    rc_free_all();
}