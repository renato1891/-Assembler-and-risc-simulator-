//Nome: Renato Borges Boaventura
//matricula: 0021620
//data 10/10/2016

#ifndef _hash_externa_
#define _hash_externa_
typedef struct hash *Hash;
extern Hash cria_hash(void);
extern void insere_hash(Hash p, char *palavra, int pc);
extern int funcao1(Hash p, char  *chave); // função do N%M, em que N é a chave e M é o tamanho total
extern int decodifica(Hash p, char *palavra);
extern void destroi_hash(Hash p);
extern void insere_linha(Hash p, char *palavra,int linha);
extern int compara_palavras(char *palavra1, char *palavra2);
extern int retorna_pc(Hash p, char *palavra);
#endif



