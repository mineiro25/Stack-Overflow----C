#include <libxml/parser.h>
#include <time.h>
#include <string.h>

// Estrutura de users
typedef struct informacao {
	unsigned long id;
	char *nome;
	unsigned long posts;
	char *bio;
	unsigned long reputacao;
	struct informacao *next;
}*usuario;


// Função que serve para inserir a informação sobre um user na estrutura
usuario insereNome(usuario teste,char *nome, unsigned long idUser, unsigned long post, char *bio, unsigned long reputacao){
 		usuario temp;
 		temp = malloc(sizeof(struct informacao));
 		temp->id = idUser;
 		temp->nome =nome;
 		temp->posts = post;
 		temp->bio = bio;
 		temp->reputacao=reputacao;
 	 
 		temp->next=teste;
 		return temp;
}  

// Função que vai ler o ficheiro users.xml e carregar toda a informação necessária para a estrutura
usuario usersToStructure (const char *directoria) {
		printf ("A carregar os usuarios...");
		clock_t begin = clock();
        char directory[100];
		strcpy (directory,directoria);
		strcat(directory,"Users.xml"); 
        xmlDocPtr doc = xmlParseFile(directory);



		xmlNodePtr nodo = xmlDocGetRootElement(doc);
		xmlNodePtr aux = nodo->children->next;
		xmlNodePtr cur;
		xmlChar *key;

		usuario test2 = NULL;
		unsigned long id;
    	char* nome;
    	char* bio;
    	unsigned long reputacao;

	while (aux != NULL){
			cur = aux->properties;
			bio = "";
		 	while (cur != NULL) {	 				
						 	
				    	if ((!xmlStrcmp(cur->name, (const xmlChar *)"Id"))) {
				    			key = xmlNodeListGetString(doc,cur->children,1);
								id = atol((const char*)key);
								 
				    		}
			    		
			    		else {}

			    		if ((!xmlStrcmp(cur->name, (const xmlChar *)"DisplayName"))) {
			    			 key = xmlNodeListGetString(doc,cur->children,1);
			    			 nome = (char*)key;
			    		 
			    		}
			    		else {}

			    		if ((!xmlStrcmp(cur->name, (const xmlChar *)"AboutMe"))) {
			    			 key = xmlNodeListGetString(doc,cur->children,1);
			    			 bio = (char*)key;
			    		}
			    		else {}

				    	if ((!xmlStrcmp(cur->name, (const xmlChar *)"Reputation"))) {
				    			key = xmlNodeListGetString(doc,cur->children,1);
								reputacao = atol((const char*)key);
								 
				    		}
			    		
			    		else {}

						cur = cur->next;
			}	

		test2=insereNome(test2,nome,id,0,bio,reputacao);
		aux = aux->next->next;
	}
	
	clock_t end = clock();
    double tempo = end-begin;
    printf ("(%f segundos)\n",tempo);
	
	return test2;
}

// Função que conta quantos usuarios existe no users.xml
int contaUsers (usuario usuarios) {
	int i = 0;
	while (usuarios!=NULL) {
		i++;
		usuarios = usuarios->next;
	}
	return i;

}

// Função que obtem a reputação de user que queremos
int reputacaoUser (usuario estrutura, unsigned long id) {

	while (estrutura!=NULL) {
		if (estrutura->id==id) return estrutura->reputacao;
		estrutura = estrutura->next;
	}

	return 0;

}