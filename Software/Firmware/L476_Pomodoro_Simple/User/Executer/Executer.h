#ifndef EXECUTER_H
#define EXECUTER_H

#include "Common.h"

#define EXECUTER_OK 0
#define EXECUTER_ERROR 1

status_t Executer_execute(void);
void Executer_init(void);
void Executer_run(void);

#endif // EXECUTER_H
