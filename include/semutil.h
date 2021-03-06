#ifndef SEMUTIL_H
#define SEMUTIL_H

#define MAXARGS 50
#define MAXLOCS 50

int currtemp();
struct id_entry *dcl(struct id_entry *, int, int);
struct id_entry *dclr(char *, int, int);
struct sem_rec *merge(struct sem_rec *, struct sem_rec *);
int nexttemp();
struct sem_rec *node(int, int, struct sem_rec *, struct sem_rec *);
int tsize(int);

#endif
