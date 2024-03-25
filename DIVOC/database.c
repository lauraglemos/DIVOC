#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "database.h"
#include "inout.h"

struct aPatient;
 typedef struct aPatient Patient;
  typedef struct aPatient *pPatient;


pPatient p_register(pPatient pHead){                    //registra a un nuevo paciente
  char name [256];
  char DNI[256];
  int date;
  int fever, cough;
  char  symptom;
  int check;
  fprintf(stdout,"Register\n");
  fprintf(stdout,"\n");
  get_string("Name",name,1,24);

  do{
    get_string("DNI",DNI,9,9) ;
    check = verify_dni (DNI);

    if (check==0) {
      fprintf(stdout,"\n");
      fprintf(stdout, "Invalid DNI\n");
       }
    }while(check==0);
      
  date=get_integer("Date",1900,2020);
  fever=yes_or_no("Fever (y/n) :");
  cough=yes_or_no("Cough (y/n) :");
  symptom=get_character("Symptom","FSTMN");

      
  pPatient pAux = CreaPaciente (name, DNI, date, fever, cough, symptom);
  pHead= InsertaPaciente(name, DNI, date, fever, cough, symptom, pHead);


  fprintf(stdout,"New patient:\n");
  display_patient(pAux);
  return pHead;
  
}

 int p_search(pPatient pHead){
   char DNI [256];
   
   fprintf(stdout,"Search\n");
   
  if(pHead==NULL){
    fprintf(stdout,"No patients yet\n");
    return 0;
  }
  
  get_string("DNI",DNI,9,9);
  pPatient pAux = BuscaPaciente (pHead, DNI);

  if(pAux ==NULL) {
    fprintf(stdout,"\n");
    fprintf(stdout,"Unknown patient\n"); }

  else{
    fprintf(stdout,"Patient data:\n");
    display_patient(pAux);
  }
    return 0;
  }

    
 


  pPatient  p_discharge(pPatient pHead){
    pPatient pAux;
    char DNI [256];
    
    fprintf(stdout,"Discharge\n");
  if(pHead==NULL){
    fprintf(stdout,"No patients yet\n");
  return NULL;
  }
    get_string("DNI",DNI,9,9);
     pAux = EliminaPaciente (pHead, DNI);
    
       if(pAux ==-1){
	 fprintf(stdout, "Discharged patient\n");
     return NULL;
       }
   if(pAux==NULL){
     fprintf(stdout,"\n");
     fprintf(stdout, "Unknown patient\n");
     return pHead;
       }

   else{

     pHead=pAux;

     fprintf(stdout, "Discharged patient\n");
    
      return pHead;
    }
  }
  int p_list (pPatient pHead){
    int  date;
    fprintf(stdout,"List\n");
  if(pHead==NULL){
    fprintf(stdout,"No patients yet\n");
    return 0;
}

  else{
fprintf(stdout,"\n");
  date=get_integer("Date",1900,2020);
  fprintf(stdout,"\n");
  fprintf(stdout,"Patients born before %d:\n",date);

  while (pHead != NULL){

    if (pHead->date<=date) display_patient (pHead);


    pHead = pHead ->sig;
  }

  }
return 0;

}

  
  
 int p_mark(pPatient pHead){ 
 fprintf(stdout,"Positives\n");
  if (pHead==NULL){
    fprintf(stdout,"No patients yet\n");
    return -1;  }
 else{
   fprintf(stdout,"\n");
    fprintf(stdout, "Positive patients:\n");
    while(pHead!=NULL){
      if((pHead->fever==1)&&(pHead->cough==1)&&((pHead->symptom)!='N'))
    display_patient(pHead);
    pHead = pHead ->sig;
      }}
 return 0;
  }
 
 int  p_exit(FILE *fich, pPatient pHead){
   int opcion;
   fprintf (stdout, "Exit\n");
  fprintf (stdout, "\n");

  opcion = yes_or_no("Are you sure you want to exit the program? (y/n):\n");

  if(opcion==0) {
    fprintf(stdout, "\n");
    return 0;
  }

 
    else {

      if (pHead!=NULL) {

      

	ImprimePaciente(fich, pHead);
    
      }
	

    return 1;
    }
  }
