#include <stdio.h>

struct aPatient;

  typedef struct aPatient Patient;
  typedef struct aPatient *pPatient;

pPatient CreaPaciente(char *, char *, int, int, int, char);

pPatient CreaLista(FILE *);

void ImprimePaciente (FILE *, pPatient);

pPatient InsertaPaciente (char*, char*,int,int,int,char,pPatient);

pPatient EliminaPaciente(pPatient, char*);

pPatient BuscaPaciente(pPatient , char *);

void get_string(char *, char *, int, int);

int get_integer(char *, int, int);

char get_character(char *, char *);

void headline(char*, char);

void stripe(char, int);

int  yes_or_no(char *);

void display_patient(pPatient );


int verify_dni (char *);

