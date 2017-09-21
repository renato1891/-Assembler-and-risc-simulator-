
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


/*======== ESTRUTURAS =========*/
struct operacao3
{
	unsigned int rc:8;
	unsigned int rb:8;
	unsigned int ra:8;
	unsigned int opcode:8;  
};

typedef struct operacao3 *Operacao3;

struct operacao2
{
	unsigned int rc:8;
	unsigned int end:16;
	unsigned int opcode:8;
};

typedef struct operacao2 *Operacao2;

struct operacao4{
	unsigned int end: 24;
 	unsigned int opcode: 8;
};

typedef struct operacao4 *Operacao4;




/*======== PROTOTIPO DAS FUNCOES ===========*/
int fromBinary(char *s);
void lcl(Operacao2 operacao2operando);
void lch(Operacao2 operacao2operando);
void soma(Operacao3 operacao3operandos);
void sub(Operacao3 operacao3operandos);
void zero(Operacao3 operacao3operandos);
void xor(Operacao3 operacao3operandos);
void or(Operacao3 operacao3operandos);
void not(Operacao3 operacao3operandos);
void and(Operacao3 operacao3operandos);
void asl(Operacao3 operacao3operandos);
void asr(Operacao3 operacao3operandos);
void lsl(Operacao3 operacao3operandos);
void lsr(Operacao3 operacao3operandos);
void copia(Operacao3 operacao3operandos);
void load(Operacao3 operacao3operandos);
void store(Operacao3 operacao3operandos);
void store(Operacao3 operacao3operandos);
void jal(Operacao4 operacao4operandos, int *PC);
void jr(Operacao3 operacao3operandos, int *PC);
void beq(Operacao3 operacao3operandos, int *PC);
void bne(Operacao3 operacao3operandos, int *PC);
void j(Operacao4 operacao4operandos, int *PC);
void mult(Operacao3 operacao3operandos);
void divisao(Operacao3 operacao3operandos);
void exponenciacao(Operacao3 operacao3operandos);
void soma_imediata(Operacao3 operacao3operandos);
void sub_imediato(Operacao3 operacao3operandos);
void inc(Operacao3 operacao3operandos);  
void dec(Operacao3 operacao3operandos);
void senzero(Operacao3 operacao3operandos, int *PC);

/*======== VARIAVEIS GLOBAIS ==========*/
int memoria[65536];
int bancoRegistradores[32];
int neg=0, zer=0, carry=0, overflow=0;

