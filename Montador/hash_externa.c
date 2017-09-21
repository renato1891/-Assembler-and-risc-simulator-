//Nome: Renato Borges Boaventura
//matricula: 0021620
//data 10/10/2016
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "hash_externa.h"
#include "lista_hash.h"
#include <ctype.h>
#include <math.h>




struct hash{
  int tamanho;
  int vetor_numero[32]; // vetor de números que irá ser usado na funcao hash 1
  Listah *vetor_lista; 
};


Hash cria_hash(void){
  int i;
  Hash aux = (Hash) malloc (sizeof(struct hash));
  srand((unsigned) time(NULL)); //semente de randomizacao    
  aux->vetor_lista = (Listah*) malloc (sizeof(Listah)*18);
  aux->tamanho = 18;

  for(i=0;i<32;i++)
      aux->vetor_numero[i]= (1+rand()%((15+1)-1));   //randomiza os números do vetor de números 
  for(i=0;i<18; i++)
    aux->vetor_lista[i] = NULL;   //inicia todos os ponteiros pra NULL
  return aux;
}




// primeira funcao hash 
int funcao1(Hash p, char  *chave){
    

    int chave_int = decodifica(p,chave);

    
    return(chave_int%p->tamanho);
}



int decodifica(Hash p,char *palavra){  //funcao auxiliar da funcao1(primeira funcao hash)
    int i, numero=0;
    for(i=0;i<strlen(palavra); i++)
        numero+= palavra[i]*p->vetor_numero[i];
    return numero;
}

void insere_hash(Hash p, char *palavra, int pc){
    

    int pos = funcao1(p,palavra);  // primeira funcao hash
    if(p->vetor_lista[pos]==NULL)  //caso não tiver uma lista criada, ela vai ser criada
      p->vetor_lista[pos] = cria_listah();  
      insere_listah(p->vetor_lista[pos],palavra, pc);
      return;
}




int compara_palavras(char *palavra1, char *palavra2){
  int i;
    if(strlen(palavra1) != strlen(palavra2)){
      return 0;
    }

     i = strncmp(palavra1, palavra2, 32);
     if(i==0)
      return 1;
    else 
      return 0;
}


void destroi_hash(Hash p){
  if(p==NULL){
    return;
  }
  int i;
  for(i=0;i<p->tamanho;i++){
    destroi_listah(p->vetor_lista[i]);
    p->vetor_lista[i] = NULL;
  }
 free(p->vetor_lista);
 free(p);
}




int retorna_pc(Hash p, char *palavra){
  int pos = funcao1(p,palavra);  // primeira funcao hash
  if(p->vetor_lista[pos]!= NULL)
    return(retorna_elemento(p->vetor_lista[pos], palavra));
  else 
    return 0;

}