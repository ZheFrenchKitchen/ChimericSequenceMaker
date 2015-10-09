#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#include "../../include/main/localisation.h"

#define NDEBUG //if you want to remove assert

// ugly
int nb_loc = 0;
int genes = 0;


void modify_genes_coord(std::string *id_name,gene_localisation_t *locs,int *index , int *coord_upgrade) {

	if (strcmp(locs[*index+1].seq_name,id_name->c_str()) == 0 ){

		locs[*index].start = locs[*index].start + *coord_upgrade;
		locs[*index].end   = locs[*index].end + *coord_upgrade;

	 }

}

void modify_coord(std::string *id_name,localisation_t *locs,int *index , int *coord_upgrade) {

	if (strcmp(locs[*index+1].seq_name,id_name->c_str()) == 0 ){


		locs[*index+1].start = locs[*index+1].start + *coord_upgrade;
		locs[*index+1].end   = locs[*index+1].end + *coord_upgrade;

	 }

}

int compare_locations(const void *objet1, const void *objet2)
{
    const localisation_t *instance1 = (localisation_t *) objet1;
    const localisation_t *instance2 = (localisation_t *) objet2;

    if (strcmp(instance1->seq_name, instance2->seq_name) == 0 ){ return instance1->start - instance2->start;}

    	else  return  strcmp(instance1->seq_name, instance2->seq_name)  ;

}

void _count_locations_to_transform(FILE *file,int *p_lines){

	int ch = 0;
	nb_loc = 0;
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

int count_genes(FILE *file){

	int ch = 0;
	int nb_gene = 0;

	if (file == NULL)
	{
		fprintf(stderr, "File doesn't exist.\n");
		exit(EXIT_FAILURE);
	}

	while(!feof(file))
	{
	  ch = fgetc(file);
	  if(ch == '\n') {nb_gene++;}

	}

	return nb_gene;
}

void locs_destroy(localisation_t  *locs,int * nombre_elements)
{
    assert(locs != NULL);
    for (int i=0; i < *nombre_elements;i++){

    	 free(locs[i].seq_name);
    	 free(locs[i].sequence);
    }
    free(locs);
}
void genes_locs_destroy(gene_localisation_t  *locs,int * nombre_elements)
{
    assert(locs != NULL);
    for (int i=0; i < *nombre_elements;i++){

    	 free(locs[i].seq_name);
    	 free(locs[i].chr_name);
    }
    free(locs);
}

void locs_print(localisation_t  *locs,int * nombre_elements)
{

	printf("#########################################\n");
	for (int i=0; i < *nombre_elements;i++){

	 	printf("\n");
	 	printf("name_seq : [%s]\n", locs[i].seq_name);
	 	printf("Start : [%d]\n", locs[i].start);
	 	printf("End : [%d]\n", locs[i].end);
	 	printf("Sequence : [%s]\n", locs[i].sequence);
	 	printf("\n");

	}
}

void genes_locs_print(gene_localisation_t  *locs,int * nombre_elements)
{

	printf("#########################################\n");
	for (int i=0; i < *nombre_elements;i++){

	 	printf("\n");
	 	printf("name_seq : [%s]\n", locs[i].seq_name);
	 	printf("Start : [%d]\n", locs[i].start);
	 	printf("End : [%d]\n", locs[i].end);
	 	printf("name_chr : [%s]\n", locs[i].chr_name);
	 	printf("\n");

	}
}

gene_localisation_t *genes_init(std::string *filename){




	FILE *file_ref;
	file_ref = fopen(filename->c_str(), "r");
	genes = count_genes(file_ref); 	// Initially i tried to reuse _count_locations_to_transform but i had a segmentation error
										// code is getting ugly...i duplicate a new structure derivate from locations
	fclose(file_ref);

	gene_localisation_t *locs = (gene_localisation_t*) calloc(genes, sizeof(gene_localisation_t));
	assert(locs != NULL);

	file_ref = fopen(filename->c_str(), "r");
	int index_line = 0;
	char line[64];
	while (fgets(line, sizeof(line), file_ref)) {

		line[strcspn ( line, "\n" )] = '\0';
		 char *token = strtok(line," \t");
		 int a = 0;
    	 while(token != NULL)
		 {

			if (a==0) locs[index_line].seq_name 	= strdup(token);
			if (a==2) locs[index_line].start 		= atol(token);
			if (a==3) locs[index_line].end 			= atol(token);
			if (a==1) locs[index_line].chr_name 	= strdup(token);
			token = strtok(NULL, " \t");

			 a++;
		 }

    	index_line++;
    }

	fclose(file_ref);
    return locs;
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

	int index_line = 0;
	while (fgets(line, sizeof(line), file)) {

		line[strcspn ( line, "\n" )] = '\0';
		 char *token = strtok(line," \t");
		 int a = 0;
    	 while(token != NULL)
		 {

			if (a==0) locs[index_line].seq_name 	= strdup(token);
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

