/*
Claire Grace
Sept. 28, 2014
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "list.h"

void process_data(FILE *input_file) {
	struct rusage u;
	getrusage(RUSAGE_SELF, &u);
	int *masterarr;
	masterarr = malloc(sizeof(int)*5000);
	struct node **masterhead = malloc(sizeof(struct node)*5000);
	int *mastercount; 
	mastercount = 0;
	char newstr[100] = "before";
	char *strptr;
	strptr = newstr;
	fgets(strptr, 100, input_file); // for testing
	while (1) {
		if(!feof(input_file)) {	//make sure not at end of file
			fgets(strptr, 100, input_file);
		}
		else {
			break;
		}
		
		char ** currentline = tokenify(strptr); // tokenify the current line 
		//test
		//printf("this line's tokens are: \n");
		//print_tokens(currentline);
		
		add_tokens(currentline, masterarr, mastercount);
		free_tokens(currentline);	
	}

	// sort the master array
	qsort(masterarr, *mastercount, sizeof(int), compar_ints);

	// then add all ints as nodes to masterhead
	fill_LL(masterhead, &masterarr, *mastercount);

	// now print out all ints from each node
	printLL(masterhead);

	//print user and system time
	getrusage(RUSAGE_SELF, &u);
	long usertime1 = u.ru_utime.tv_sec; //whole num of seconds
	long usertime2 = u.ru_utime.tv_usec; //fraction
	long systemtime1 = u.ru_stime.tv_sec; //whole
	long systemtime2 = u.ru_stime.tv_usec; //fraction
	printf("User time: %ld.%06ld\n", usertime1, usertime2);
	printf("System time: %ld.%06ld\n", systemtime1, systemtime2);


	free(masterarr);
	free(masterhead);
	fclose(input_file); //close the file 

}


void usage(char *program) {
    fprintf(stderr, "usage: %s [<datafile>]\n", program);
    exit(1);
}

#ifndef AUTOTEST
int main(int argc, char **argv) {
    FILE *datafile = NULL;

    /* find out how we got invoked and deal with it */
    switch (argc) {
        case 1:
            /* only one program argument (the program name) */ 
            /* just equate stdin with our datafile */
            datafile = stdin;        
            break;

        case 2:
            /* two arguments: program name and input file */
            /* open the file, assign to datafile */
            datafile = fopen(argv[1], "r");
            if (datafile == NULL) {
                printf("Unable to open file %s: %s\n", argv[1], strerror(errno));
                exit(-1);
            }
            break;

        default:
            /* more than two arguments?  throw hands up in resignation */
            usage(argv[0]);
    }

    /* 
     * you should be able to just read from datafile regardless 
     * whether it's stdin or a "real" file.
     */
    process_data(datafile);
    fclose(datafile);
    return 0;
}
#endif
