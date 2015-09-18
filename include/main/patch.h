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
	void patcher(char *argv[],int *optind);
	//void read_localisationFile();
	void _count_locations_to_transform(FILE *file,int *p_lines);

#ifdef __cplusplus
}
#endif

#endif