/*======== FUNCAO MAIN ===============*/
int main(int argc, char** argv){
	if(argc !=2){
		exit(1);
	}
	
	/*coloca nas primeiras posicoes da memoria as instrucoes*/
	
	//memoria[contMemoria] = 251658753; /*carrgar 2 para registrador r1*/
	//contMemoria++;
	//memoria[contMemoria] = 251658754; /*carrgar 2 para registrador r2*/
	//contMemoria++;
	//memoria[contMemoria] = 16974082; /*soma r1 com r2 e colocar em r3*/
	bancoRegistradores[0] = 0;
	char binario[34]= " ";
	FILE *arq;
	int numero=0,pc=0, IR;
	arq = fopen(argv[1], "r");
	if(arq == NULL){
			printf("Erro, nao foi possivel abrir o arquivo\n");
			exit(1);
	}
		fgets(binario, sizeof(binario)/sizeof(char), arq);
		char *unidade, letra;
			unidade = strtok(binario," ");
			while(unidade!=NULL){
            	letra = unidade[0];
				if(isdigit(letra))
				numero = fromBinary(unidade);	
				unidade = strtok(NULL," ");

			}
			pc = numero;
			while( (fgets(binario, sizeof(binario)/sizeof(char), arq))!=NULL ){
				memoria[numero] = fromBinary(binario);
				numero++;
			}
		while(memoria[pc]!= 0xffffffff){
				IR = memoria[pc];
				printf("PC: %d\n\n", pc);
				pc++;
				neg=0; 
				zer=0; 
				carry=0; 
				overflow=0;
				Operacao4 operacao4operandos = (Operacao4) &IR;
				Operacao3 operacao3operandos = (Operacao3) &IR;
				Operacao2 operacao2operandos = (Operacao2) &IR;
			if(operacao3operandos->opcode == 15)
				lcl(operacao2operandos);
			if(operacao3operandos->opcode == 14)
				lch(operacao2operandos);
			if(operacao3operandos->opcode == 1)
				soma(operacao3operandos);
			if(operacao3operandos->opcode == 2)
				sub(operacao3operandos);
			if(operacao3operandos->opcode == 3)
				zero(operacao3operandos);
			if(operacao3operandos->opcode == 4)
				xor(operacao3operandos);
			if(operacao3operandos->opcode == 5)
				or(operacao3operandos);
			if(operacao3operandos->opcode == 6)
				not(operacao3operandos);
			if(operacao3operandos->opcode == 7)
				and(operacao3operandos);
			if(operacao3operandos->opcode == 8)
				asl(operacao3operandos);
			if(operacao3operandos->opcode == 9)
				asr(operacao3operandos);
			if(operacao3operandos->opcode == 10)
				lsl(operacao3operandos);
			if(operacao3operandos->opcode == 11)
				lsr(operacao3operandos);
			if(operacao3operandos->opcode == 12)
				copia(operacao3operandos);
			if(operacao3operandos->opcode == 16)
				load(operacao3operandos);
			if(operacao3operandos->opcode == 17)
				store(operacao3operandos);
			if(operacao3operandos->opcode == 32)
				jal(operacao4operandos, &pc);
			if(operacao3operandos->opcode == 33)
				jr(operacao3operandos, &pc);
			if(operacao3operandos->opcode == 34)
				beq(operacao3operandos, &pc);
			if(operacao3operandos->opcode == 35)
				bne(operacao3operandos, &pc);
			if(operacao3operandos->opcode == 36)
				j(operacao4operandos, &pc);
			if(operacao3operandos->opcode == 37)
				mult(operacao3operandos);
			if(operacao3operandos->opcode == 38)
				divisao(operacao3operandos);
			if(operacao3operandos->opcode == 39)
				exponenciacao(operacao3operandos);
			if(operacao3operandos->opcode == 40)
				soma_imediata(operacao3operandos);
			if(operacao3operandos->opcode == 41)
				sub_imediato(operacao3operandos);
			if(operacao3operandos->opcode == 42)
				inc(operacao3operandos);
			if(operacao3operandos->opcode == 43)
				dec(operacao3operandos);
			if(operacao3operandos->opcode == 44)
				senzero(operacao3operandos, &pc);
			if(operacao3operandos==0)
				printf("FUNÇÃO NOP\n");

		}
	
	fclose(arq);
	exit(0);
}


/*======== FUNCOES ===========*/



int fromBinary(char *s) {
  return (int) strtol(s, NULL, 2);
}


void soma(Operacao3 operacao3operandos){
	printf("ADD\n");
	int rc, rb, ra;
	ra = operacao3operandos->ra;
	rb = operacao3operandos->rb;
	rc = operacao3operandos->rc;

	printf("RA = %d\n", ra);
	printf("RB = %d\n", rb);
	printf("RC = %d\n", rc);
	bancoRegistradores[rc] = bancoRegistradores[ra] + bancoRegistradores[rb];
	printf("REGISTRADOR %d POSSUI %d\n", rc, bancoRegistradores[rc]);
	if(bancoRegistradores[rc]==0)
		zer=1;
	if(bancoRegistradores[rc]<0)
		neg = 1;
	if((bancoRegistradores[ra]>>31 & 1) && (bancoRegistradores[rb]>>31 & 1))
		carry=1;
	else{
		if(((bancoRegistradores[ra]>>31 & 1)==0 && (bancoRegistradores[rb]>>31 & 1)==1 && (bancoRegistradores[rc]>>31&1)==0) 
			|| ((bancoRegistradores[ra]>>31 & 1)==1 && (bancoRegistradores[rb]>>31 & 1)==0 && (bancoRegistradores[rc]>>31&1)==0))
			carry = 1;
	}

	if(bancoRegistradores[ra]>>31&1 && bancoRegistradores[rb]>0 && bancoRegistradores[rc]<0)
		overflow = 1;

	printf("HÁ FLAGS AFETADAS.\nVALORES DAS FLAGS:\n");
	printf("NEG: %d\n", neg);
	printf("ZERO: %d\n", zer);
	printf("CARRY: %d\n", carry);
	printf("OVERFLOW: %d\n", overflow);
}

