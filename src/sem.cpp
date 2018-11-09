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
extern struct id_entry* formalentries[MAXLOCS];   /* entries for parameters */
extern struct id_entry* localentries[MAXLOCS];   /* entries for local variables */

using namespace llvm;

static LLVMContext TheContext;
static IRBuilder<> Builder(TheContext);
static std::unique_ptr<Module> TheModule;
static Function* TheFunction;
static std::map<std::string, AllocaInst*> local_values;

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
struct sem_rec *ccand(struct sem_rec *e1, void* m, struct sem_rec *e2)
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
struct sem_rec *ccor(struct sem_rec *e1, void* m, struct sem_rec *e2)
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
    R->s_mode |= T_INT;
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
void dodo(void* m1, void* m2, struct sem_rec *e, void* m3)
{
   fprintf(stderr, "sem: dodo not implemented\n");
}

/*
 * dofor - for statement
 */
void dofor(void* m1, struct sem_rec *e2, void* m2, struct sem_rec *n1,
           void* m3, struct sem_rec *n2, void* m4)
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
void
doif(struct sem_rec *R, void* m1, void* m2)
{
   fprintf(stderr, "sem: doif not implemented\n");
}

/*
 * doifelse - if then else statement
 */
void doifelse(struct sem_rec *e, void* m1, struct sem_rec *n,
                         void* m2, void* m3)
{
   fprintf(stderr, "sem: doifelse not implemented\n");
}

/*
 * doret - return statement
 */
void
doret (struct sem_rec *R)
{
    if (!R) {
        Builder.CreateRetVoid();
        return;
    }

    Type *rettype, *valtype;
    Value *value;

    /* Make sure the value matches the return type of the function */
    value = (Value*) R->anything;
    valtype = value->getType();
    rettype = TheFunction->getReturnType();

    if (rettype->isIntegerTy() && valtype != rettype)
        value = Builder.CreateFPToSI(value, TheFunction->getReturnType(), "cast");
    else if (rettype->isDoubleTy() && valtype != rettype)
        value = Builder.CreateSIToFP(value, TheFunction->getReturnType(), "cast");

    Builder.CreateRet(value);
}

/*
 * dowhile - while statement
 */
void dowhile(void* m1, struct sem_rec *e, void* m2, struct sem_rec *n,
             void* m3)
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
 * Create an allocated instance of a variable inside the 'entry' of a function.
 */
AllocaInst*
create_func_alloca (Function *F, int type, int width, std::string var)
{
    Value *arr_size = NULL;
    IRBuilder<> B(&F->getEntryBlock(), F->getEntryBlock().begin());

    if (width > 1)
        arr_size = ConstantInt::get(Type::getInt8Ty(TheContext), width);

    switch (type) {
        case 'f':
            return B.CreateAlloca(Type::getDoubleTy(TheContext), arr_size, var);
        case 'i':
        default:
            return B.CreateAlloca(Type::getInt8Ty(TheContext), arr_size, var);
    }
}

/*
 * Given two semantic records, cast the right LLVM Value to match the left.
 */
Value*
cast_pair (struct sem_rec *left, struct sem_rec *right)
{
    Value *R = (Value*) right->anything;
    if ((left->s_mode & T_DOUBLE) && !(right->s_mode & T_DOUBLE))
        R = Builder.CreateSIToFP(R, Type::getDoubleTy(TheContext), "cast");
    else if ((left->s_mode & T_INT) && !(right->s_mode & T_INT))
        R = Builder.CreateFPToSI(R, Type::getInt8Ty(TheContext), "cast");
    return R;
}

/*
 * Take a constructed function id_entry and add it to the LLVM AST.
 */
