#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#include "../../include/main/localisation.h"


//#define NDEBUG if you want to remove assert
int nb_loc = 0;

int compare_locations(const void *objet1, const void *objet2)
{
    const localisation_t *instance1 = (localisation_t *) objet1;
    const localisation_t *instance2 = (localisation_t *) objet2;

    if (instance1->chromosome == instance2->chromosome){ return instance1->start - instance2->start;}

    	else  return  strcmp(instance1->chromosome, instance2->chromosome)  ;

}

void _count_locations_to_transform(FILE *file,int *p_lines){

	int ch = 0;
	if (file == NULL)
	{
		fprintf(stderr, "File doesn't exist.\n");
		exit(EXIT_FAILURE);
	}

	while(!feof(file))
	{
	  ch = fgetc(file);
	  if(ch == '\n') {(*p_lines)++; nb_loc++;}

	}

}

void locs_destroy(localisation_t  *locs,int * nombre_elements)
{
    assert(locs != NULL);
    for (int i=0; i < *nombre_elements;i++){

    	 free(locs[i].chromosome);
    	 free(locs[i].sequence);
    }
    free(locs);
}

void locs_print(localisation_t  *locs,int * nombre_elements)
{
	for (int i=0; i < *nombre_elements;i++){

	 	printf("\n");
	 	printf("Chromosome : [%s]\n", locs[i].chromosome);
	 	printf("Start : [%d]\n", locs[i].start);
	 	printf("End : [%d]\n", locs[i].end);
	 	printf("Sequence : [%s]\n", locs[i].sequence);
	 	printf("\n");

	}
}

localisation_t *localisation_init(char *argv[],int *optind){

	int c;

	int lines = 0;
	int *p_lines  = &lines;

	FILE *file;
	char line[256];

	file = fopen(argv[*optind], "r");
	//_count_locations_to_transform(file,p_lines);
	_count_locations_to_transform(file,&lines);

	fclose(file);

	file = fopen(argv[*optind], "r");

	localisation_t *locs = (localisation_t*) calloc(lines, sizeof(localisation_t));
	assert(locs != NULL);
	//printf("Number or locs [%d] \n", lines);

	int index_line = 0;
	while (fgets(line, sizeof(line), file)) {

		line[strcspn ( line, "\n" )] = '\0';
		 char *token = strtok(line," \t");
		 int a = 0;
    	 while(token != NULL)
		 {
    		//printf("Token [%d] : [%s]\n",a, token);

			if (a==0) locs[index_line].chromosome 	= strdup(token);
			if (a==1) locs[index_line].start 		= atol(token);
			if (a==2) locs[index_line].end 			= atol(token);
			if (a==3) locs[index_line].sequence 	= strdup(token);
			token = strtok(NULL, " \t");

			 a++;
		 }

    	index_line++;
    }

    fclose(file);

    return locs;
}

