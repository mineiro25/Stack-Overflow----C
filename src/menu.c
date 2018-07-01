#include <date.h>
#include <stdlib.h>
#include <stdio.h>	 
#include <libxml/parser.h>
#include <interface.h>
#include <string.h>

// Estrutura dos professores
struct llist {
  int size;
  long * list;
}; 

struct date {
  int day;
  int month;
  int year;
};

// Estrutura de posts
typedef struct node {
	unsigned long id;
        unsigned char* title;
        unsigned long userID;
        unsigned long tipo;
        unsigned char* data;
        unsigned char* tag;
        unsigned long numAnswers;
        unsigned long numComments;
        unsigned long parentID;
        unsigned long score;
        struct node *next;

}*head;

// Estrutura de comentários
typedef struct comments {
		unsigned long id;
        unsigned long userID;
        unsigned char* data;
        unsigned long postID;
        unsigned long score;
        unsigned char* text;
        struct comments *next;
}*respostas;

// Estrutura de users
typedef struct informacao {
	unsigned long id;
	char *nome;
	unsigned long posts;
	char *bio;
	unsigned long reputacao;
	struct informacao *next;
}*usuario;

// Estrutura principal
typedef struct TCD_community{
	head posts;
	usuario users;
	respostas comentarios;
}*TAD_community;	

// Função que vai implementar o menu no terminal
void menu (const char *directoria) {
		TAD_community novo = init();   int op =0; int id; char tag[90000]; int N; char palavra[90000]; int id2;
		
		Date inicio; Date fim; int dia, mes, ano;
    
		novo=load(novo,directoria);
	printf ("Ficheiros carregados. Vamos agora carregar a estrutura! Por favor aguarde...\n");
		do {
 
        
 
    
        printf ("Bem-vindo ao programa de LABORATÓRIOS DE INFORMÁTICA!\n");
        printf ("********************************************************\n");
        printf ("************************* MENU *************************\n");
        printf ("********************************************************\n");
        printf (" 1 - Informação sobre um post \n 2 - Top N de utilizadores com maior nº de posts de sempre \n");
        printf (" 3 - Numero total de posts durante um intervalo de tempo\n 4 - Procurar perguntas por tag\n 5 - Informação sobre utilizador\n 6 - Respostas com mais votos durante um intervalo de tempo\n");
        printf (" 7 - Respostas com mais respostas durante um intervalo de tempo\n 8 - Dado uma palavra, procurar por N titulos que contenham a palavra q\n 9 - Dado dois IDs de dois utilizadores, procurar por N perguntas em que ambos participaram\n");
        printf (" 10 - Dado um ID de uma pergunta, obter a melhor resposta\n 11 - Dado um intervalo arbitrario de tempo, devolver as N tags mais usadas pelos N utilizadores\n");
        printf (" 0 - SAIR\n");
        //printf ("********************************************************\n");
        printf ("********************************************************\n");
        printf ("Introduza a opção desejada: ");



        scanf ("%d",&op);
        switch (op) {
            case 1:
                printf("Qual id do post quer procurar? ");
                scanf ("%d",&id);
                info_from_post(novo,id);
                break;
        
            case 2:
				printf ("Introduza o N: ");
				scanf("%d",&id);
                top_users(novo,id);
                break;
        

            case 3: 
				printf ("Introduza a data inicial: ");
				scanf ("%d %d %d",&dia,&mes,&ano); 
				inicio = createDate(dia,mes,ano);
				printf ("Introduza a data final: ");
				scanf ("%d %d %d",&dia,&mes,&ano); 
				fim = createDate(dia,mes,ano);
				total_posts(novo,inicio,fim);
                break;

            case 4: 
				printf ("Introduza a data inicial: ");
				scanf ("%d %d %d",&dia,&mes,&ano); 
				inicio = createDate(dia,mes,ano);
				printf ("Introduza a data final: ");
				scanf ("%d %d %d",&dia,&mes,&ano); 
				fim = createDate(dia,mes,ano);
                printf ("Introduza a tag: ");
                scanf ("%s",&tag);
				questions_with_tag(novo,tag,inicio,fim);
			 
                break;
            case 5:
                printf("Qual id do user quer procurar? ");
                scanf ("%d",&id);
                get_user_info(novo,id); 
                break;	


            case 6:
				printf ("Introduza a data inicial: ");
				scanf ("%d %d %d",&dia,&mes,&ano); 
				inicio = createDate(dia,mes,ano);
				printf ("Introduza a data final: ");
				scanf ("%d %d %d",&dia,&mes,&ano); 
				fim = createDate(dia,mes,ano);
                printf ("Introduza o N: ");
                scanf("%d",&N);
				most_voted_answers(novo,N,inicio,fim);
				break;

            case 7:
                printf ("Introduza a data inicial: ");
				scanf ("%d %d %d",&dia,&mes,&ano); 
				inicio = createDate(dia,mes,ano);
				printf ("Introduza a data final: ");
				scanf ("%d %d %d",&dia,&mes,&ano); 
				fim = createDate(dia,mes,ano);
                printf ("Introduza o N: ");
                scanf("%d",&N);
				most_answered_questions(novo,N,inicio,fim);
                break;

            case 8:
                printf ("Introduza a palavra que deseja procurar: ");
                scanf ("%s",&palavra);
                printf ("Introduza o N: ");
                scanf("%d",&N);
                contains_word(novo,palavra,N);
                break;

            case 9:
                printf ("Introduza o ID do 1º user: ");
                scanf("%d",&id);
                printf ("Introduza o ID do 2º user: ");
                scanf("%d",&id2);
                printf ("Introduza o N: ");
                scanf ("%d",&N);
                both_participated(novo,id,id2,N);
                break;
        
            case 10:
                better_answer(novo,5942);    
                break;
            case 11:
                // ainda sem nada
                printf ("Introduza a data inicial: ");
				scanf ("%d %d %d",&dia,&mes,&ano); 
				inicio = createDate(dia,mes,ano);
				printf ("Introduza a data final: ");
				scanf ("%d %d %d",&dia,&mes,&ano); 
				fim = createDate(dia,mes,ano);
				top_tag(novo,20,inicio,fim);
               
                break;
            case 0:
                // sair do programa
                break;
            default:
                printf("Opção inválida!\n");
                sleep(2);
        }
    } while (op!=0);



}
