#include "Executer.h"

void Executer_init(void)
{
}

void Executer_execute(void)
{
}

void Executer_run(void)
{
    Executer_init();
    while (Executer_execute() == EXECUTER_OK)
    {
        /**
         * The main execution steps are run in the Executer_execute() function.
         */
    }
}