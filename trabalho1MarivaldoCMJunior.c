#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NTABHASH 11


typedef struct noTraducao{
	char traducao[50];
	struct noTraducao *proxTrad;
}NoTraducao, *Traducoes;

typedef struct noPalavra{
	char palavra[30];
	char classe;
	int contAcessos;
	NoTraducao *trad;
	struct noPalavra *ant;
	struct noPalavra *prox;
}NoPalavra, *Palavras;




void inicializaPalavras(Palavras *p){
	*p = NULL;
}

void inicializaTraducoes(Traducoes *t){
	*t = NULL;
}

int ord(char *s){
	int soma=0;
	int i;
	
	for(i=0;i<strlen(s);i++){
		switch(s[i]){
			case 'a':
				soma = soma +1;
				break;
			case 'b':
				soma = soma +2;
				break;
			case 'c':
				soma = soma +3;
				break;
			case 'd':
				soma = soma +4;
				break;
			case 'e':
				soma = soma +5;
				break;
			case 'f':
				soma = soma +6;
				break;
			case 'g':
				soma = soma +7;
				break;
			case 'h':
				soma = soma +8;
				break;
			case 'i':
				soma = soma +9;
				break;
			case 'j':
				soma = soma +10;
				break;
			case 'k':
				soma = soma +11;
				break;
			case 'l':
				soma = soma +12;
				break;
			case 'm':
				soma = soma +13;
				break;
			case 'n':
				soma = soma +14;
				break;
			case 'o':
				soma = soma +15;
				break;
			case 'p':
				soma = soma +16;
				break;
			case 'q':
				soma = soma +17;
				break;
			case 'r':
				soma = soma +18;
				break;
			case 's':
				soma = soma +19;
				break;
			case 't':
				soma = soma +20;
				break;
			case 'u':
				soma = soma +21;
				break;
			case 'v':
				soma = soma +22;
				break;
			case 'w':
				soma = soma +23;
				break;
			case 'x':
				soma = soma +24;
				break;
			case 'y':
				soma = soma +25;
				break;
			case 'z':
				soma = soma +26;
				break;
		}
	}
	return soma;
}




void ordenaLista(Palavras *p){
		
	NoPalavra *aux,*aux2;
	Traducoes tradAux;
	
	char sTemp[30];
	int contTemp;
	char classAux;
	
	for(aux=*p;(aux);aux=aux->prox){
		for(aux2=aux->prox;(aux2);aux2=aux2->prox){
			if(aux->contAcessos < aux2->contAcessos){
				
				contTemp = aux2->contAcessos;
				aux2->contAcessos = aux->contAcessos;
				aux->contAcessos = contTemp;
				
				strcpy(sTemp, aux2->palavra);
				strcpy(aux2->palavra,aux->palavra);
				strcpy(aux->palavra, sTemp);
				
				classAux = aux2->classe;
				aux2->classe = aux->classe;
				aux->classe = classAux;
				
				tradAux = aux2->trad;
				aux2->trad = aux->trad;
				aux->trad = tradAux;
			}
		}
	}
	
}

bool insereTraducao(Traducoes *l, char t[50]){
	NoTraducao *nova;
	
	if(!(nova=(NoTraducao*)malloc(sizeof(NoTraducao))))
		return false;
	
	
	nova->proxTrad= *l;
	strcpy(nova->traducao, t);
	*l = nova;
	return true;
}



bool inserePalavra(Palavras *l, char s[30], char tp, int qtdT){
	NoPalavra *nova;
	

	char tr[50];
	int i;
	
	if(!(nova=(NoPalavra *)malloc(sizeof(NoPalavra))))
		return false;
	
	
	if(*l)
		(*l)->ant = nova;
		
	nova->prox = *l;
	nova->trad = NULL;
	nova->ant = NULL;
	nova->classe = tp;
	nova->contAcessos = 0;
	strcpy(nova->palavra,s);
	*l = nova;
	
	for(i=0;i<qtdT;i++){
		scanf(" %[^\n]s",tr);
		insereTraducao(&nova->trad,tr);
	}
	ordenaLista(l);
	return true;
	
}


void listaTraducoes(Palavras *l, char pa[30]){
	NoPalavra *p;
	NoTraducao *t;
	
	for(p = *l;(p)&&(strcmp(p->palavra, pa)!=0);p = p->prox);
	if(p){
		p->contAcessos ++;
		for(t = p->trad;(t);t=t->proxTrad)
			printf("%s\n", t->traducao);
	}
}

void consultaDados(Palavras *l, char pa[30]){
	NoPalavra *p;
	
	for(p = *l;(p)&&(strcmp(p->palavra, pa)!=0);p = p->prox);
	if(p){
		if(p->classe=='s')
			printf("substantivo %d\n", p->contAcessos);
		else if(p->classe == 'a')
			printf("adjetivo %d\n", p->contAcessos);
		else if(p->classe == 'v')
			printf("verbo %d\n", p->contAcessos);
	}
}


