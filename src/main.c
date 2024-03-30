#include "ligen.h"

int main( int argc, const char* argv[] )
{
    // Map:
    // 0 = Command
    // 1 = Command Line Arg
    // 2 = Command Line Arg
    // ...

    if (argc >= 2)
    {
        gen_headers( argv[1], argv[2] );
    }
    else
    {
        LIPRNT(KRED, "%s\n", "Expected 2 Arguments, got None");
        printf("%s", KNRM);
        printf("%s\n", __LIGEN_USAGE__);
    }
}