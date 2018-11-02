#include <stdio.h>

extern "C" {
    #include "cc.h"
    #include "scan.h"
    #include "semutil.h"
    #include "sem.h"
    #include "sym.h"
}

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
void bgnstmt()
{
  extern int lineno;

  printf("bgnstmt %d\n", lineno);
  //   fprintf(stderr, "sem: bgnstmt not implemented\n");
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
struct sem_rec *con(const char *x)
{
   fprintf(stderr, "sem: con not implemented\n");
   return ((struct sem_rec *) NULL);
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
void doret(struct sem_rec *e)
{
   fprintf(stderr, "sem: doret not implemented\n");
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
 * fhead - beginning of function body
 */
void fhead(struct id_entry *p)
{
   fprintf(stderr, "sem: fhead not implemented\n");
}

/*
 * fname - function declaration
 */
struct id_entry *fname(int t, const char *id)
{
   fprintf(stderr, "sem: fname not implemented `%s'\n", id);
   return ((struct id_entry *) NULL);
}

/*
 * ftail - end of function body
 */
void ftail()
{
   fprintf(stderr, "sem: ftail not implemented\n");
}

/*
 * id - variable reference
 */
struct sem_rec *id(const char *x)
{
   fprintf(stderr, "sem: id not implemented\n");
   return ((struct sem_rec *) NULL);
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
struct sem_rec *set(const char *op, struct sem_rec *x, struct sem_rec *y)
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
emit_ir ()
{
    // Make the module, which holds all the code.
    TheModule = llvm::make_unique<Module>("LEROY", TheContext);

    std::vector<Type*> argTypes;
	FunctionType *FT =
        FunctionType::get(Type::getInt8Ty(TheContext), makeArrayRef(argTypes), false);

	Function *F =
      Function::Create(FT, Function::ExternalLinkage, "main", TheModule.get());
	
    BasicBlock *BB = BasicBlock::Create(TheContext, "entry", F);
    Builder.SetInsertPoint(BB);

    Value *val = ConstantInt::get(Type::getInt8Ty(TheContext), 0);
    Builder.CreateRet(val);

    if (verifyFunction(*F, &errs())) {
        fprintf(stderr, "\n\n");
        return;
    }

    // Print out all of the generated code.
    TheModule->print(outs(), nullptr);
}
