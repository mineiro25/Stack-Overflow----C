#include <stdlib.h>
#include <libxml/parser.h>
#include <time.h>
#include <string.h>

typedef struct comments {
		unsigned long id;
        unsigned long userID;
        unsigned char* data;
        unsigned long postID;
        unsigned long score;
        unsigned char* text;
        struct comments *next;
}*respostas;


respostas insereRespostas(respostas teste, unsigned long id, unsigned char* data, unsigned long userID, unsigned long postID,unsigned long score, unsigned char *text){
        respostas temp;
        temp = malloc(sizeof(struct comments));
        temp->id = id;
        temp->data = data;
        temp->userID = userID;
        temp->postID = postID;
        temp->score = score;
        temp->text=text;
        temp->next = teste;

        return temp;	
}  



respostas commentsToStructure (const char *directoria) {
		printf ("A carregar os comentarios...");
		clock_t begin = clock();
        char directory[100];
		strcpy (directory,directoria);
		strcat(directory,"Comments.xml"); 
        xmlDocPtr doc = xmlParseFile(directory);

		
		xmlNodePtr nodo = xmlDocGetRootElement(doc);
		xmlNodePtr aux = nodo->children->next;
		xmlNodePtr cur;
		xmlChar *key;

		respostas test2 =NULL;
	 	unsigned long id;
        unsigned long userID;
        unsigned char* data;
        unsigned long postID;
        unsigned long score;
        unsigned char* text;
	
	while (aux != NULL){

			cur = aux->properties;
			id = 0;
			userID = 0;
			postID = 0;
			score = 0 ;
			data = (unsigned char*)"";
		
		 	while (cur != NULL) {	 				
						 	
				    	if ((!xmlStrcmp(cur->name, (const xmlChar *)"Id"))) {
				    			key = xmlNodeListGetString(doc,cur->children,1);  				
								id = atol((const char*)key);
								//printf ("id %ld\n",id);
				    		}
			    		
			    		else {}

				    	if ((!xmlStrcmp(cur->name, (const xmlChar *)"PostId"))) {
				    			key = xmlNodeListGetString(doc,cur->children,1);  				
								postID = atol((const char*)key);
								//printf ("postid %ld\n",postID);
				    		}
			    		
			    		else {}

				    	if ((!xmlStrcmp(cur->name, (const xmlChar *)"UserId"))) {
				    			key = xmlNodeListGetString(doc,cur->children,1);  				
								userID = atol((const char*)key);
								//printf ("userid %ld\n", userID);
				    		}
			    		
			    		else {}

				    	if ((!xmlStrcmp(cur->name, (const xmlChar *)"Score"))) {
				    			key = xmlNodeListGetString(doc,cur->children,1);  				
								score = atol((const char*)key);
								//printf ("score %ld\n",score);
				    		}
			    		
			    		else {}

				    	if ((!xmlStrcmp(cur->name, (const xmlChar *)"CreationDate"))) {
				    			key = xmlNodeListGetString(doc,cur->children,1);  				
								data = key;
				    			//printf ("%s\n",key);
				    		}
			    		
			    		else {}
			    		
				    	if ((!xmlStrcmp(cur->name, (const xmlChar *)"Text"))) {
				    			key = xmlNodeListGetString(doc,cur->children,1);  				
								text = key;
				    			//printf ("%s\n",key);
				    		}
			    		
			    		else {}

						cur = cur->next;

			}	
		
		test2 = insereRespostas(test2, id,  data, userID,  postID, score, text );
		aux = aux->next->next;
 		 
	}
	    clock_t end = clock();
        double tempo = end-begin;
        printf ("(%f segundos)\n",tempo);
 
	return test2;
}
