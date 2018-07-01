#include <date.h>
#include <stdlib.h>
#include <stdio.h>	 
#include <libxml/parser.h>
#include <interface.h>
#include <string.h>

#define MAX_USERS 1000000

// Estrutura do professor
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

//Estrutura de comentarios
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


// Estrutura tag
typedef struct tagStructure {
	unsigned long id;
	unsigned char *nome;
	struct tagStructure *next;
}*tags;

// Estrutura principal
typedef struct TCD_community{
	head posts;
	usuario users;
	respostas comentarios;
}*TAD_community;	


// Funções que estão no ficheiro funcoes.c
int getMonth (unsigned char* data);
int getYear (unsigned char* data);
int getDay (unsigned char* data);
int comparaTag (char *tag, unsigned char *string);
int verificaTags (unsigned char* tag, char* tag2);
int comparaTitulo (unsigned char* titulo, char* palavra);
//Funções que estão no ficheiro posts.c
head postToStructure();
head insert(head teste, unsigned long id, unsigned char* title, unsigned long userID, unsigned long tipoPost,unsigned char* dataPost, unsigned char* tag, unsigned long numAnswers, unsigned long numComments, unsigned long parentID, unsigned long score);
int verificaTipoPost (head estrutura, long id);
int devolveParentID (head estrutura, long id);
int conta_posts (head com, unsigned long userid);

//Funções que estão no ficheiro usuarios.c
usuario insereNome(usuario teste,char *nome, unsigned long idUser, unsigned long post, char *bio, unsigned long reputacao);
usuario usersToStructure();
int contaUsers (usuario usuarios);
int reputacaoUser (usuario estrutura, unsigned long id);

//Funções que estão no ficheiro comentarios.c
respostas commentsToStructure ();
respostas insereRespostas(respostas teste, unsigned long id, unsigned char* data, unsigned long userID, unsigned long postID,unsigned long score, unsigned char *text);

//Função que está no ficheiro parser.c
int parsingDirectory (char *directoria);

//Função que está no ficheiro menu.c
void menu();

// QUERY 1 
STR_pair info_from_post(TAD_community com, long id) {
	
	STR_pair resposta = NULL;
	head estrutura = com->posts;
	usuario users = com->users;
	
	unsigned long usersid;
	char* nome = "";
	unsigned char* titulo = (unsigned char*)"";
	int tipo = verificaTipoPost(estrutura, id);
	
	if (tipo==2) {
		
		int teste = devolveParentID (estrutura,id);
		id=teste;
	}

	while (estrutura!=NULL ) {
		if (id ==estrutura->id && estrutura->tipo==1) {
			usersid = estrutura->userID;
			titulo = estrutura->title;
			break;

		}
		estrutura=estrutura->next;
	}
	while (users!=NULL) {
		if (usersid==users->id) {
	 		 
	 		nome = users->nome;
	 		break;
		}
		users = users->next;
	}
	
	printf ("Resposta: %s %s \n\n",titulo,nome);
	resposta = create_str_pair((char*)titulo,nome);
	
	return resposta;

} 

// QUERY 2
 void top_users(TAD_community com, int N) {
 
    unsigned long i;
    unsigned long nUser[N];
    int nUser_NPosts[N];
    int j;
    unsigned long u, uAnt;
    int up, upAnt;
  
	 
	 
	int nUser_Conta[MAX_USERS];

	for (i=0;i<MAX_USERS;i++){
         nUser_Conta[i]=0;
     }
 

	for (j=0;j<N;j++){
         nUser[j]=0;
         nUser_NPosts[j]=0;
     }

    while (com->posts!=NULL) {
        if (com->posts->userID>0 && (com->posts->tipo == 1 || com->posts->tipo == 2)) nUser_Conta[com->posts->userID]++;
        com->posts = com->posts->next;
    }


     for (i=0;i<MAX_USERS;i++){
            u=i;
            up=nUser_Conta[i];
            
			for (j=0 ;j< N;j++){
                if (up>nUser_NPosts[j]){
                    uAnt=nUser[j];
                    upAnt=nUser_NPosts[j];
                    nUser[j]=u;
                    nUser_NPosts[j]=up;
                    u=uAnt;
                    up=upAnt;
                }
            }
 
     }

     printf("TOP %d\n", N);
     for (j=0 ;j< N;j++){
        printf("%d: %ld \n", j,nUser[j]);
    }

}