void lcl(Operacao2 operacao2operando){
	printf("LOAD CONSTANTE MENOS SIGNIFICATIVOS\n");
	int rc;
	int constan;

	rc = operacao2operando->rc;
	constan = operacao2operando->end;

	bancoRegistradores[rc] = constan | (rc & 0xffff0000);
	printf("REGISTRADOR %d POSSUI %d\n", rc, bancoRegistradores[rc]);
	printf("NENHUMA FLAG AFETADA\n");
}


void sub(Operacao3 operacao3operandos){
	printf("SUB\n");
	int rc, rb, ra;
	ra = operacao3operandos->ra;
	rb = operacao3operandos->rb;
	rc = operacao3operandos->rc;

	printf("RA = %d\n", ra);
	printf("RB = %d\n", rb);
	printf("RC = %d\n", rc);
	bancoRegistradores[rc] = bancoRegistradores[ra] - bancoRegistradores[rb];
	printf("REGISTRADOR %d POSSUI %d\n", rc, bancoRegistradores[rc]);
	if(bancoRegistradores[rc]==0)
		zer=1;
	if(bancoRegistradores[rc]<0)
		neg = 1;
	if((bancoRegistradores[ra]>>31 & 1) && (bancoRegistradores[rb]>>31 & 1))
		carry=1;
	else{
		if(((bancoRegistradores[ra]>>31 & 1)==0 && (bancoRegistradores[rb]>>31 & 1)==1 && (bancoRegistradores[rc]>>31&1)==0) 
			|| ((bancoRegistradores[ra]>>31 & 1)==1 && (bancoRegistradores[rb]>>31 & 1)==0 && (bancoRegistradores[rc]>>31&1)==0))
			carry = 1;
	}
	if((bancoRegistradores[rc]<bancoRegistradores[ra]) != (bancoRegistradores[rb]>0))
		overflow = 1;
	printf("HÁ FLAGS AFETADAS.\nVALORES DAS FLAGS:\n");
	printf("NEG: %d\n", neg);
	printf("ZERO: %d\n", zer);
	printf("CARRY: %d\n", carry);
	printf("OVERFLOW: %d\n", overflow);
}


void zero(Operacao3 operacao3operandos){
	printf("Zera\n");
	int rc;
	rc = operacao3operandos->rc;
	printf("RC = %d\n", rc);
	bancoRegistradores[rc] = 0;
	printf("REGISTRADOR %d POSSUI %d\n", rc, bancoRegistradores[rc]);
	printf("HÁ FLAGS AFETADAS.\nVALORES DAS FLAGS:\n");
	printf("NEG: 0\n");
	printf("ZERO: 1\n");
	printf("CARRY: 0\n");
	printf("OVERFLOW: 0\n");

}



void xor(Operacao3 operacao3operandos){
	printf("XOR\n");
	int rc, rb, ra;
	ra = operacao3operandos->ra;
	rb = operacao3operandos->rb;
	rc = operacao3operandos->rc;

	printf("RA = %d\n", ra);
	printf("RB = %d\n", rb);
	printf("RC = %d\n", rc);
	bancoRegistradores[rc] = bancoRegistradores[rb]^bancoRegistradores[ra];
	printf("REGISTRADOR %d POSSUI %d\n", rc, bancoRegistradores[rc]);
	if(bancoRegistradores[rc]==0)
		zer=1;
	if(bancoRegistradores[rc]<0)
		neg = 1;
	printf("HÁ FLAGS AFETADAS.\nVALORES DAS FLAGS:\n");
	printf("NEG: %d\n", neg);
	printf("ZERO: %d\n", zer);
	printf("CARRY: 0\n");
	printf("OVERFLOW: 0\n");

}



