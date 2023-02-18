#include "Main.h"
#include "Common.h"

#include "Executer.h"

#ifdef TEST
int testableMain(void)
#else
int main(void)
#endif
{
    Executer_init();

    while (Executer_exec() == STATUS_OK)
    {
        /**
         * Run the application in the Executer_exec()
         */
    }
}
