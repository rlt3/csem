#include <stdio.h>
#include <stdlib.h>
#include "semutil.h"
#include "cc.h"
#include "sem.h"
#include "sym.h"

int ntmp = 0;                /* last temporary number      */
int formalnum;               /* number of formal arguments */
char formaltypes[MAXARGS];   /* types of formal arguments  */
int localnum;                /* number of local variables  */
char localtypes[MAXLOCS];    /* types of local variables   */
int localwidths[MAXLOCS];    /* widths of local variables  */

extern struct sem_rec **top;
extern void yyerror (const char *msg);

/*
 * currtemp - returns the current temporary number
 */
int currtemp()
{
   return ntmp;
}

/*
 * dcl - adjust the offset or allocate space for a global
 */
struct id_entry *dcl(struct id_entry *p, int type, int scope)
{
   extern int level;

   p->i_type += type;
   if (scope != 0)
      p->i_scope = scope;
   else if (p->i_width > 0 && level == 2)
      p->i_scope = GLOBAL;
   else
      p->i_scope = LOCAL;
   if (level > 2 && p->i_scope == PARAM) {
      p->i_offset = formalnum;
      if (p->i_type == T_DOUBLE)
         formaltypes[formalnum++] = 'f';
      else
         formaltypes[formalnum++] = 'i';
      if (formalnum > MAXARGS) {
         fprintf(stderr, "too many arguments\n");
         exit(1);
      }
   }
   else if (level > 2 && p->i_scope != PARAM) {
      p->i_offset = localnum;
      localwidths[localnum] = p->i_width;
      if (p->i_type & T_DOUBLE)
         localtypes[localnum++] = 'f';
      else
         localtypes[localnum++] = 'i';
      if (localnum > MAXLOCS) {
         fprintf(stderr, "too many locals\n");
         exit(1);
      }
   }
   else if (p->i_width > 0 && level == 2)
      printf("alloc %s %d\n", p->i_name,
             p->i_width * tsize(p->i_type&~T_ARRAY));
   return p;
}

/*
 * dclr - insert attributes for a declaration
 */
struct id_entry *dclr(char *name, int type, int width)
{
   struct id_entry *p;
   extern int level;
   char msg[80];

   if ((p = lookup(name, 0)) == NULL || p->i_blevel != level)
      p = install(name, -1);
   else  {
      sprintf(msg, "identifier %s previously declared", name);
      yyerror(msg);
      return (p);
   }
   p->i_defined = 1;
   p->i_type = type;
   p->i_width = width;
   return (p);
}

/*
 * merge - merge backpatch lists p1 and p2
 */
struct sem_rec *merge(struct sem_rec *p1, struct sem_rec *p2)
{
   struct sem_rec *p;

   if (p1 == NULL)
      return (p2);
   if (p2 == NULL)
      return (p1);
   for (p = p1; p->back.s_link; p = p->back.s_link)
      ;
   p->back.s_link = p2;
   return (p1);
}

/*
 * nexttemp - increments the temporary number and returns it
 */
int nexttemp()
{
   return ++ntmp;
}

/*
 * node - allocate a semantic node with fields a, b, c, d
 */
struct sem_rec *node(int a, int b, struct sem_rec *c, struct sem_rec *d)
{
   struct sem_rec *t;

   /* allocate space */
   t = (struct sem_rec *) alloc(sizeof(struct sem_rec));

   /* save semantic record */
   save_rec(t);

   /* fill in the fields */
   t->s_place = a;
   t->s_mode = b;
   t->back.s_link = c;
   t->s_false = d;
   return (t);
}

/*
 * tsize - return size of type
 */
int tsize(int type)
{
   if (type == T_INT)
      return(4);
   else if (type == T_DOUBLE)
      return(8);
   else 
      return(0);
}
