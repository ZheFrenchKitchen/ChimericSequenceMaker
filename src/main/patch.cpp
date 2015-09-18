#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#include "../../include/main/patch.h"


//#define NDEBUG if you want to remove assert

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
	  if(ch == '\n') (*p_lines)++;

	}

}

void patcher(char *argv[],int *optind){

	int c;

	int lines = 0;
	int *p_lines  = &lines;
	printf("\n lines %d",lines);
	printf("\n *p_lines %d",*p_lines);

	FILE *file;
	char line[256];

	file = fopen(argv[*optind], "r");
	//_count_locations_to_transform(file,p_lines);
	_count_locations_to_transform(file,&lines);
	printf("\n lines %d",lines);
	printf("\n *p_lines %d",*p_lines);
	fclose(file);

	file = fopen(argv[*optind], "r");
	/*
	char *strArray[lines+1];
	localisation_t *locs = (localisation_t*) calloc(1, sizeof(localisation_t));
	strArray[a] = (char *) malloc(strlen(token) + 1);

	assert(who != NULL);
	localisation_t* array_loc[3];
	int i = 0;
	while (fgets(line, sizeof(line), file)) {
       // note that fgets don't strip the terminating \n, checking its
         //  presence would allow to handle lines longer that sizeof(line)
    	// Token will point to "SEVERAL".

    	// C++ need casting for malloc/calloc not C


        char *token = strtok(line,"	");

    	 int a = 0;
    	  while(token != NULL)
    	     {
    	         strcpy(strArray[a], token);
    	         strArray[a] = (char *) malloc(strlen(token) + 1);
    	         strcpy(strArray[a], token);
    	         printf("[%s]\n", token);
    	         token = strtok(NULL, "	");
    	         a++;
    	     }
    	  for (int i = 0; i < 3; i++)     printf("Allllezz [%s]\n", token);

    } */
/*    for (int i = 0; i < 3; i++)
       {
    	printf("#########");

    	printf("\nChromosome  : %s\n",array_loc[i]->chromosome);
    	printf("\nStart  : %d\n",array_loc[i]->start);
    	printf("\nEnd  : %d\n",array_loc[i]->start);
    	printf("\nSequence  : %s\n",array_loc[i]->sequence);
       }
/*/
	printf("\n");
    fclose(file);

}
/*
localisation_t *create_localisation_item()
{
	// C++ need casting for malloc/calloc not C
	localisation_t *o = (localisation_t*)calloc(1, sizeof(localisation_t));
	// Could set default value here
	//o->a = 1; o->b = 3; o->h = 0;
	return o;
}

void read_localisationFile()
{

}
*/