void or(Operacao3 operacao3operandos){
	printf("OR\n");
	int rc, rb, ra;
	ra = operacao3operandos->ra;
	rb = operacao3operandos->rb;
	rc = operacao3operandos->rc;

	printf("RA = %d\n", ra);
	printf("RB = %d\n", rb);
	printf("RC = %d\n", rc);
	bancoRegistradores[rc] = bancoRegistradores[rb]|bancoRegistradores[ra];
	printf("REGISTRADOR %d POSSUI %d\n", rc, bancoRegistradores[rc]);
	if(bancoRegistradores[rc]==0)
		zer=1;
	if(bancoRegistradores[rc]<0)
		neg = 1;
	printf("HÁ FLAGS AFETADAS.\nVALORES DAS FLAGS:\n");
	printf("NEG: %d\n", neg);
	printf("ZERO: %d\n", zer);
	printf("CARRY: 0\n");
	printf("OVERFLOW: 0\n");

}


void not(Operacao3 operacao3operandos){
	printf("NOT\n");
	int rc, rb, ra;
	ra = operacao3operandos->ra;
	rb = operacao3operandos->rb;
	rc = operacao3operandos->rc;

	printf("RA = %d\n", ra);
	printf("RB = %d\n", rb);
	printf("RC = %d\n", rc);
	bancoRegistradores[rc] = ~bancoRegistradores[ra];
	printf("REGISTRADOR %d POSSUI %d\n", rc, bancoRegistradores[rc]);
	if(bancoRegistradores[rc]==0)
		zer=1;
	if(bancoRegistradores[rc]<0)
		neg = 1;
	printf("HÁ FLAGS AFETADAS.\nVALORES DAS FLAGS:\n");
	printf("NEG: %d\n", neg);
	printf("ZERO: %d\n", zer);
	printf("CARRY: 0\n");
	printf("OVERFLOW: 0\n");

}

void and(Operacao3 operacao3operandos){
	printf("AND\n");
	int rc, rb, ra;
	ra = operacao3operandos->ra;
	rb = operacao3operandos->rb;
	rc = operacao3operandos->rc;

	printf("RA = %d\n", ra);
	printf("RB = %d\n", rb);
	printf("RC = %d\n", rc);
	bancoRegistradores[rc] = bancoRegistradores[rb]&bancoRegistradores[ra];
	printf("REGISTRADOR %d POSSUI %d\n", rc, bancoRegistradores[rc]);
	if(bancoRegistradores[rc]==0)
		zer=1;
	if(bancoRegistradores[rc]<0)
		neg = 1;
	printf("HÁ FLAGS AFETADAS.\nVALORES DAS FLAGS:\n");
	printf("NEG: %d\n", neg);
	printf("ZERO: %d\n", zer);
	printf("CARRY: 0\n");
	printf("OVERFLOW: 0\n");

}

void asl(Operacao3 operacao3operandos){
	printf("SHIFT ARITMÉTICO PARA A ESQUERDA\n");
	int rc, rb, ra;
	ra = operacao3operandos->ra;
	rb = operacao3operandos->rb;
	rc = operacao3operandos->rc;

	printf("RA = %d\n", ra);
	printf("RB = %d\n", rb);
	printf("RC = %d\n", rc);
	bancoRegistradores[rc] = bancoRegistradores[ra]<<bancoRegistradores[rb];
	printf("REGISTRADOR %d POSSUI %d\n", rc, bancoRegistradores[rc]);

}


void asr(Operacao3 operacao3operandos){
	printf("SHIFT ARITMÉTICO PARA A DIREITA\n");
	int rc, rb, ra;
	ra = operacao3operandos->ra;
	rb = operacao3operandos->rb;
	rc = operacao3operandos->rc;

	printf("RA = %d\n", ra);
	printf("RB = %d\n", rb);
	printf("RC = %d\n", rc);
	bancoRegistradores[rc] = bancoRegistradores[ra]>>bancoRegistradores[rb];
	printf("REGISTRADOR %d POSSUI %d\n", rc, bancoRegistradores[rc]);
	if(bancoRegistradores[rc]==0)
		zer=1;
	if(bancoRegistradores[rc]<0)
		neg = 1;
	printf("HÁ FLAGS AFETADAS.\nVALORES DAS FLAGS:\n");
	printf("NEG: %d\n", neg);
	printf("ZERO: %d\n", zer);
	printf("CARRY: 0\n");
	printf("OVERFLOW: 0\n");

}


