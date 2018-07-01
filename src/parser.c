#include <date.h>
#include <stdio.h>
#include <libxml/parser.h>
#include <interface.h>
#include <string.h>
#include <stdlib.h>
 
int parsePosts (const char *directoria) {
	xmlDocPtr doc;
	xmlNodePtr nodo;

	char directory[100];
	strcpy (directory,directoria);
	strcat(directory,"Posts.xml");
	doc = xmlParseFile(directory);
	
	if (doc == NULL) { 
		printf ("DOH, não consegui encontrar o documento Posts \n");
		return 0;
	}

	nodo = xmlDocGetRootElement(doc);
	
// Para verificar se o documento tem mesmo lá algo dentro ! 
	if (nodo==NULL) {
		printf ("DOH, o documento Posts está vazio! Verifica isso!\n");
		xmlFreeDoc(doc);
		return 0;
	}

	return 1;
}


int parseBadges (const char *directoria) {
	xmlDocPtr doc;
	xmlNodePtr nodo;
	
	char directory[100];
	strcpy (directory,directoria);
	strcat(directory,"Badges.xml");
	doc = xmlParseFile(directory);
	
	if (doc == NULL) { 
		printf ("DOH, não consegui encontrar o documento Badges \n");
		return 0;
	}

	nodo = xmlDocGetRootElement(doc);
	
// Para verificar se o documento tem mesmo lá algo dentro ! 
	if (nodo==NULL) {
		printf ("DOH, o documento Badges está vazio! Verifica isso!\n");
		xmlFreeDoc(doc);
		return 0;
	}

	return 1;
}


int parseComments (const char *directoria) {
	xmlDocPtr doc;
	xmlNodePtr nodo;
	
	char directory[100];
	strcpy (directory,directoria);
	strcat(directory,"Comments.xml");
	doc = xmlParseFile(directory);
	
	if (doc == NULL) { 
		printf ("DOH, não consegui encontrar o documento Comments \n");
		return 0;
	}

	nodo = xmlDocGetRootElement(doc);
	
// Para verificar se o documento tem mesmo lá algo dentro ! 
	if (nodo==NULL) {
		printf ("DOH, o documento Comments está vazio! Verifica isso!\n");
		xmlFreeDoc(doc);
		return 0;
	}

	return 1;
}

int parsePostHistory (const char *directoria) {
	xmlDocPtr doc;
	xmlNodePtr nodo;
	
	char directory[100];
	strcpy (directory,directoria);
	strcat(directory,"PostHistory.xml");
	doc = xmlParseFile(directory);
	
	if (doc == NULL) { 
		printf ("DOH, não consegui encontrar o documento PostHistory \n");
		return 0;
	}

	nodo = xmlDocGetRootElement(doc);
	
// Para verificar se o documento tem mesmo lá algo dentro ! 
	if (nodo==NULL) {
		printf ("DOH, o documento PostHistory está vazio! Verifica isso!\n");
		xmlFreeDoc(doc);
		return 0;
	}

	return 1;
}

int parsePostLinks (const char *directoria) {
	xmlDocPtr doc;
	xmlNodePtr nodo;
	
	char directory[100];
	strcpy (directory,directoria);
	strcat(directory,"PostLinks.xml");
	doc = xmlParseFile(directory);
	
	if (doc == NULL) { 
		printf ("DOH, não consegui encontrar o documento PostLinks \n");
		return 0;
	}

	nodo = xmlDocGetRootElement(doc);
	
// Para verificar se o documento tem mesmo lá algo dentro ! 
	if (nodo==NULL) {
		printf ("DOH, o documento PostLinks está vazio! Verifica isso!\n");
		xmlFreeDoc(doc);
		return 0;
	}

	return 1;
}

int parseTags (const char *directoria) {
	xmlDocPtr doc;
	xmlNodePtr nodo;
	
	char directory[100];
	strcpy (directory,directoria);
	strcat(directory,"Tags.xml");
	doc = xmlParseFile(directory);
	
	if (doc == NULL) { 
		printf ("DOH, não consegui encontrar o documento Tags \n");
		return 0;
	}

	nodo = xmlDocGetRootElement(doc);
	
// Para verificar se o documento tem mesmo lá algo dentro ! 
	if (nodo==NULL) {
		printf ("DOH, o documento Tags está vazio! Verifica isso!\n");
		xmlFreeDoc(doc);
		return 0;
	}

	return 1;
}

int parseUsers (const char *directoria) {
	xmlDocPtr doc;
	xmlNodePtr nodo;
	
	char directory[100];
	strcpy (directory,directoria);
	strcat(directory,"Users.xml");
	doc = xmlParseFile(directory);
	
	if (doc == NULL) { 
		printf ("DOH, não consegui encontrar o documento Users \n");
		return 0;
	}

	nodo = xmlDocGetRootElement(doc);
	
// Para verificar se o documento tem mesmo lá algo dentro ! 
	if (nodo==NULL) {
		printf ("DOH, o documento Users está vazio! Verifica isso!\n");
		xmlFreeDoc(doc);
		return 0;
	}

	return 1;
}

int parseVotes (const char *directoria) {
	xmlDocPtr doc;
	xmlNodePtr nodo;
	
	char directory[100];
	strcpy (directory,directoria);
	strcat(directory,"Votes.xml");
	doc = xmlParseFile(directory);
	
	if (doc == NULL) { 
		printf ("DOH, não consegui encontrar o documento Votes \n");
		return 0;
	}

	nodo = xmlDocGetRootElement(doc);
	
// Para verificar se o documento tem mesmo lá algo dentro ! 
	if (nodo==NULL) {
		printf ("DOH, o documento Votes está vazio! Verifica isso!\n");
		xmlFreeDoc(doc);
		return 0;
	}

	return 1;
}


int parsingDirectory (char *directoria) {
 printf ("Só um minutinho! Vamos analisar os ficheiros!\n");
 return (parseVotes(directoria) && parseUsers(directoria) && parseTags(directoria) && parseComments(directoria) && parseBadges(directoria) && parsePosts(directoria) && parsePostLinks(directoria) && parsePostHistory(directoria));
}