// Query 3 
LONG_pair total_posts(TAD_community com, Date begin, Date end){
	head teste = com->posts;
	LONG_pair resultado = NULL;

	int dia;
	int mes;
	int ano;
	int contaP=0;
	int contaA=0;
	int contaO=0;
	int dataI = begin->year*10000+begin->month*100+begin->day;
	int data;
	int dataF = end->year*10000+end->month*100+end->day;
	
	while (teste!=NULL) {
		dia = getDay(teste->data);
		mes = getMonth(teste->data);
		ano = getYear(teste->data);
 		data = ano*10000+mes*100+dia;
		
		if (data>=dataI && data<=dataF) {
			if (teste->tipo==1) contaP++;
			else if (teste->tipo==2) contaA++;
				 else contaO++;
		}
 
		 teste = teste->next;
	}
	printf ("Perguntas: %d\nRespostas: %d\n", contaP, contaA);
	resultado = create_long_pair(contaP,contaA);

	return resultado;
}

//QUERY 4
LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end) {
	head posts = com->posts;
	LONG_list resultado;
	int dataI = begin->year*10000+begin->month*100+begin->day;
	int dataF = end->year*10000+end->month*100+end->day;
	int dia, mes, ano, data;
	int i = 0; unsigned long *ids = malloc(sizeof(long));


	while (posts!=NULL) {
		dia = getDay(posts->data);
		mes = getMonth(posts->data);
		ano = getYear(posts->data);
		data = ano*10000+mes*100+dia;


 		if (data>=dataI && data<=dataF) {		
	
			int condicao = comparaTag(tag,posts->tag);
			
			if (posts->tipo==1 && condicao==1) {
				ids[i] = posts->id;
				printf ("%ld\n",ids[i]);
				i++;
			}
		}


		posts = posts->next;
	}
	resultado = create_list(i);

	int j = 0;
	while (j<i) {
		set_list(resultado,j,ids[j]);
		
		j++;
	}

	return resultado;
}

// QUERY 5
USER get_user_info(TAD_community com, long id) {
	head posts = com->posts; 
	usuario user = com->users;
	
	USER resultado = NULL;

	long *array = malloc(sizeof(int)); 
	int i=0;
	
	char *biografia;

	while (user!=NULL) {
		if (user->id == id){
			biografia = user->bio;
			printf ("Biografia: %s\n",biografia);
			break;
		}
		else user = user->next;
	}
 
	printf ("Ultimos 10 posts: ");
	while (posts!=NULL && i<10) {
		if (posts->userID == id) {
			array[i] = posts->id;
			printf ("%ld; ",array[i]);
			i++;	
		}
		posts=posts->next;
	}


	resultado = create_user(biografia,array);
	 

	return resultado;
}
 
//QUERY 6
LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end){
	
	head lista =  com->posts;
	LONG_list resposta = NULL;
	
	int i = 0;
	int votos[N];
	unsigned long ids[N];
	int aux; unsigned long aux2;
 	int auxiliar;
	unsigned long auxiliar2;
	int dia, mes, ano, data;
	
	int dataI = begin->year*10000+begin->month*100+begin->day;
	int dataF = end->year*10000+end->month*100+end->day;

	for (i=0;i<N;i++) {
		votos[i]=0;
		ids[i]=0;
	}
	

	while (lista!=NULL) {
				
		aux = lista->score;
		aux2 = lista->id;

		dia = getDay(lista->data);
		mes = getMonth(lista->data);
		ano = getYear(lista->data);
 		data = ano*10000+mes*100+dia;


 		if (data>=dataI && data<=dataF && lista->tipo==2) {

			for (i=0;i<N;i++) {
				if ((votos[i] < aux) || ((votos[i] == aux) && aux2 > ids[i])) {
					auxiliar = votos[i];
					auxiliar2 = ids[i];
					votos[i] = aux;
					ids[i] = aux2;
					aux = auxiliar;
					aux2 = auxiliar2;
				}
			}

		}

		lista = lista->next;
	}


	resposta = create_list(N);

	for (i=0;i<N;i++) {	
		set_list(resposta,i,ids[i]);
		printf ("%ld; ",ids[i]);
	}
 	return resposta;

}

