#include <stdio.h>


struct aPatient{
  char name[100];
  char DNI[100];
  int date;
  int fever;
  int cough;
  char symptom;

  struct aPatient *sig;

};
 typedef struct aPatient Patient;
  typedef struct aPatient *pPatient;



pPatient p_register(pPatient);

pPatient  p_discharge(pPatient);

int p_list(pPatient);

int p_search(pPatient);

int p_mark (pPatient);

int p_exit(FILE*, pPatient);
