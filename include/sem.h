#ifndef SEM_H
#define SEM_H

void bgnstmt();
void global_alloc (struct id_entry*, int);
struct sem_rec *call(const char *, struct sem_rec *);
struct sem_rec *cast(struct sem_rec *, int);
struct sem_rec *ccand(struct sem_rec *, void*, struct sem_rec *);
struct sem_rec *ccexpr(struct sem_rec *);
struct sem_rec *ccnot(void*, struct sem_rec *);
struct sem_rec *ccor(struct sem_rec *, void*, struct sem_rec *);
struct sem_rec *con(const char *);
void dobreak();
void docontinue();
void dodo(void*, void*, void*, struct sem_rec *, void*);
void dofor(void*, void*, struct sem_rec *, void*, struct sem_rec *, void*,
           struct sem_rec *, void*);
void dogoto(const char *);
void doif(void*, struct sem_rec *, void*, void*);
void doifelse(void*, struct sem_rec *, void*, struct sem_rec *, void*, void*);
void doret(struct sem_rec *);
void dowhile(void*, void*, struct sem_rec *, void*, struct sem_rec *, void*);
void endloopscope(int);
struct sem_rec *exprs(struct sem_rec *, struct sem_rec *);
void fhead(struct id_entry *);
struct id_entry *fname(int, const char *);
void ftail();
struct sem_rec *gen(const char *, struct sem_rec *, struct sem_rec *, int);
struct sem_rec *id(const char *);
struct sem_rec *indx(struct sem_rec *x, struct sem_rec *i);
void labeldcl(const char *);
void* m();
void* m_get(int);
struct sem_rec *n();
struct sem_rec *op1(const char *, struct sem_rec *);
struct sem_rec *op2(const char *, struct sem_rec *, struct sem_rec *);
struct sem_rec *opb(const char *, struct sem_rec *, struct sem_rec *);
struct sem_rec *rel(const char *, struct sem_rec *, struct sem_rec *);
struct sem_rec *set(const char *, struct sem_rec *, struct sem_rec *);
void startloopscope();
struct sem_rec *string(const char *);

void init_IR ();
void emit_IR ();

#endif
