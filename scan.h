void initlex();
void initrw(int, const char *);
int yylex();
void skip();
void comment();
int istype(int);
void putbak(int);
int quote(char []);
