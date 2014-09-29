#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <string.h>

char** tokenify(const char *newstr) {
	char *pstring = strdup(newstr); //pointer to copy of s 
	char *ptoken; 
	ptoken = strtok(pstring, " \t\n");
	char **array = malloc(sizeof(char*)*((strlen(newstr)/2)+2));
	
	// count the number of tokens
	int i = 0;
	while (ptoken != NULL) {
		char *ptrtok = strdup(ptoken);
		array[i] = ptrtok;
		ptoken = strtok(NULL, " \t\n");
		i++;	
	}
	// set last index in array to NULL
	array[i]=NULL;
	// free 
	free(pstring);
	return array;
}


void print_tokens(char *tokens[]) { //Prof. Sommers' code from lab
    int i = 0;
    while (tokens[i] != NULL) {
        printf("Token %d: %s\n", i+1, tokens[i]);
        i++;
    }
}


int check_valid(char arr[]) {
	
	// check for a comment
	for (int i = 0; i<strlen(arr); i++) {
		if (arr[i] == '#') {
			return 0; // 0 means it's a comment
		}
	}
	
	// check to make sure it's an integer
	for (int j = 0; j<strlen(arr); j++) {
		if (isdigit(arr[j])==0) { // check for a char that isn't a digit
			if (j!=0 && arr[0] != '-') {
				return 1;
			}
		}
	}
	return 2; // 2 means that it's a valid integer token 
}


void add_tokens(char **tokenarr, int *masterarr[], int *mastercount) {

	int count = 0;
	for (int i=0; i<sizeof(tokenarr); i++) {
		if (check_valid(tokenarr[i]) ==2) { // 2 means valid
			const char *ptr = tokenarr[i];
			int validtok = atoi(ptr);
			//printf("im adding to masterarr: this token is %d\n", validtok);
			masterarr[count] = validtok;
			count++;
			
		}

		else if (check_valid(tokenarr[i])==0) { // 0 means we hit a # for comment
			return;
		}
		// if neither 2 or 0, keep looping
	} 
	return; 
} 




void list_append(int num, struct node **head) { // taken from hw03
	
	struct node *newnode = malloc(sizeof(struct node));
	newnode->num = num;
	newnode->next = NULL;

	if (*head == NULL) { // if list is empty, set it to new node
		*head = newnode; 
		return;
	}

	struct node *temp = *head;
	
	while (temp->next != NULL) {
		temp = temp->next;
	}
	
	temp->next = newnode;
	free(newnode);

}


void free_tokens(char **tokens) { // Prof. Sommers' code
    int i = 0;
    while (tokens[i] != NULL) {
        free(tokens[i]); // free each string
        i++;
    }
    free(tokens); // then free the array

}

int compar_ints(const void * num1, const void * num2) {

	const int *n1 = (const int *)num1; //cast type
	const int *n2 = (const int *)num2;

	if (n1 > n2) {
		return 1;
	}
	if (n1<n2) {
		return -1;
	}

	return 0;
}

void fill_LL(struct node **masterhead, int *masterarr[], int mastercount){
	int i = 0;
	int curnum = 0;

	while (i<=mastercount) {
		curnum = (*masterarr)[i]; //access each integer to add
		list_append(curnum, masterhead);
	}
	return;
} 

void printLL(struct node **masterhead) {

	printf("*** List Contents Begin ***\n");
	struct node *temp = *masterhead;
	while (temp!=NULL) {
		printf("%d\n", temp->num); //print each node's integer
		temp = temp->next;

	}
	printf("*** List Contents End ***\n");
};


	
