#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "inout.h"
#include "database.h"



pPatient CreaPaciente(char *name, char *DNI, int date,int fever, int cough, char symptom){
  pPatient pAux= (pPatient)malloc(sizeof(Patient));
  pAux->date=date;
  pAux->fever=fever;
  pAux->cough=cough;
  pAux->symptom=symptom;
  strcpy(pAux->name, name);
  strcpy(pAux->DNI, DNI);

  pAux->sig= NULL;

  return pAux;
}

pPatient CreaLista(FILE *fich) {
  pPatient pAux;
  pPatient pIni;
  pPatient pFin;

  int y=0;
  char name[256];
  int date;
  char DNI [256];
  int fever;
  int cough;
  char symptom;


  while(y!=20) {
    fscanf(fich, "%s %s %d %d %d %c", name, DNI,&date, &fever, &cough, &symptom);
    
    if(feof(fich)!=0){
      break;
    }
      
   pAux = CreaPaciente(name, DNI, date, fever, cough, symptom);

  if(y==0){
    pIni=pFin=pAux;
    y++;
  }
 
  else{
    pFin->sig = pAux;
    pFin = pAux;
  }
  }
  return pIni;
}

void ImprimePaciente (FILE *fich, pPatient pHead) {
 while (pHead!=NULL) {
    fputs (pHead->name, fich);
    fprintf (fich, " ");
    fputs (pHead->DNI, fich);
    fprintf (fich, " ");
    fprintf (fich, "%d ", pHead->date);
    fprintf (fich, "%d ", pHead->fever);
    fprintf (fich, "%d ", pHead->cough);
    fprintf (fich, "%c\n", pHead->symptom);
	pHead = pHead->sig;
    }
}

pPatient InsertaPaciente (char *name, char *DNI,int date, int fever, int cough, char symptom, pPatient pHead) {

  pPatient pAux;
  pPatient pCheck;

  pCheck = CreaPaciente(name, DNI, date,fever, cough, symptom);
  
  if (pHead == NULL){
    pHead = pCheck;
  }
   

  else {
    pAux = pHead;
  
  
   while (pAux->sig != NULL) {
     pAux=pAux->sig;
   }
   
     pAux->sig = pCheck;
  }

  return pHead;
}

pPatient EliminaPaciente(pPatient pHead, char *DNI) {

  pPatient anterior;
  pPatient remove;

  
  if (strcmp(pHead->DNI, DNI) == 0) remove = pHead;

  else {
    anterior = pHead;
    if (anterior->sig == NULL) return NULL;
    else{
    while (strcmp(anterior->sig->DNI, DNI) !=0) {
      anterior = anterior->sig;
      if (anterior->sig == NULL) return NULL;
    }
    remove = anterior->sig;
    }
  }

  if (remove == pHead) {

    if (remove->sig == NULL) return -1;
      pHead = pHead->sig;
    free(remove);
  }
  else {
    anterior->sig = remove->sig;
    free(remove);
  }

  return pHead;
}

pPatient BuscaPaciente(pPatient pHead, char *DNI) {

  while (pHead != NULL) {

    if (strcmp(pHead->DNI, DNI) == 0) return pHead;
    else pHead = pHead->sig;
  }
  return NULL;
}


void headline(char *mensaje, char simbolo){                  //muestra el nombre de la aplicación

  int k;

  fprintf(stdout,"%c",simbolo);
  
  for(k=0;k<21;k++){
    fprintf (stdout," ");
  }
  
  fprintf(stdout,"%s",mensaje);

  for(k=0;k<21;k++){
    fprintf(stdout," ");
  }

  fprintf(stdout,"%c\n",simbolo);

  return;

}


void stripe(char simbolo, int size){                    //dibuja una línea formada por guiones

  int k;
  
  for(k=0;k<size;k++){
    fprintf(stdout,"%c",simbolo);
  }
  fprintf(stdout,"\n");
    return;
}


  void get_string(char *opcion,char *datoleido,int MIN,int MAX){  //lee una cadena desde el teclado
    
    char dato[MAX],linea [256],extra[256];
    int longitud,x=0;
  do{
    fprintf(stdout,"%s", opcion);
    fprintf(stdout,"(%d-%d char):\n",MIN,MAX);
 fgets (linea, sizeof(linea),stdin);
  x=sscanf (linea,"%s%s",dato,extra);
  if (x==1)
  longitud= strlen(dato);
  else
    longitud=-1;
    }while ((longitud<MIN)||(longitud>MAX));
  strcpy (datoleido,dato);
 }

  int  get_integer(char *opcion,int MIN,int MAX ){            //lee un entero desde el teclado
    int entero,x=0,valido;
    char extra[256],linea[256];
    
    while (x==0){
      fprintf (stdout,"%s", opcion);
      fprintf (stdout,"[%d-%d]:\n", MIN, MAX);
  fgets (linea, sizeof(linea),stdin);
  valido=sscanf(linea,"%d%s",&entero,extra);
  if (valido == 1) {
  if((entero<=MAX)&&(entero>=MIN)){
      x= 1;
    }
  }
    }

  return entero;
  }

  char  get_character(char *opcion, char *comprobacion){ //lee un carácter desde el teclado

    char caracter;
    int x=0;
    char *comprobamos, linea[256], extra[256];
    do{
      fprintf(stdout,"%s", opcion);
      fprintf(stdout,"(%s): \n",comprobacion);
    
      
  fgets (linea, sizeof(linea),stdin);
  x= sscanf(linea,"%c%s", &caracter, extra);
  
  caracter=toupper(caracter);
  comprobamos= strchr(comprobacion,caracter);
    }while ((comprobamos ==NULL)|| x!=1);
 
	   return caracter;
}

int yes_or_no(char *pregunta){  //confirma si el usuario responde que sí o no
  char respuesta;
  int valido;
  char extra[256],linea[256];

  do{
    fprintf(stdout,"%s\n", pregunta);
  fgets(linea, sizeof(linea),stdin);
  valido= sscanf(linea,"%c%s", &respuesta,extra);
  respuesta=toupper(respuesta);
  }while ((respuesta !='N' && respuesta !='Y')|| valido !=1);


  if(respuesta=='Y')
    return 1;
     

  else
    return 0;
}
 

    void display_patient(pPatient pHead){         //muestra la informacion sobre un paciente
      fprintf(stdout, ">%24s;%s;%d;%d;%d;%c;\n", pHead->name, pHead->DNI, pHead->date, pHead->fever, pHead->cough, pHead->symptom);
    }
     
     

  int verify_dni (char *DNI) {

  
    int dni_numerico;
    char letra;
    char indice;
    char comprobacion[] = "TRWAGMYFPDXBNJZSQVHLCKE";
    char cadena[10];
    int i;

    strcpy(cadena, DNI);

    cadena[8] = '\0';

    for (i=0; i<8; i++) {

      if ( isdigit(cadena[i])==0) return 0;
    }

    
    dni_numerico = atoi(cadena);
  
    indice = comprobacion[dni_numerico%23];
    letra = DNI[8];

  
    if (indice == letra) {
      return 1;
    }

    else if (indice != letra) {
      return 0;
    }

    return 0;
   
  }
