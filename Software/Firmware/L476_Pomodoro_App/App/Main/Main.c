#include "Main.h"
#include "Common.h"
#include "Rcc.h"

#ifdef TEST
int TestableMain(void)
#else
int main(void)
#endif
{
    printf("huhu\n");

    Rcc_Init();


    while (TRUE)
    {
        /* Do nuthin */
    }
}
