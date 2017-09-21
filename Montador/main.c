
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: renato
 *
 * Created on 14 de Setembro de 2016, 16:48
 */
/*
Nome: Renato Borges Boaventura
matricula: 0021620
data 10/10/2016
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "hash_externa.h"


/*======== ESTRUTURAS =========*/

/*======== VARIAVEIS GLOBAIS ==========*/


/*======== FUNCOES ===========*/



int fromBinary(char *s);
void primeiro_passo(Hash p, char* nome_arquivo);
void segundo_passo(Hash p, char *nome_arquivo_entrada, char *nome_arquivo_saida);
void getBin(int value, int bitsCount, char* output);
/*======== FUNCAO MAIN ===============*/



int main(int argc, char** argv){
	Hash p = cria_hash();
	primeiro_passo(p,argv[1]);
	segundo_passo(p,argv[1], argv[2]);
	exit(0);
}


/*======== FUNCOES ===========*/



int fromBinary(char *s) {
  return (int) strtol(s, NULL, 2);
}


void primeiro_passo(Hash p, char* nome_arquivo){
	int pc=-1;
	char *unidade;
	char linha[50] = " ";
	FILE *arq;
	arq = fopen(nome_arquivo, "r");
	if(arq == NULL){
			printf("Erro, nao foi possivel abrir o arquivo\n");
			exit(1);
	}
	while((fgets(linha, sizeof(linha)/sizeof(char), arq))!=NULL){
			unidade = strtok(linha," ,");
		while(unidade!=NULL){
			if(unidade[strlen(unidade)-1]=='\n')
				unidade[strlen(unidade)-1] = '\0';
			if(unidade[strlen(unidade)-1]== ':'){
				unidade[strlen(unidade)-1] = '\0';
				insere_hash(p, unidade, (pc+1));	
				pc--;
			}
				
				unidade = strtok(NULL," ,");

			}
			pc++;
		}
		fclose(arq);
		//printf("%d\n", retorna_pc(p, "LABEL2"));
	return;
}



void getBin(int value, int bitsCount, char* output)
{
    int i;
    output[bitsCount] = '\0';
    for (i = bitsCount - 1; i >= 0; --i, value >>= 1)
    {
        output[i] = (value & 1) + '0';
    }
}