void lsl(Operacao3 operacao3operandos){
	printf("SHIFT LÓGICO PARA A ESQUERDA\n");
	int rc, rb, ra;
	ra = operacao3operandos->ra;
	rb = operacao3operandos->rb;
	rc = operacao3operandos->rc;

	printf("RA = %d\n", ra);
	printf("RB = %d\n", rb);
	printf("RC = %d\n", rc);
	bancoRegistradores[rc] = (unsigned int)bancoRegistradores[ra]<<(unsigned int)bancoRegistradores[rb];
	printf("REGISTRADOR %d POSSUI %d\n", rc, bancoRegistradores[rc]);
	if(bancoRegistradores[rc]==0)
		zer=1;
	if(bancoRegistradores[rc]<0)
		neg = 1;
	printf("HÁ FLAGS AFETADAS.\nVALORES DAS FLAGS:\n");
	printf("NEG: %d\n", neg);
	printf("ZERO: %d\n", zer);
	printf("CARRY: 0\n");
	printf("OVERFLOW: 0\n");

}


void lsr(Operacao3 operacao3operandos){
	printf("SHIFT LÓGICO PARA A DIREITA\n");
	int rc, rb, ra;
	ra = operacao3operandos->ra;
	rb = operacao3operandos->rb;
	rc = operacao3operandos->rc;

	printf("RA = %d\n", ra);
	printf("RB = %d\n", rb);
	printf("RC = %d\n", rc);
	bancoRegistradores[rc] = (unsigned int)bancoRegistradores[ra]>>(unsigned int)bancoRegistradores[rb];
	printf("REGISTRADOR %d POSSUI %d\n", rc, bancoRegistradores[rc]);
	if(bancoRegistradores[rc]==0)
		zer=1;
	if(bancoRegistradores[rc]<0)
		neg = 1;
	printf("HÁ FLAGS AFETADAS.\nVALORES DAS FLAGS:\n");
	printf("NEG: %d\n", neg);
	printf("ZERO: %d\n", zer);
	printf("CARRY: 0\n");
	printf("OVERFLOW: 0\n");

}

void copia(Operacao3 operacao3operandos){
	printf("COPIA\n");
	int rc, ra;
	ra = operacao3operandos->ra;
	rc = operacao3operandos->rc;

	printf("RA = %d\n", ra);
	printf("RC = %d\n", rc);
	bancoRegistradores[rc] = bancoRegistradores[ra];
	printf("REGISTRADOR %d POSSUI %d\n", rc, bancoRegistradores[rc]);
	if(bancoRegistradores[rc]==0)
		zer=1;
	if(bancoRegistradores[rc]<0)
		neg = 1;
	printf("HÁ FLAGS AFETADAS.\nVALORES DAS FLAGS:\n");
	printf("NEG: %d\n", neg);
	printf("ZERO: %d\n", zer);
	printf("CARRY: 0\n");
	printf("OVERFLOW: 0\n");

}

void lch(Operacao2 operacao2operando){
	printf("LOAD CONSTANTE MAIS SIGNIFICATIVOS\n");
	int rc;
	int constan;

	rc = operacao2operando->rc;
	constan = operacao2operando->end;

	bancoRegistradores[rc] = ( constan << 16) | (rc & 0x0000ffff);
	printf("REGISTRADOR %d POSSUI %d\n", rc, bancoRegistradores[rc]);
	printf("NENHUMA FLAG AFETADA\n");
}


void store(Operacao3 operacao3operandos){
	printf("STORE\n");
	int rc, ra;
	ra = operacao3operandos->ra;
	rc = operacao3operandos->rc;

	printf("RA = %d\n", ra);
	printf("RC = %d\n", rc);
	memoria[bancoRegistradores[rc]] = bancoRegistradores[ra];
	printf("REGISTRADOR %d POSSUI %d\n", rc, bancoRegistradores[rc]);
	printf("NENHUMA FLAG AFETADA\n");

}

void load(Operacao3 operacao3operandos){
	printf("LOAD\n");
	int rc, ra;
	ra = operacao3operandos->ra;
	rc = operacao3operandos->rc;

	printf("RA = %d\n", ra);
	printf("RC = %d\n", rc);
	bancoRegistradores[rc] = memoria[bancoRegistradores[ra]];
	printf("REGISTRADOR %d POSSUI %d\n", rc, bancoRegistradores[rc]);
	printf("NENHUMA FLAG AFETADA\n");
}



 void jal(Operacao4 operacao4operandos, int *PC){
	printf("JUMP AND LINK\n"); 
	bancoRegistradores[31] = *PC-1;
	*PC =  operacao4operandos->end;
	printf("REGISTRADOR 31 POSSUI %d\n",bancoRegistradores[31]);
	printf("PROGRAM COUNTER AGORA POSSUI %d\n", *PC);

}


