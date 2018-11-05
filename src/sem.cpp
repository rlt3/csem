#include <stdio.h>

extern "C" {
    #include "cc.h"
    #include "scan.h"
    #include "semutil.h"
    #include "sem.h"
    #include "sym.h"
}

#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>

/*
 * These have been extern'd from semutil.c. This handles local types of 
 * variables inside blocks, how many have been declared, and other things
 * I haven't quite figured out yet.
 */
extern int formalnum;               /* number of formal arguments */
extern char formaltypes[MAXARGS];   /* types of formal arguments  */
extern int localnum;                /* number of local variables  */
extern char localtypes[MAXLOCS];    /* types of local variables   */
extern int localwidths[MAXLOCS];    /* widths of local variables  */

using namespace llvm;

static LLVMContext TheContext;
static IRBuilder<> Builder(TheContext);
static std::unique_ptr<Module> TheModule;
static std::map<std::string, Value *> NamedValues;

/*
 * backpatch - backpatch list of quadruples starting at p with k
 */
void backpatch(struct sem_rec *p, int k)
{
   fprintf(stderr, "sem: backpatch not implemented\n");
}

/*
 * bgnstmt - encountered the beginning of a statement
 */
void
bgnstmt()
{
    /* todo ? */
}

/*
 * call - procedure invocation
 */
struct sem_rec *call(const char *f, struct sem_rec *args)
{
   fprintf(stderr, "sem: call not implemented\n");
   return ((struct sem_rec *) NULL);
}

/*
 * ccand - logical and
 */
struct sem_rec *ccand(struct sem_rec *e1, int m, struct sem_rec *e2)
{
   fprintf(stderr, "sem: ccand not implemented\n");
   return ((struct sem_rec *) NULL);
}

/*
 * ccexpr - convert arithmetic expression to logical expression
 */
struct sem_rec *ccexpr(struct sem_rec *e)
{
   fprintf(stderr, "sem: ccexpr not implemented\n");
   return ((struct sem_rec *) NULL);
}

/*
 * ccnot - logical not
 */
struct sem_rec *ccnot(struct sem_rec *e)
{
   fprintf(stderr, "sem: ccnot not implemented\n");
   return ((struct sem_rec *) NULL);
}

/*
 * ccor - logical or
 */
struct sem_rec *ccor(struct sem_rec *e1, int m, struct sem_rec *e2)
{
   fprintf(stderr, "sem: ccor not implemented\n");
   return ((struct sem_rec *) NULL);
}

/*
 * con - constant reference in an expression
 */
struct sem_rec*
con (const char *x)
{
    /*
     * Use 'anything' part of record to hold our value. This is used int
     * doret to make a retval of the constant here.
     */
    struct sem_rec *R = node(currtemp(), T_INT, NULL, NULL);
    int v;
    sscanf(x, "%d", &v);
    R->anything = (void*) ConstantInt::get(Type::getInt8Ty(TheContext), v);
    return R;
}

/*
 * dobreak - break statement
 */
void dobreak()
{
   fprintf(stderr, "sem: dobreak not implemented\n");
}

/*
 * docontinue - continue statement
 */
void docontinue()
{
   fprintf(stderr, "sem: docontinue not implemented\n");
}

/*
 * dodo - do statement
 */
void dodo(int m1, int m2, struct sem_rec *e, int m3)
{
   fprintf(stderr, "sem: dodo not implemented\n");
}

/*
 * dofor - for statement
 */
void dofor(int m1, struct sem_rec *e2, int m2, struct sem_rec *n1,
           int m3, struct sem_rec *n2, int m4)
{
   fprintf(stderr, "sem: dofor not implemented\n");
}

/*
 * dogoto - goto statement
 */
void dogoto(const char *id)
{
   fprintf(stderr, "sem: dogoto not implemented\n");
}

/*
 * doif - one-arm if statement
 */
void doif(struct sem_rec *e, int m1, int m2)
{
   fprintf(stderr, "sem: doif not implemented\n");
}

/*
 * doifelse - if then else statement
 */
void doifelse(struct sem_rec *e, int m1, struct sem_rec *n,
                         int m2, int m3)
{
   fprintf(stderr, "sem: doifelse not implemented\n");
}

/*
 * doret - return statement
 */
void
doret (struct sem_rec *R)
{
    if (!R)
        Builder.CreateRetVoid();
    else
        Builder.CreateRet((Value*) R->anything);
}

/*
 * dowhile - while statement
 */
void dowhile(int m1, struct sem_rec *e, int m2, struct sem_rec *n,
             int m3)
{
   fprintf(stderr, "sem: dowhile not implemented\n");
}

/*
 * endloopscope - end the scope for a loop
 */
void endloopscope(int m)
{
   fprintf(stderr, "sem: endloopscope not implemented\n");
}

/*
 * exprs - form a list of expressions
 */
struct sem_rec *exprs(struct sem_rec *l, struct sem_rec *e)
{
   fprintf(stderr, "sem: exprs not implemented\n");
   return ((struct sem_rec *) NULL);
}

/*
 * Take a constructed function id_entry and add it to the LLVM AST.
 */
