#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "inout.h"
#include "database.h"


int main(){
  int fin =0;
  char q, x;
  pPatient pHead;
  pHead =NULL;

  FILE *fich;          //Fichero
  fich=fopen("patients.txt","r");

  if(fich!=NULL){
    if((x=fgetc(fich))!=EOF){
      rewind(fich);
      pHead =CreaLista(fich);
      fclose(fich);
  }
  }

  fich=fopen("patients.txt", "w");
 stripe('-',50);      //CarÃ¡tula
   headline("DIVOC_",'|');
   stripe('-',50);
    
  do {                         //MenÃº
    fprintf (stdout, "\n\nR) Register a patient\nS) Search for a patient\nD) Discharge a patient\nL) List patients by age\nP) Mark positive\n\nX) Exit the program\n\n");
      q=get_character ("Choose an option", "RSDLPX");
  
   switch(toupper(q)) {
    case 'R':
      pHead=p_register(pHead);
      break;
  case 'S':
      p_search(pHead);
      break;
    case 'L':
       p_list(pHead);
      break;
    case 'D':
      pHead=p_discharge(pHead);
      break;
      case 'P':
	p_mark(pHead);
	break;
      case 'X':
	fin =p_exit (fich,pHead);     
      break;
    default:
      break;

  }
   
  }while (fin==0);

      fclose(fich);
      return 0;
      }

