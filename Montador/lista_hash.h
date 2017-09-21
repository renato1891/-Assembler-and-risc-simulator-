//Nome: Renato Borges Boaventura
//matricula: 0021620
//data 10/10/2016
#ifndef _lista_hash_
#define _lista_hash_
typedef struct nodoh *Nodoh;
typedef struct listah *Listah;
extern Listah cria_listah(void);
extern void insere_listah(Listah p, char *palavra, int pc);
extern void destroi_listah(Listah p);
extern void apaga_pos_listah(Listah p, int pos);
extern int retorna_elemento(Listah p, char *palavra);
#endif