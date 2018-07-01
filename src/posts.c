#include <stdlib.h>
#include <libxml/parser.h>
#include <time.h>

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

// Função que serve para retirar a informação que é necessária do post e inserir essa mesma informação na estrutura
head insert(head teste, unsigned long id, unsigned char* title, unsigned long userID, unsigned long tipoPost,unsigned char* dataPost, unsigned char* tag, unsigned long numAnswers, unsigned long numComments, unsigned long parentID, unsigned long score){
        head temp;
        temp = malloc(sizeof(struct node));
        temp->id = id;
        temp->title = title;
        temp->userID = userID;
        temp->tipo = tipoPost;
        temp->data=dataPost;
        temp->tag=tag;
        temp->numAnswers=numAnswers;
        temp->numComments=numComments;
        temp->parentID = parentID;
        temp->score=score;
        temp->next=teste;

        return temp;    
}  


// Função que vai ler o ficheiro posts.xml e carregar toda a informação necessária para a estrutura
head postToStructure (const char *directoria) {
        
        clock_t begin = clock();
        char directory[100];
	strcpy (directory,directoria);
	strcat(directory,"Posts.xml"); 
        printf ("A carregar os posts...");                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
        xmlDocPtr doc = xmlParseFile(directory);

        xmlNodePtr nodo = xmlDocGetRootElement(doc);
        xmlNodePtr aux = nodo->children->next;
        xmlNodePtr cur;
        xmlChar *key;

        head test2 =NULL;
        unsigned long id;
        unsigned long tipo;
        unsigned char* title;
        unsigned long userID;
        unsigned char* data;
        unsigned char* tag;
        unsigned long numAnswers;
        unsigned long numComments;
        unsigned long parentId;
        unsigned long score;

                 
        while (aux != NULL){
                        
                cur = aux->properties;
                tag = (unsigned char*)"";
                title=(unsigned char*)"";
                data = (unsigned char*)"";
                tipo=0;
                userID=0;
                parentId=0;

                while (cur != NULL) {                                   
                                                        
                        if ((!xmlStrcmp(cur->name, (const xmlChar *)"Id"))) {
                                        key = xmlNodeListGetString(doc,cur->children,1);                                
                                        id = atol((const char*)key);
                        }
                                        
                                        else {}

                                        if ((!xmlStrcmp(cur->name, (const xmlChar *)"ParentId"))) {
                                                        key = xmlNodeListGetString(doc,cur->children,1);                                
                                                                parentId = atol((const char*)key);
                                                }
                                        
                                        else {}


                                        if ((!xmlStrcmp(cur->name, (const xmlChar *)"PostTypeId"))) {
                                                 key = xmlNodeListGetString(doc,cur->children,1);
                                                 tipo = atol((const char*)key);          
                                        }
                                        else {}
                                                
                                         
                                                if ((!xmlStrcmp(cur->name, (const xmlChar *)"CreationDate"))) {
                                                        key = xmlNodeListGetString(doc,cur->children,1);
                                                        data = key;
                                                 

                                                }
                                                else {}

                                         
                                                if ((!xmlStrcmp(cur->name, (const xmlChar *)"Body"))) {
                                                        key = xmlNodeListGetString(doc,cur->children,1);
                                         
                                                }
                                                else {}
                        
                                                if ((!xmlStrcmp(cur->name, (const xmlChar *)"OwnerUserId"))) {
                                                        key = xmlNodeListGetString(doc,cur->children,1);
                                                                         
                                                         userID=atol((const char*)key); 
                                                }
                                                else {}

                                                
                                                if ((!xmlStrcmp(cur->name, (const xmlChar *)"Title"))) {
                                                        key = xmlNodeListGetString(doc,cur->children,1);
                                         
                                                         title = key;
                                                }
                                                else {}

                                                if ((!xmlStrcmp(cur->name, (const xmlChar *)"Tags"))) {
                                                        key = xmlNodeListGetString(doc,cur->children,1);

                                                         tag = key;
                                                }
                                                else {}

                                                if ((!xmlStrcmp(cur->name, (const xmlChar *)"AnswerCount"))) {
                                                key = xmlNodeListGetString(doc,cur->children,1);                                
                                                 
                                                        numAnswers = atol((const char*)key);
                                        }
                                        
                                        else {}

                                                if ((!xmlStrcmp(cur->name, (const xmlChar *)"CommentCount"))) {
                                                key = xmlNodeListGetString(doc,cur->children,1);                                
                                                 
                                                        numComments = atol((const char*)key);
                                        }
                                        
                                        else {}
                                        
                                        if ((!xmlStrcmp(cur->name, (const xmlChar *)"Score"))) {
                                                        key = xmlNodeListGetString(doc,cur->children,1);                                
                                                 
                                                                score = atol((const char*)key);
                                                }
                                        
                                        else {}
                                                
                                                cur = cur->next;

                        }       
                
                test2 = insert(test2,id,title,userID,tipo,data,tag,numAnswers,numComments,parentId,score);      
                
                aux = aux->next->next;
                 
        }
        clock_t end = clock();
        double tempo = end-begin;
        printf ("(%f segundos)\n",tempo);
 
        return test2;
}

// Função que verifica qual é o tipo de post
int verificaTipoPost (head estrutura, long id) {
	
	//head estrutura = postToStructure();
	
	while (estrutura!=NULL) {
		if (id == estrutura->id) return estrutura->tipo;
		else estrutura =  estrutura->next;
	}

	return 0;
}

//  Função que devolve o parentID do post quando o tipo for 2
int devolveParentID (head estrutura, long id) {
	
	
	
	while (estrutura!=NULL) {
		if (id == estrutura->id) return estrutura->parentID;
		else estrutura =  estrutura->next;
	}

	return 0;
}

// Função que vai contar todos os posts existentes do userID
int conta_posts (head com, unsigned long userid) {
	int conta = 0;

	while (com!=NULL) {
		if (com->userID == userid) {
			conta++;
		}
		com = com->next;
	}


	return conta;
}
