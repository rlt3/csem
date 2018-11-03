#ifndef SYM_H
#define SYM_H

void dump(int, FILE *);
void new_block();
void exit_block();
void enterblock();
struct id_entry *install(const char *, int);
void leaveblock();
struct id_entry *lookup(const char *, int);
void sdump(FILE *);
char *slookup(const char *);
int hash(const char *);
char *alloc(unsigned);
void save_rec(struct sem_rec *);

#endif
