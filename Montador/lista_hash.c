//Nome: Renato Borges Boaventura
//matricula: 0021620
//data 10/10/2016
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lista_hash.h"
#include "hash_externa.h"


struct listah{
	Nodoh inicio;
	Nodoh final;
	int quantidade;

};

struct nodoh{
	char palavra[32];
	Nodoh prox;
    int pc;
};


Listah cria_listah(void){
	Listah aux = (Listah) malloc (sizeof(struct listah));
	aux -> inicio =NULL;
	aux -> final = NULL;
	aux -> quantidade = 0;
	return aux;
}

void insere_listah(Listah p, char *palavra, int pc){
	Nodoh aux = (Nodoh) malloc (sizeof(struct nodoh));
        strcpy(aux->palavra,palavra);
        if (p->inicio==NULL){
        aux -> prox = NULL;
       	aux->pc = pc;
        p->inicio = aux;
        p->final= aux;
        p->quantidade++; 
        return;
    }
	
    p->final->prox = aux;
    p->final = aux;
    aux->prox = NULL;
    aux ->pc = pc;
    p->quantidade++;
    return;
}

void destroi_listah(Listah p){
    if(p==NULL){
        return;
    }
    while(p->inicio!=NULL){
        apaga_pos_listah(p,1);
	}
    p = NULL;
    return;
}

void apaga_pos_listah(Listah p, int pos){
    if (p==NULL)
        return;
        if(pos==1){
            Nodoh aux = p->inicio;
            if(p->inicio==p->final){
                free(aux);
                p->inicio = NULL;
                p->final = NULL;
                p->quantidade--;
                return;
            }
            p->inicio = p->inicio->prox;    //essa função apaga somente a primeira posicao da lista
            free(aux);
            p->quantidade--;
            return;
        }
}

int retorna_elemento(Listah p, char *palavra){
    Nodoh aux = p->inicio;
    while(aux != NULL && !compara_palavras(aux->palavra, palavra) && aux != NULL )
        aux = aux->prox;
    if(aux != NULL)
        return(aux->pc);
    else 
        return 0;
}