void listaPalavrasIndice(Palavras *l){
	NoPalavra *p;
		
	for(p = *l;(p);p = p->prox){
		printf("%s\n", p->palavra);
	}
}


void consultaPorClasse(Palavras *l, char c){
	NoPalavra *p;
	for(p=*l;(p);p=p->prox)
		if(p->classe == c)
			printf("%s\n",p->palavra);
}

bool insereListaAuxiliar(Palavras *p, char s[30]){
	NoPalavra *novo;
	NoPalavra *aux;
	//NoPalavra *aux2;
	if(!(novo = (NoPalavra*)malloc(sizeof(NoPalavra)))){
			return false;
	}
	
	strcpy(novo->palavra,s);
	
	//se inserir no começo
	aux = *p;
	
	if(!*p){
		novo->prox=NULL;
		novo->ant = NULL;
		*p=novo;
		return true;
	}
	
	if((strcmp(s,aux->palavra)<=0) ){
		novo->prox = *p;
		novo->ant=NULL;
		*p = novo;
		return true;
	}
	
	for(aux=*p;(aux->prox)&&(strcmp(s,aux->prox->palavra)>0);aux=aux->prox);
	
	if(aux->prox){		
		novo->prox = aux->prox;
		aux->prox->ant=novo;
		aux->prox = novo;
		novo->trad = NULL;
		novo->ant = aux;
		return true;
	}
	novo->prox = NULL;
	novo->ant = aux;
	aux->prox = novo;
	return true;
}


void apagarListaTrad(Traducoes *l){
	NoTraducao *p;
	
	for(p=*l;(p);p=p->proxTrad){
		*l = p->proxTrad;
		free(p);
	}
}

void listaCrescente(Palavras *l){
	NoPalavra *p;
	
	for(p = *l;(p);p=p->prox)
		printf("%s\n",p->palavra);
}


void listaDecrescente(Palavras *l){
	NoPalavra *p;
	NoPalavra *pAux;
	
	for(p=*l;(p);pAux=p, p=p->prox);
	for(p = pAux;(p);p = p->ant)
		printf("%s\n",p->palavra);
}

void removerPalavra(Palavras *l, char s[30]){
	NoPalavra *p;
	
	for(p=*l;(p)&&(strcmp(p->palavra, s));p=p->prox);
	
	apagarListaTrad(&p->trad);
	
	if(p){
		if(p->prox)
			p->prox->ant = p->ant;
		if(p->ant)
			p->ant->prox = p->prox;
		else
			*l = p->prox;
			
		free(p);
	}
}


	


int main(){
	
	Palavras vetorListas[NTABHASH];
	
	Palavras listaOrdenada;
	
	int qtdTrad;
	int i;
	int indice;
	int qtd;

	char op;
	char palavra[30];
	char tipo;
	char ordem;
	
	//inicia a lista de cada posiçao do vetor
	for(i = 0;i<NTABHASH;i++){
		inicializaPalavras(&vetorListas[i]);
	}
	
	inicializaPalavras(&listaOrdenada);
	
	scanf(" %d",&qtd);
	for(i=0;i<qtd;i++){
		scanf(" %s %c %d",palavra,&tipo,&qtdTrad);
		indice = ord(palavra) % NTABHASH;
		inserePalavra(&vetorListas[indice],palavra, tipo,qtdTrad);
		insereListaAuxiliar(&listaOrdenada, palavra);
	}
	
	while(op != 'e'){
       scanf(" %c",&op);
       switch(op){	
			case 'c':	
				scanf(" %s", palavra);				
				indice = ord(palavra) % NTABHASH;
				consultaDados(&vetorListas[indice],palavra);
				break;
				
			case 't':
				scanf(" %s", palavra);
				
				indice = ord(palavra) % NTABHASH;
				listaTraducoes(&vetorListas[indice], palavra);
				ordenaLista(&vetorListas[indice]);
				break;		
			
			case 'i':
				scanf(" %d",&indice);
				ordenaLista(&vetorListas[indice]);
				listaPalavrasIndice(&vetorListas[indice]);
				break;
				
			case 'a':
				scanf(" %c", &tipo);
				
				for(i=0;i<NTABHASH;i++)
					consultaPorClasse(&vetorListas[i], tipo);
				break;
			
			case 'l':
				scanf(" %c", &ordem);
				
				if(ordem=='c'){
					listaCrescente(&listaOrdenada);
				}
				else
					listaDecrescente(&listaOrdenada);
				break;
				
			case 'r':
				scanf(" %s", palavra);
				indice = ord(palavra) % NTABHASH;
				removerPalavra(&vetorListas[indice], palavra);
				removerPalavra(&listaOrdenada, palavra);
				break;
		}
		
       
    }
	
	return 0;
}
