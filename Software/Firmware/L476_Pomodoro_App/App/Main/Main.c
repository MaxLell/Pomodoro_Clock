#include "Main.h"
#include "Common.h"

#ifdef TEST
int TestableMain(void)
#else
int main(void)
#endif
{
    printf("huhu\n");
    while (TRUE)
    {
        /* Do nuthin */
    }
}