void jr(Operacao3 operacao3operandos, int *PC){
	printf("JUMP REGISTER\n");
	int rc; 
	rc = operacao3operandos->rc;
	*PC = bancoRegistradores[rc];
	printf("RC = 31\n");
	printf("PROGRAM COUNT POSSUI %d\n", *PC);
	printf("NENHUMA FLAG AFETADA\n");

}

void beq(Operacao3 operacao3operandos, int *PC){
	printf("BRANCH EQUAL\n");
	int end, rb, ra;
	ra = operacao3operandos->ra;
	rb = operacao3operandos->rb;
	end = operacao3operandos->rc;

	printf("RA = %d\n", ra);
	printf("RB = %d\n", rb);
	printf("END = %d\n", end);
	
	if(bancoRegistradores[ra]==bancoRegistradores[rb])
	*PC = end;
	printf("PROGRAM COUNT POSSUI %d\n", *PC);
	printf("NENHUMA FLAG AFETADA\n");

}

void bne(Operacao3 operacao3operandos, int *PC){
	printf("BRANCH NOT EQUAL\n");
	int end, rb, ra;
	ra = operacao3operandos->ra;
	rb = operacao3operandos->rb;
	end = operacao3operandos->rc;

	printf("RA = %d\n", ra);
	printf("RB = %d\n", rb);
	printf("END = %d\n", end);
	if(bancoRegistradores[ra]!=bancoRegistradores[rb])
	*PC = end;
	printf("PROGRAM COUNT POSSUI %d\n", *PC);
	printf("NENHUMA FLAG AFETADA\n");

}

void j(Operacao4 operacao4operandos, int *PC){
	printf("JUMP INCONDICIONAL\n"); 
	*PC =  operacao4operandos->end;
	printf("PROGRAM COUNTER AGORA POSSUI %d\n", *PC);
	printf("NENHUMA FLAG AFETADA\n");
}

void senzero(Operacao3 operacao3operandos, int *PC){
	/* Decrementa o dado presente no registrador ou o dado na posição de memória diretamente endereçada e
desvia se o resultado da operação for diferente de zero, sem afetar quaisquer flags.*/
	printf("SE ZERO\n");
	int end, ra;
	ra = operacao3operandos->ra;
	end = operacao3operandos->rc;

	printf("RA = %d\n", ra);
	printf("END = %d\n", end);
	bancoRegistradores[ra]--;
	if(bancoRegistradores[ra]!=0)
	*PC = end;
	printf("PROGRAM COUNT POSSUI %d\n", *PC);
	printf("NENHUMA FLAG AFETADA\n");

}


void mult(Operacao3 operacao3operandos){
	printf("MULTIPLICAÇÃO\n");
	int rc, rb, ra;
	ra = operacao3operandos->ra;
	rb = operacao3operandos->rb;
	rc = operacao3operandos->rc;

	printf("RA = %d\n", ra);
	printf("RB = %d\n", rb);
	printf("RC = %d\n", rc);
	bancoRegistradores[rc] = bancoRegistradores[ra] * bancoRegistradores[rb];
	printf("REGISTRADOR %d POSSUI %d\n", rc, bancoRegistradores[rc]);
	if(bancoRegistradores[rc]==0)
		zer=1;
	if(bancoRegistradores[rc]<0)
		neg = 1;
	if((bancoRegistradores[ra]>>31 & 1) && (bancoRegistradores[rb]>>31 & 1))
		carry=1;
	else{
		if(((bancoRegistradores[ra]>>31 & 1)==0 && (bancoRegistradores[rb]>>31 & 1)==1 && (bancoRegistradores[rc]>>31&1)==0) 
			|| ((bancoRegistradores[ra]>>31 & 1)==1 && (bancoRegistradores[rb]>>31 & 1)==0 && (bancoRegistradores[rc]>>31&1)==0))
			carry = 1;
	}
	if(bancoRegistradores[ra]>0 && bancoRegistradores[rb]>0 && bancoRegistradores[rc]<0)
		overflow = 1;
	printf("HÁ FLAGS AFETADAS.\nVALORES DAS FLAGS:\n");
	printf("NEG: %d\n", neg);
	printf("ZERO: %d\n", zer);
	printf("CARRY: %d\n", carry);
	printf("OVERFLOW: %d\n", overflow);

}

