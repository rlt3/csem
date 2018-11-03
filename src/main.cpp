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
    init_IR();

    enterblock();
    initlex();
    enterblock();
    if (yyparse())
        yyerror("syntax error");

    emit_IR();

    /*
     * TODO:
     *  - Chain blocks together into an AST.
     *  - Use value of some variable in CreateRet for functions.
     */

	exit(0);
}