void fhead (struct id_entry *E)
{
    std::vector<Type*> args;
    Type* func_type;
    GlobalValue::LinkageTypes linkage;
	FunctionType *FT;
    Function *F;
    BasicBlock *B;

    /* handle all function arguments */
    for (int i = 0; i < formalnum; i++) {
        switch (formaltypes[i]) {
            case 'f': args.push_back(Type::getDoubleTy(TheContext)); break;
            case 'i': args.push_back(Type::getInt8Ty(TheContext)); break;
            default:  yyerror("type failure!");
        }
    }

    /* handle function return type */
    switch (E->i_type) {
        case T_INT:    func_type = Type::getInt8Ty(TheContext); break;
        case T_DOUBLE: func_type = Type::getDoubleTy(TheContext); break;
    }
	FT = FunctionType::get(func_type, makeArrayRef(args), false);

    /* need main to be entry point into program for linking */
    if (strcmp(E->i_name, "main") == 0) {
        linkage = Function::ExternalLinkage;
    } else {
        linkage = Function::InternalLinkage;
    }
	
    F = Function::Create(FT, linkage, E->i_name, TheModule.get());
    B = BasicBlock::Create(TheContext, "entry", F);
    Builder.SetInsertPoint(B);

    /* Add the ret value of the function to the builder */
    //Value *val = ConstantInt::get(Type::getInt8Ty(TheContext), 0);
    //Builder.CreateRet(val);

    //if (verifyFunction(*F, &errs())) {
    //    yyerror("IR verification failed");
    //}
}

/*
 * Create and fill up an id_entry with the correct information.
 */
struct id_entry*
fname (int type, const char *id)
{
    struct id_entry *E = lookup(id, 0);

    /* add function to hash table if it doesn't exist */
    if (!E)
        E = install(id, 0);

    /* cannot have two functions of the same name */
    if (E->i_defined)
        yyerror("cannot declare function more than once");

    E->i_type = type;
	E->i_scope = GLOBAL;
	E->i_defined = true;

    /* need to enter the block to let hash table do internal work */
    enterblock();
    /* then need to reset argument count variables */
    formalnum = 0;
    localnum = 0;

    return E;
}

/*
 * ftail - end of function body
 */
void
ftail()
{
    leaveblock();
}

/*
 * id - variable reference
 */
struct sem_rec *
id (const char *x)
{
    return node(currtemp(), T_LBL, NULL, NULL);
}

/*
 * indx - subscript
 */
struct sem_rec *indx(struct sem_rec *x, struct sem_rec *i)
{
   fprintf(stderr, "sem: indx not implemented\n");
   return ((struct sem_rec *) NULL);
}

/*
 * labeldcl - process a label declaration
 */
void labeldcl(const char *id)
{
   fprintf(stderr, "sem: labeldcl not implemented\n");
}

/*
 * m - generate label and return next temporary number
 */
int m()
{
   fprintf(stderr, "sem: m not implemented\n");
   return (0);
}

/*
 * n - generate goto and return backpatch pointer
 */
struct sem_rec *n()
{
   fprintf(stderr, "sem: n not implemented\n");
   return ((struct sem_rec *) NULL);
}

/*
 * op1 - unary operators
 */
struct sem_rec *op1(const char *op, struct sem_rec *y)
{
   fprintf(stderr, "sem: op1 not implemented\n");
   return ((struct sem_rec *) NULL);
}

/*
 * op2 - arithmetic operators
 */
struct sem_rec *op2(const char *op, struct sem_rec *x, struct sem_rec *y)
{
   fprintf(stderr, "sem: op2 not implemented\n");
   return ((struct sem_rec *) NULL);
}

/*
 * opb - bitwise operators
 */
struct sem_rec *opb(const char *op, struct sem_rec *x, struct sem_rec *y)
{
   fprintf(stderr, "sem: opb not implemented\n");
   return ((struct sem_rec *) NULL);
}

/*
 * rel - relational operators
 */
struct sem_rec *rel(const char *op, struct sem_rec *x, struct sem_rec *y)
{
   fprintf(stderr, "sem: rel not implemented\n");
   return ((struct sem_rec *) NULL);
}

/*
 * set - assignment operators
 */
struct sem_rec *
set (const char *op, struct sem_rec *x, struct sem_rec *y)
{
  /* assign the value of expression y to the lval x */
  struct sem_rec *p, *cast_y;

  if(*op!='\0' || x==NULL || y==NULL){
    fprintf(stderr, "sem: set not implemented\n");
    return((struct sem_rec *) NULL);
  }

  /* if for type consistency of x and y */
  cast_y = y;
  if((x->s_mode & T_DOUBLE) && !(y->s_mode & T_DOUBLE)){
    
    /*cast y to a double*/
    printf("t%d = cvf t%d\n", nexttemp(), y->s_place);
    cast_y = node(currtemp(), T_DOUBLE, (struct sem_rec *) NULL,
		  (struct sem_rec *) NULL);
  }
  else if((x->s_mode & T_INT) && !(y->s_mode & T_INT)){

    /*convert y to integer*/
    printf("t%d = cvi t%d\n", nexttemp(), y->s_place);
    cast_y = node(currtemp(), T_INT, (struct sem_rec *) NULL,
		  (struct sem_rec *) NULL);
  }

  /*output quad for assignment*/
  if(x->s_mode & T_DOUBLE)
    printf("t%d := t%d =f t%d\n", nexttemp(), 
	   x->s_place, cast_y->s_place);
  else
    printf("t%d := t%d =i t%d\n", nexttemp(), 
	   x->s_place, cast_y->s_place);

  /*create a new node to allow just created temporary to be referenced later */
  return(node(currtemp(), (x->s_mode&~(T_ARRAY)),
	      (struct sem_rec *)NULL, (struct sem_rec *)NULL));
}

/*
 * startloopscope - start the scope for a loop
 */
void startloopscope()
{
   fprintf(stderr, "sem: startloopscope not implemented\n");
}

/*
 * string - generate code for a string
 */
struct sem_rec *string(const char *s)
{
   fprintf(stderr, "sem: string not implemented\n");
   return ((struct sem_rec *) NULL);
}

void
init_IR ()
{
    TheModule = llvm::make_unique<Module>("LEROY", TheContext);
}

void
emit_IR ()
{
    TheModule->print(outs(), nullptr);
}
