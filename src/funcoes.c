#include <stdlib.h>
#include <stdio.h>


// Função para converter o ano que vem em string para int, notar que vem algo de gênero "2015-03-24T08:17:09.823"
int getYear (unsigned char* data) {
	int i=0;
	char *teste = malloc(sizeof(char));
	for (i=0;i<4;i++) {
		teste[i]=data[i];
		
	}

	int resultado = atoi(teste);
	return resultado;
}

// Função para converter o mês que vem em string para int, notar que vem algo de gênero "2015-03-24T08:17:09.823"
int getMonth (unsigned char* data) {
	int i=0;
	char *teste = malloc(sizeof(char));
	int j=0;
	
	for (i=0;i<8;i++)  {
		if (i==6 || i==5) teste[j++]=data[i];
	}
	
	
	int resultado = atoi(teste);
	
	return resultado;
}
// Função para converter o dia que vem em string para int, notar que vem algo de gênero "2015-03-24T08:17:09.823"
int getDay (unsigned char* data) {
	int i=0;
	char *teste = malloc(sizeof(char));
	int j=0;
	
	for (i=0;i<10;i++)  {
		if (i==8 || i==9) teste[j++]=data[i];
	}
	
	
	int resultado = atoi(teste);
	
	return resultado;
}
// Função que vai comparar a tag que quero com todas as tags existentes na linha
int comparaTag (char *tag, unsigned char *string) {

	
	int i = 0; int j=0; int achou = 0;
	
	for (i=0; string[i]!='\0' && achou==0; i++) {

		for (j=0;tag[j]!='\0' && toupper(tag[j])==toupper(string[i]);j++){
			i++;
		}
		if (tag[j]=='\0' && (string[i]=='>') ) achou=1;
		
	}


	return achou;
}
// Função que verifica se as duas funções são iguais
int verificaTags (unsigned char* tag, char* tag2) {
	int i = 0;
	int j = 0;

	for (i=0;tag[i]!='\0';i++) {
		if (tag[i]==tag2[j]) {
			for (j=0;tag2[j]!='\0';j++) printf ("%c",tag2[j]);
		}
	}
	if (tag2[j]=='\0') return 1;

	return 0;

}

// Função que vai comparar a palavra que quero no titulo
int comparaTitulo (unsigned char* titulo, char* palavra) {

	int i = 0;
	int j = 0;
 

	for (i=0;titulo[i]!='\0';i++) {
		for (j=0;palavra[j]!='\0' && palavra[j]==titulo[i];i++,j++);
		if (palavra[j]=='\0') return 1;
	}
 

	return 0;
}