// QUERY 7
LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end){
	head lista =  com->posts;
	LONG_list resposta = create_list(N);
	
	int i = 0;
	int respostas[N];
	unsigned long ids[N];
	int aux; unsigned long aux2;
	int auxiliar;
	unsigned long auxiliar2;
	int dia, mes, ano, data;
	
	int dataI = begin->year*10000+begin->month*100+begin->day;
	int dataF = end->year*10000+end->month*100+end->day;

	for (i=0;i<N;i++) {
		respostas[i]=0;
		ids[i]=0;
	}
	

	while (lista!=NULL) {
				
				aux = lista->numAnswers;
				aux2 = lista->id;
				dia = getDay(lista->data);
				mes = getMonth(lista->data);
				ano = getYear(lista->data);
 				data = ano*10000+mes*100+dia;
	 

 		if (data>=dataI && data<=dataF && lista->tipo==1) {

		for (i=0;i<N;i++) {
				if (aux > respostas[i]) {
					auxiliar = respostas[i];
					auxiliar2 = ids[i];
					respostas[i] = aux;
					ids[i] = aux2;
					aux = auxiliar;
					aux2 = auxiliar2;
				}
			}

		}

		lista = lista->next;
	}

	for (i=0;i<N;i++){
		set_list(resposta,i,ids[i]);
//		printf ("%ld\n",resposta->list[i]);
		printf ("%ld %d\n",ids[i],respostas[i]);
	} 
	return resposta;
}

//QUERY 8
LONG_list contains_word(TAD_community com, char* word, int N) {

	head posts = com->posts;
	LONG_list resposta = create_list(N);
	int i = 0 ;

	while (posts!=NULL) {
		int condicao = comparaTitulo(posts->title,word);
		if (posts->tipo==1 && condicao==1 && i<N) {
			set_list(resposta,i,posts->id);
			i++;
		}
																																																																																																					
		posts = posts->next;																																																																																																																																																																																																																																																																																																																																												
	}	
	int j = 0;
	while (j<i) {
		
		printf ("%ld\n",resposta->list[j]);
		j++;
	}

	return resposta;


}

// QUERY 9

LONG_list both_participated(TAD_community com, long id1, long id2, int N) {

	head posts = com->posts;
	LONG_list resposta = create_list(N);
	unsigned long *array1 = malloc(sizeof(unsigned long));	 
	int achou = 0;
	int i = 0; int j = 0;
	int resultado[N];
	int k = 0;
	
	while (posts!=NULL) {
		
		if (posts->userID == id1)  {	
				if(posts->tipo==2) array1[i] = posts->parentID;
				else array1[i] = posts->id;
				i++;
		}
		posts = posts->next;	
	}

	posts = com->posts;
	int post = 0 ;

	while (posts!=NULL) {

		if (posts->userID == id2)  {	
				if(posts->tipo==2) post = posts->parentID;
				else post = posts->id;
		}

		for (j=0;j<i;j++) {
			if (array1[j] == post) {
				achou=0;
				for(i=0;i<k;i++){
					if (resultado[i]==post){
						achou=1;
						break;
					}
				}
				if (achou==0) {
					resultado[k] = array1[j];
					k++;
					break;
				}
			}
		}
	

		posts = posts->next;
	}

	
	resultado[k]='\0';

	for (k=0;k<N && resultado[k]!='\0';k++) set_list(resposta,k,resultado[k]);
	
	return resposta;
 

}
																																																																																																																																																																																																																																																																																							
// QUERY 10 
long better_answer(TAD_community com, long id){
	head lista =  com->posts;
	usuario users  = com->users;
	
	float maior = 0;
	unsigned long idBestAnswer = 0;
 
	while (lista!=NULL) {
		
		if (lista->parentID == id) {
			int reputacao = reputacaoUser(users,lista->userID);
			float resultado =	(lista->score * 0.45) + (reputacao*0.25) + (	lista->score * 0.2) + (lista->numComments*0.1);																																																																																																																																																																																																																																																																																																																																																													
			unsigned long idDoPost = lista->id;

			if (resultado > maior) {
				maior = resultado;
				idBestAnswer = idDoPost;
			}
			

		}
		
		lista = lista->next;																																													
	}
	printf ("%f maior %ld id", maior,idBestAnswer);																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																															

	return idBestAnswer;
}