void divisao(Operacao3 operacao3operandos){
	printf("DIVISÃO\n");
	int rc, rb, ra;
	ra = operacao3operandos->ra;
	rb = operacao3operandos->rb;
	rc = operacao3operandos->rc;

	printf("RA = %d\n", ra);
	printf("RB = %d\n", rb);
	printf("RC = %d\n", rc);
	bancoRegistradores[rc] = bancoRegistradores[ra] / bancoRegistradores[rb];
	printf("REGISTRADOR %d POSSUI %d\n", rc, bancoRegistradores[rc]);
	if(bancoRegistradores[rc]==0)
		zer=1;
	if(bancoRegistradores[rc]<0)
		neg = 1;
	if((bancoRegistradores[ra]>>31 & 1) && (bancoRegistradores[rb]>>31 & 1))
		carry=1;
	else{
		if(((bancoRegistradores[ra]>>31 & 1)==0 && (bancoRegistradores[rb]>>31 & 1)==1 && (bancoRegistradores[rc]>>31&1)==0) 
			|| ((bancoRegistradores[ra]>>31 & 1)==1 && (bancoRegistradores[rb]>>31 & 1)==0 && (bancoRegistradores[rc]>>31&1)==0))
			carry = 1;
	}
	if(bancoRegistradores[ra]>0 && bancoRegistradores[rb]>0 && bancoRegistradores[rc]<0)
		overflow = 1;
	printf("HÁ FLAGS AFETADAS.\nVALORES DAS FLAGS:\n");
	printf("NEG: %d\n", neg);
	printf("ZERO: %d\n", zer);
	printf("CARRY: %d\n", carry);
	printf("OVERFLOW: %d\n", overflow);

}


void exponenciacao(Operacao3 operacao3operandos){
	printf("EXPONENCIAÇÃO\n");
	int rc, rb, ra;
	ra = operacao3operandos->ra;
	rb = operacao3operandos->rb;
	rc = operacao3operandos->rc;

	printf("RA = %d\n", ra);
	printf("RB = %d\n", rb);
	printf("RC = %d\n", rc);
	bancoRegistradores[rc] = pow(bancoRegistradores[ra],bancoRegistradores[rb]);
	printf("REGISTRADOR %d POSSUI %d\n", rc, bancoRegistradores[rc]);
	if(bancoRegistradores[rc]==0)
		zer=1;
	if(bancoRegistradores[rc]<0)
		neg = 1;
	if(bancoRegistradores[ra]>0 && bancoRegistradores[rb]>0 && bancoRegistradores[rc]<0)
		overflow = 1;
	printf("HÁ FLAGS AFETADAS.\nVALORES DAS FLAGS:\n");
	printf("NEG: %d\n", neg);
	printf("ZERO: %d\n", zer);
	printf("OVERFLOW: %d\n", overflow);

}

void soma_imediata(Operacao3 operacao3operandos){
	printf("SOMA IMEDIATA\n");
	int rc, valor1, valor2;
	valor1 = operacao3operandos->ra;
	valor2 = operacao3operandos->rb;
	rc = operacao3operandos->rc;

	printf("PRIMEIRO VALOR = %d\n", valor1);
	printf("SEGUNDO VALOR = %d\n", valor2);
	printf("RC = %d\n", rc);
	bancoRegistradores[rc] = valor1+valor2;
	printf("REGISTRADOR %d POSSUI %d\n", rc, bancoRegistradores[rc]);
	if(bancoRegistradores[rc]==0)
		zer=1;
	if(bancoRegistradores[rc]<0)
		neg = 1;
	if((valor1>>31 & 1) && (valor2>>31 & 1))
		carry=1;
	else{
		if(((valor1>>31 & 1)==0 && (valor2>>31 & 1)==1 && (bancoRegistradores[rc]>>31&1)==0) 
			|| ((valor1>>31 & 1)==1 && (valor2>>31 & 1)==0 && (bancoRegistradores[rc]>>31&1)==0))
			carry = 1;
	}
	if(valor1>0 && valor2>0 && bancoRegistradores[rc]<0)
		overflow = 1;
	printf("HÁ FLAGS AFETADAS.\nVALORES DAS FLAGS:\n");
	printf("NEG: %d\n", neg);
	printf("ZERO: %d\n", zer);
	printf("CARRY: %d\n", carry);
	printf("OVERFLOW: %d\n", overflow);

}

