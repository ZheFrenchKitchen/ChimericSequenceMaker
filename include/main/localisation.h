#ifndef PATCH_H
#define PATCH_H

#include <stdint.h>


typedef struct {
	char *chromosome,*sequence;
	int start,end;
} localisation_t;



#ifdef __cplusplus
extern "C" {
#endif

	//patch_options_t *patch_options_init();
	localisation_t *localisation_init(char *argv[],int *optind);
	//void read_localisationFile();
	void _count_locations_to_transform(FILE *file,int *p_lines);

	void locs_print(localisation_t  *locs,int *nombre_elements);

	void locs_destroy(localisation_t  *locs,int *nombre_elements);

#ifdef __cplusplus
}
#endif

#endif