void segundo_passo(Hash p, char *nome_arquivo_entrada, char *nome_arquivo_saida){
	char *unidade;
	char linha[50] = " ";
	FILE *arq1, *arq2;
	arq1 = fopen(nome_arquivo_entrada, "r");
	arq2 = fopen(nome_arquivo_saida, "w");
	fprintf(arq2,"address 0\n");
	if(arq1== NULL || arq2 ==NULL){
			printf("Erro, nao foi possivel abrir o arquivo\n");
			exit(1);
	}
	while((fgets(linha, sizeof(linha)/sizeof(char), arq1))!=NULL){
			unidade = strtok(linha," ,");
		while(unidade!=NULL){
			if(unidade[strlen(unidade)-1]=='\n')
				unidade[strlen(unidade)-1] = '\0';	
				if(compara_palavras(unidade, "lcl")){
					char bits[24];
					getBin(15,8,bits);
					fprintf(arq2,"%s",bits);
					char *registrador= strtok(NULL," ,");
					char *end = strtok(NULL," ,");
					int endReg = atoi(&registrador[1]);
					int constante = atoi(end);
					getBin(constante,16,bits);
					fprintf(arq2,"%s",bits);
					getBin(endReg,8,bits);
					fprintf(arq2,"%s\n",bits);
				}	

				if(compara_palavras(unidade, "nop")){
					char bits[24];
					getBin(0,32,bits);
					fprintf(arq2,"%s\n",bits);

				}	
				if(compara_palavras(unidade, "add")){
					char bits[24];
					getBin(1,8,bits);
					fprintf(arq2,"%s",bits);
					char *rc= strtok(NULL," ,");
					char *ra = strtok(NULL," ,");
					char *rb = strtok(NULL," ,");
					int rcint = atoi(&rc[1]);
					int raint = atoi(&ra[1]);
					int rbint = atoi(&rb[1]);
					getBin(raint,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(rbint,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(rcint,8,bits);
					fprintf(arq2,"%s\n",bits);

				}
				if(compara_palavras(unidade, "sub")){
					char bits[24];
					getBin(2,8,bits);
					fprintf(arq2,"%s",bits);
					char *rc= strtok(NULL," ,");
					char *ra = strtok(NULL," ,");
					char *rb = strtok(NULL," ,");
					int rcint = atoi(&rc[1]);
					int raint = atoi(&ra[1]);
					int rbint = atoi(&rb[1]);
					getBin(raint,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(rbint,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(rcint,8,bits);
					fprintf(arq2,"%s\n",bits);

				}
				if(compara_palavras(unidade, "zeros")){
					char bits[24];
					getBin(3,8,bits);
					fprintf(arq2,"%s",bits);
					char *rc= strtok(NULL," ,");
					int rcint = atoi(&rc[1]);
					getBin(rcint,24,bits);
					fprintf(arq2,"%s\n",bits);

				}
				if(compara_palavras(unidade, "xor")){
					char bits[24];
					getBin(4,8,bits);
					fprintf(arq2,"%s",bits);
					char *rc= strtok(NULL," ,");
					char *ra = strtok(NULL," ,");
					char *rb = strtok(NULL," ,");
					int rcint = atoi(&rc[1]);
					int raint = atoi(&ra[1]);
					int rbint = atoi(&rb[1]);
					getBin(raint,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(rbint,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(rcint,8,bits);
					fprintf(arq2,"%s\n",bits);

				}
				if(compara_palavras(unidade, "or")){
					char bits[24];
					getBin(5,8,bits);
					fprintf(arq2,"%s",bits);
					char *rc= strtok(NULL," ,");
					char *ra = strtok(NULL," ,");
					char *rb = strtok(NULL," ,");
					int rcint = atoi(&rc[1]);
					int raint = atoi(&ra[1]);
					int rbint = atoi(&rb[1]);
					getBin(raint,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(rbint,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(rcint,8,bits);
					fprintf(arq2,"%s\n",bits);

				}
				if(compara_palavras(unidade, "not")){
					char bits[24];
					getBin(6,8,bits);
					fprintf(arq2,"%s",bits);
					char *rc= strtok(NULL," ,");
					char *ra = strtok(NULL," ,");
					int rcint = atoi(&rc[1]);
					int raint = atoi(&ra[1]);
					getBin(raint,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(rcint,16,bits);
					fprintf(arq2,"%s\n",bits);

				}
				if(compara_palavras(unidade, "and")){
					char bits[24];
					getBin(7,8,bits);
					fprintf(arq2,"%s",bits);
					char *rc= strtok(NULL," ,");
					char *ra = strtok(NULL," ,");
					char *rb = strtok(NULL," ,");
					int rcint = atoi(&rc[1]);
					int raint = atoi(&ra[1]);
					int rbint = atoi(&rb[1]);
					getBin(raint,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(rbint,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(rcint,8,bits);
					fprintf(arq2,"%s\n",bits);

				}
				if(compara_palavras(unidade, "asl")){
					char bits[24];
					getBin(8,8,bits);
					fprintf(arq2,"%s",bits);
					char *rc= strtok(NULL," ,");
					char *ra = strtok(NULL," ,");
					char *rb = strtok(NULL," ,");
					int rcint = atoi(&rc[1]);
					int raint = atoi(&ra[1]);
					int rbint = atoi(&rb[1]);
					getBin(raint,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(rbint,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(rcint,8,bits);
					fprintf(arq2,"%s\n",bits);

				}
				if(compara_palavras(unidade, "asr")){
					char bits[24];
					getBin(9,8,bits);
					fprintf(arq2,"%s",bits);
					char *rc= strtok(NULL," ,");
					char *ra = strtok(NULL," ,");
					char *rb = strtok(NULL," ,");
					int rcint = atoi(&rc[1]);
					int raint = atoi(&ra[1]);
					int rbint = atoi(&rb[1]);
					getBin(raint,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(rbint,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(rcint,8,bits);
					fprintf(arq2,"%s\n",bits);

				}
				if(compara_palavras(unidade, "lsl")){
					char bits[24];
					getBin(10,8,bits);
					fprintf(arq2,"%s",bits);
					char *rc= strtok(NULL," ,");
					char *ra = strtok(NULL," ,");
					char *rb = strtok(NULL," ,");
					int rcint = atoi(&rc[1]);
					int raint = atoi(&ra[1]);
					int rbint = atoi(&rb[1]);
					getBin(raint,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(rbint,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(rcint,8,bits);
					fprintf(arq2,"%s\n",bits);

				}
				if(compara_palavras(unidade, "lsr")){
					char bits[24];
					getBin(11,8,bits);
					fprintf(arq2,"%s",bits);
					char *rc= strtok(NULL," ,");
					char *ra = strtok(NULL," ,");
					char *rb = strtok(NULL," ,");
					int rcint = atoi(&rc[1]);
					int raint = atoi(&ra[1]);
					int rbint = atoi(&rb[1]);
					getBin(raint,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(rbint,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(rcint,8,bits);
					fprintf(arq2,"%s\n",bits);

				}
				if(compara_palavras(unidade, "passa")){
					char bits[24];
					getBin(12,8,bits);
					fprintf(arq2,"%s",bits);
					char *rc= strtok(NULL," ,");
					char *ra = strtok(NULL," ,");
					int rcint = atoi(&rc[1]);
					int raint = atoi(&ra[1]);
					getBin(raint,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(rcint,16,bits);
					fprintf(arq2,"%s\n",bits);

				}
				if(compara_palavras(unidade, "lch")){
					char bits[24];
					getBin(14,8,bits);
					fprintf(arq2,"%s",bits);
					char *registrador= strtok(NULL," ,");
					char *end = strtok(NULL," ,");
					int endReg = atoi(&registrador[1]);
					int constante = atoi(end);
					getBin(constante,16,bits);
					fprintf(arq2,"%s",bits);
					getBin(endReg,8,bits);
					fprintf(arq2,"%s\n",bits);
				}	
				if(compara_palavras(unidade, "load")){
					char bits[24];
					getBin(16,8,bits);
					fprintf(arq2,"%s",bits);
					char *rc= strtok(NULL," ,");
					char *ra = strtok(NULL," ,");
					int rcint = atoi(&rc[1]);
					int raint = atoi(&ra[1]);
					getBin(raint,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(rcint,16,bits);
					fprintf(arq2,"%s\n",bits);

				}
				if(compara_palavras(unidade, "store")){
					char bits[24];
					getBin(17,8,bits);
					fprintf(arq2,"%s",bits);
					char *rc= strtok(NULL," ,");
					char *ra = strtok(NULL," ,");
					int rcint = atoi(&rc[1]);
					int raint = atoi(&ra[1]);
					getBin(raint,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(rcint,16,bits);
					fprintf(arq2,"%s\n",bits);

				}
				if(compara_palavras(unidade, "jal")){
					char bits[24];
					getBin(32,8,bits);
					fprintf(arq2,"%s",bits);
					char *end= strtok(NULL," ,");
					if(end[strlen(end)-1]=='\n')
						end[strlen(end)-1]= '\0';
					int endint = retorna_pc(p,end);
					getBin(endint,24,bits);
					fprintf(arq2,"%s\n",bits);

				}
				if(compara_palavras(unidade, "jr")){
					char bits[24];
					getBin(33,8,bits);
					fprintf(arq2,"%s",bits);
					char *rc= strtok(NULL," ,");
					int rcint = atoi(&rc[1]);
					getBin(rcint,24,bits);
					fprintf(arq2,"%s\n",bits);

				}
				if(compara_palavras(unidade, "beq")){
					char bits[24];
					getBin(34,8,bits);
					fprintf(arq2,"%s",bits);
					char *ra= strtok(NULL," ,");
					char *rb = strtok(NULL," ,");
					char *end = strtok(NULL," ,");
					if(end[strlen(end)-1]=='\n')
						end[strlen(end)-1]= '\0';
					int raint = atoi(&ra[1]);
					int rbint = atoi(&rb[1]);
					int endint = retorna_pc(p,end);
					getBin(raint,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(rbint,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(endint,8,bits);
					fprintf(arq2,"%s\n",bits);

				}
				if(compara_palavras(unidade, "bne")){
					char bits[24];
					getBin(35,8,bits);
					fprintf(arq2,"%s",bits);
					char *ra= strtok(NULL," ,");
					char *rb = strtok(NULL," ,");
					char *end = strtok(NULL," ,");
					if(end[strlen(end)-1]=='\n')
						end[strlen(end)-1]= '\0';
					int raint = atoi(&ra[1]);
					int rbint = atoi(&rb[1]);
					int endint = retorna_pc(p,end);
					getBin(raint,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(rbint,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(endint,8,bits);
					fprintf(arq2,"%s\n",bits);

				}
				if(compara_palavras(unidade, "j")){
					char bits[24];
					getBin(36,8,bits);
					fprintf(arq2,"%s",bits);
					char *end = strtok(NULL," ,");
					if(end[strlen(end)-1]=='\n')
						end[strlen(end)-1]= '\0';
					int endint = retorna_pc(p,end);
					getBin(endint,24,bits);
					fprintf(arq2,"%s\n",bits);

				}
			
				if(compara_palavras(unidade, "mult")){
					char bits[24];
					getBin(37,8,bits);
					fprintf(arq2,"%s",bits);
					char *rc= strtok(NULL," ,");
					char *ra = strtok(NULL," ,");
					char *rb = strtok(NULL," ,");
					int rcint = atoi(&rc[1]);
					int raint = atoi(&ra[1]);
					int rbint = atoi(&rb[1]);
					getBin(raint,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(rbint,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(rcint,8,bits);
					fprintf(arq2,"%s\n",bits);

				}
				if(compara_palavras(unidade, "div")){
					char bits[24];
					getBin(38,8,bits);
					fprintf(arq2,"%s",bits);
					char *rc= strtok(NULL," ,");
					char *ra = strtok(NULL," ,");
					char *rb = strtok(NULL," ,");
					int rcint = atoi(&rc[1]);
					int raint = atoi(&ra[1]);
					int rbint = atoi(&rb[1]);
					getBin(raint,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(rbint,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(rcint,8,bits);
					fprintf(arq2,"%s\n",bits);

				}
				if(compara_palavras(unidade, "elev")){
					char bits[24];
					getBin(39,8,bits);
					fprintf(arq2,"%s",bits);
					char *rc= strtok(NULL," ,");
					char *ra = strtok(NULL," ,");
					char *rb = strtok(NULL," ,");
					int rcint = atoi(&rc[1]);
					int raint = atoi(&ra[1]);
					int rbint = atoi(&rb[1]);
					getBin(raint,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(rbint,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(rcint,8,bits);
					fprintf(arq2,"%s\n",bits);

				}
				if(compara_palavras(unidade, "somai")){
					char bits[24];
					getBin(40,8,bits);
					fprintf(arq2,"%s",bits);
					char *rc= strtok(NULL," ,");
					char *ra = strtok(NULL," ,");
					char *rb = strtok(NULL," ,");
					int rcint = atoi(&rc[1]);
					int raint = atoi(&ra[1]);
					int rbint = atoi(&rb[1]);
					getBin(raint,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(rbint,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(rcint,8,bits);
					fprintf(arq2,"%s\n",bits);

				}
				if(compara_palavras(unidade, "subi")){
					char bits[24];
					getBin(41,8,bits);
					fprintf(arq2,"%s",bits);
					char *rc= strtok(NULL," ,");
					char *ra = strtok(NULL," ,");
					char *rb = strtok(NULL," ,");
					int rcint = atoi(&rc[1]);
					int raint = atoi(&ra[1]);
					int rbint = atoi(&rb[1]);
					getBin(raint,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(rbint,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(rcint,8,bits);
					fprintf(arq2,"%s\n",bits);

				}
				if(compara_palavras(unidade, "inc")){
					char bits[24];
					getBin(42,8,bits);
					fprintf(arq2,"%s",bits);
					char *rc= strtok(NULL," ,");
					int rcint = atoi(&rc[1]);
					getBin(rcint,24,bits);
					fprintf(arq2,"%s\n",bits);

				}
				if(compara_palavras(unidade, "dec")){
					char bits[24];
					getBin(43,8,bits);
					fprintf(arq2,"%s",bits);
					char *rc= strtok(NULL," ,");
					int rcint = atoi(&rc[1]);
					getBin(rcint,24,bits);
					fprintf(arq2,"%s\n",bits);

				}
				if(compara_palavras(unidade, "senzero")){
					char bits[24];
					getBin(44,8,bits);
					fprintf(arq2,"%s",bits);
					char *ra= strtok(NULL," ,");
					char *end = strtok(NULL," ,");
					if(end[strlen(end)-1]=='\n')
						end[strlen(end)-1]= '\0';
					int raint = atoi(&ra[1]);
					int endint = retorna_pc(p,end);
					getBin(raint,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(0,8,bits);
					fprintf(arq2,"%s",bits);
					getBin(endint,8,bits);
					fprintf(arq2,"%s\n",bits);

				}

				if(compara_palavras(unidade, "halt")){
					fprintf(arq2,"11111111111111111111111111111111\n");

				}

		
				unidade = strtok(NULL," ,");
			}

		}
		fclose(arq1);
		fclose(arq2);
		//printf("%d\n", retorna_pc(p, "LABEL2"));
	return;
}