void sub_imediato(Operacao3 operacao3operandos){
	printf("SUBTRAÇÃO IMEDIATA\n");
	int rc, valor1, valor2;
	valor1 = operacao3operandos->ra;
	valor2 = operacao3operandos->rb;
	rc = operacao3operandos->rc;

	printf("PRIMEIRO VALOR = %d\n", valor1);
	printf("SEGUNDO VALOR = %d\n", valor2);
	printf("RC = %d\n", rc);
	bancoRegistradores[rc] = valor1-valor2;
	printf("REGISTRADOR %d POSSUI %d\n", rc, bancoRegistradores[rc]);
	if(bancoRegistradores[rc]==0)
		zer=1;
	if(bancoRegistradores[rc]<0)
		neg = 1;
	if((valor1>>31 & 1) && (valor2>>31 & 1))
		carry=1;
	else{
		if(((valor1>>31 & 1)==0 && (valor2>>31 & 1)==1 && (bancoRegistradores[rc]>>31&1)==0) 
			|| ((valor1>>31 & 1)==1 && (valor2>>31 & 1)==0 && (bancoRegistradores[rc]>>31&1)==0))
			carry = 1;
	}
	if((bancoRegistradores[rc]<valor1) != (valor2>0))
		overflow = 1;
	printf("HÁ FLAGS AFETADAS.\nVALORES DAS FLAGS:\n");
	printf("NEG: %d\n", neg);
	printf("ZERO: %d\n", zer);
	printf("CARRY: %d\n", carry);
	printf("OVERFLOW: %d\n", overflow);

}


void inc(Operacao3 operacao3operandos){
	printf("INCREMENTA\n");
	int rc, num;
	rc = operacao3operandos->rc;
	num = bancoRegistradores[rc];
	printf("RC = %d\n", rc);
	bancoRegistradores[rc]++;
	printf("REGISTRADOR %d POSSUI %d\n", rc, bancoRegistradores[rc]);
	if(bancoRegistradores[rc]==0)
		zer=1;
	if(bancoRegistradores[rc]<0)
		neg = 1;
	if((bancoRegistradores[rc]>>31 & 1) && (1>>31 & 1))
		carry=1;
	if(num>0 && bancoRegistradores[rc]<0)
		overflow = 1;
	printf("HÁ FLAGS AFETADAS.\nVALORES DAS FLAGS:\n");
	printf("NEG: %d\n", neg);
	printf("ZERO: %d\n", zer);
	printf("CARRY: %d\n", carry);
	printf("OVERFLOW: %d\n", overflow);
}


void dec(Operacao3 operacao3operandos){
	printf("DECREMENTA\n");
	int rc, num;
	rc = operacao3operandos->rc;
	printf("RC = %d\n", rc);
	num = bancoRegistradores[rc];
	bancoRegistradores[rc] = bancoRegistradores[rc]-1;
	printf("REGISTRADOR %d POSSUI %d\n", rc, bancoRegistradores[rc]);
	if(bancoRegistradores[rc]==0)
		zer=1;
	if(bancoRegistradores[rc]<0)
		neg = 1;
	if((bancoRegistradores[rc]>>31 & 1) && (1>>31 & 1))
		carry=1;
	if((bancoRegistradores[rc]<num) != (1>0))
		overflow = 1;
	printf("HÁ FLAGS AFETADAS.\nVALORES DAS FLAGS:\n");
	printf("NEG: %d\n", neg);
	printf("ZERO: %d\n", zer);
	printf("CARRY: %d\n",carry);
	printf("OVERFLOW: %d\n", overflow);
}


