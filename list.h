#ifndef __LIST_H__
#define __LIST_H__

struct node {
    int num;
    struct node *next; 
};

char** tokenify(const char *);
void print_tokens(char *[]);
int check_valid(char []);
void add_tokens(char **, int *[], int *);
void list_append(int, struct node **);
void free_tokens(char **);
int compar_ints(const void *, const void *);
void fill_LL(struct node **, int *[], int);
void printLL(struct node **);


#endif // __LIST_H__