long top_tag(TAD_community com, int N, Date begin, Date end){
	int i; int j;
	head lista =  com->posts;
	usuario users  = com->users;
	int nReput[MAX_USERS];
	int nTop_UserId[N];
	int nTop_UserReput[N];
	int idTop_Tag[N];
	int nTop_TagConta[N];
    
	for (i=0;i<MAX_USERS;i++){
         nReput[i]=0;
     }

	for (i=0;i<N;i++){
		nTop_TagConta[i] = 0;
     }

	// carregar reputação
	while (users!=NULL){
		nReput[users->id]=users->reputacao;
		users=users->next;
	}
	printf ("EOQWNKWNEEQWKJENWJNQEKN");
	// top N dos posts
	int dia, mes, ano, data;
	int auxId, oldId;
	int dataI = begin->year*10000+begin->month*100+begin->day;
	int dataF = end->year*10000+end->month*100+end->day;
	int achou;
	
	for (i=0;i<N;i++) {
		nTop_UserId[i]=0;
		nTop_UserReput[i]=0;
	}
	
	for (i=0; i<MAX_USERS;i++) {
		auxId = i;
		for (j=0;j<N;j++) {
				if (nReput[auxId] > nTop_UserReput[j]) {
					oldId = nTop_UserId[j];
					nTop_UserId[j] = auxId;
					nTop_UserReput[j] = nReput[auxId];
					auxId = oldId;
				}
		}
	}

	char matriz[1000][500];

i = 0;
j = 0;
int lin=0; int col=0;
int x = 0;

while (lista!=NULL) {
	dia = getDay(lista->data);	
	mes = getMonth(lista->data);
	ano = getYear(lista->data);
	data = ano*10000+mes*100+dia;

	if (lista->tipo==1 && data>=dataI && data<=dataF) {
		achou = 0;
		for (i=0;i<N;i++) {
			if (nTop_UserId[i] == lista->userID) {
				achou = 1;
				break;
			}
		}

		if (achou==1) {

			for (j=0; lista->tag[j]!='\0';j++) {
				if (lista->tag[j] == '<') {
					col=0;
				}
				else if (lista->tag[j] == '>') lin++;
				else{
					matriz[lin][col] = lista->tag[j];
					col++;
				}
			}



		}

	}


	lista = lista->next;

}

	for (i=0; i<lin;i++) {
		for (j=0;j<500;j++) {
			printf ("%c",matriz[i][j]);
		}
		printf ("\n");
	}
	
	int *array = malloc(sizeof(int));
	
	int idTag; int oldIdTag;

	for (i=0;i<lin;i++) {
		if (matriz[i][0] != 'z'){ 
			array[i]=1;
			for (j=i+1;j<lin;j++) {
				for (x=0;x<500 && matriz[j][x] == matriz[i][x];x++);
				if (matriz[j][x]=='\0') {
					array[i] += 1;
					matriz[j][0] = 'z';
				}
			}
		}

	}
	
	for (i=0;i<lin;i++) {
		auxId = array[i];
		idTag = i;
		for (j=0; j<N; j++) {
			if (auxId > nTop_TagConta[j]) {
				oldId = nTop_TagConta[j];
				nTop_TagConta[j] = auxId;
				oldIdTag = idTop_Tag[j];
				idTop_Tag[j] = idTag;
				idTag = oldIdTag;
				auxId = oldId; 
			}
		}

	}

	for (i=0;i<N;i++) {
		printf ("%d %d\n", idTop_Tag[i], nTop_TagConta[i]);
		for (j=0;j<500;j++) printf ("%c",matriz[idTop_Tag[i]][j]);
		printf ("\n");
	}

	
	
	

	
}





TAD_community init() {
	TAD_community  novo = malloc(sizeof(struct TCD_community));
	return novo;
}

TAD_community load(TAD_community com, char* dump_path){
	com ->posts = postToStructure(dump_path);
	com -> users = usersToStructure(dump_path);
	com -> comentarios = commentsToStructure(dump_path);
	return com;
}




int main(int argc, char *argv[]){
	 
	 if (argc < 2) {
        fprintf(stderr, "Preciso da directoria.\n");
        exit(1);
    }
	
	printf("\033[H\033[J");
	printf ("Parece que os ficheiros estão todos bem! Vamos agora carregar a estrutura! Só mais um minutinho! \n");
	menu(argv[1]);

 
return 1;  
} 