void
fhead (struct id_entry *E)
{
    std::vector<Type*> args;
    Type* func_type;
    GlobalValue::LinkageTypes linkage;
	FunctionType *FT;
    Function *F;
    BasicBlock *B;
    int i;

    /* push back each function argument */
    for (i = 0; i < formalnum; i++) {
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

    /* name each function argument */
    i = 0;
    for (auto &arg : F->args())
        arg.setName(formalentries[i++]->i_name);

    B = BasicBlock::Create(TheContext, "entry", F);
    Builder.SetInsertPoint(B);

    /* Start rebuilding the local values for the function scope */
    local_values.clear();

    /* 
     * We have binded the arguments to create function F. Now we must allocate
     * instances of them so they can be referenced and also mutated.
     */
    i = 0;
	for (auto &arg : F->args()) {
        std::string name = arg.getName();
        auto value = create_func_alloca(F, formaltypes[i++], 1, name);
        /* assign the initial value of the parameter (from a function call) */
        Builder.CreateStore(&arg, value);
        local_values[name] = value;
	}

    /* Create the instance of stack memory for each local variable */
    for (i = 0; i < localnum; i++) {
        std::string name = std::string(localentries[i]->i_name);
        auto value = create_func_alloca(F, localtypes[i], localwidths[i], name);
        local_values[name] = value;
    }

    TheFunction = F;
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
    struct sem_rec *R;
    struct id_entry *E;

    E = lookup(x, 0);
    if (!E) {
        yyerror("undefined reference");
        exit(1);
    }

    R = node(currtemp(), E->i_type, NULL, NULL);
    R->anything = (void*) local_values[std::string(x)];
    R->id = E;
    return R;
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
void*
m (int is_lead)
{
    return NULL;
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
struct sem_rec *
op1 (const char *op, struct sem_rec *y)
{
    Value *variable;

    variable = (Value*) y->anything;

    switch (*op) {
        case '@':
            /*
             * Very confusing. 'variable' first takes the value of the instance
             * of the variable inside the semantic record 'y' which is basically
             * a pointer. Then we create a 'load' or dereference of that
             * variable and overwrite the semantic record with that value.
             */
            y->anything = (void*) Builder.CreateLoad(variable, std::string(y->id->i_name));
            break;
        case '~':
        case '-':
        default:
           fprintf(stderr, "sem: op1 %s not implemented\n", op);
            return NULL;
    }

    return y;
}

/*
 * op2 - arithmetic operators
 */
struct sem_rec *
op2(const char *op, struct sem_rec *x, struct sem_rec *y)
{
    Value *L, *R;

    L = (Value*) x->anything;
    R = cast_pair(x, y);

    switch (*op) {
        case '+':
            x->anything = (void*) Builder.CreateAdd(L, R, "addtmp");
            break;
        case '-':
            x->anything = (void*) Builder.CreateSub(L, R, "subtmp");
            break;
        case '*':
            x->anything = (void*) Builder.CreateMul(L, R, "multmp");
            break;
        case '/':
            x->anything = (void*) Builder.CreateSDiv(L, R, "divtmp");
            break;
        case '%':
            x->anything = (void*) Builder.CreateSRem(L, R, "remtmp");
            break;
        default:
           fprintf(stderr, "sem: op2 %s not implemented\n", op);
           return NULL;
    }

    return x;
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
struct sem_rec *
rel (const char *op, struct sem_rec *x, struct sem_rec *y)
{
    //Value *L, *R;

    //L = (Value*) x->anything;
    //R = cast_pair(x, y);

    switch (*op) {
        case '=':
            //x->anything = (void*) Builder.CreateICmpEQ(L, R, "eqtmp");
            //break;

        case '!':
        case '>':
        case '<':
        default:
            fprintf(stderr, "sem: rel %s not implemented\n", op);
            return NULL;
    }

    return x;
}

/*
 * set - assignment operators
 */
struct sem_rec *
set (const char *op, struct sem_rec *x, struct sem_rec *y)
{
    Value *variable, *value;

    printf("SET\n");

    variable = (Value*) x->anything;
    value = (Value*) y->anything;

    value = cast_pair(x, y);
    Builder.CreateStore(value, variable);

    return x;
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
