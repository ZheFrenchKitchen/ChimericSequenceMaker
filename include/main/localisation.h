#ifndef LOCALISATION_H
#define LOCALISATION_H

#include <stdint.h>
#include <iostream>


using namespace std;

typedef struct {
	char *seq_name,*sequence,*region_name;
	int start,end;
} localisation_t;

typedef struct {
	char *seq_name,*chr_name;
	int start,end;
} gene_localisation_t;

	void modify_coord(std::string *id_name,localisation_t *locs,int *index , int *coord_upgrade);

	void modify_genes_coord(std::string *id_name,gene_localisation_t *locs,int *index , int *coord_upgrade) ;


#ifdef __cplusplus
extern "C" {
#endif

	int compare_locations(const void *objet1, const void *objet2);

	gene_localisation_t *genes_init(std::string *file);

	localisation_t *localisation_init(char *argv[],int *optind);

	void _count_locations_to_transform(FILE *file,int *p_lines);

	void locs_print(localisation_t  *locs,int *nombre_elements);

	void locs_destroy(localisation_t  *locs,int *nombre_elements);



#ifdef __cplusplus
}
#endif

#endif
