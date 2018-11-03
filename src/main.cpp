#include <iostream>
#include <cstring>

extern "C" {
    #include "cc.h"
    #include "scan.h"
    #include "semutil.h"
    #include "sem.h"
    #include "sym.h"
}

extern void yyerror (const char *msg);
extern int yyparse();

/* 
 * main - read a program, and parse it
 */
int
main (int argc, char **argv)
{
    enterblock();
    initlex();
    enterblock();
    if (yyparse())
        yyerror("syntax error");
    emit_ir();

    /*
     * NEXT STEPS:
     *  - COMPILE 'old' CODE WITH GCC and LINK .o FILES using G++
     *  - Add arbitrary function definitions from fname/fhead/ftail to IR Builder
     */

	exit(0);
}
