#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <algorithm>

#include "../../include/main/patch_dealer.h"
#include "../../include/main/localisation.h"
#include "../../include/main/chromosome.h"

void printer(std::vector<boost::filesystem::path> pN);

// Not used
bool is_value_in_vector(std::string item, std::vector<std::string> *vector);

int patch(int argc, char *argv[])
{
	patch_options_t *opt;
	opt = patch_options_init();

	int c;
	while ((c = getopt(argc, argv, "a:b:H")) >= 0) {
		switch (c) {
		case 'a': opt->a = atoi(optarg); break;
		case 'b': opt->b = atoi(optarg); break;
        case 'H': opt->h = 1; break;
        default: return 1;
		}
	}
	//If the resulting value of optind+1 is greater than argc, this indicates a missing option-argument
	// yes we add a file
	if (optind + 2 > argc) {

		fprintf(stderr, "\n");
		fprintf(stderr, "Usage:   chimericGenomeMaker patch [options] </path/to/ListofPositionsToTransform.txt> </path/to/DirectoryContainingChromosomeFiles> \n\n");
		fprintf(stderr, "Options: -a INT   blahblah [%d]\n", opt->a);
		fprintf(stderr, "         -b INT   blahblah [%d]\n", opt->b);
		fprintf(stderr, "         -H       blahblah \n");
		fprintf(stderr, "\n");

		return 1;
	}

	localisation_t *locs =  localisation_init(argv,&optind);

	extern int nb_loc;


	// Sorted by chr ans start
	qsort(locs, nb_loc, sizeof(localisation_t), compare_locations);
	locs_print(locs,&nb_loc);

	// Update Locs with re-evaluated coordinated

	std::vector<boost::filesystem::path> result_set = list_chromosomes(argv[optind +1]);

	std::sort(result_set.begin(), result_set.end());

	extern int nb_chr_file;
	fprintf(stderr, "Nbr chromosomes [%d] \n", nb_chr_file);

	std::vector<boost::filesystem::path>::iterator it = result_set.begin();
	std::vector<std::string>  files_opened;

	// FOREACH FILE_PATH
	while(it != result_set.end())
	{

/*
 * on s'en fout ici
 if (is_value_in_vector(it->string(), &files_opened) ) {std::cout<<"O god Yeahhhhhh = "<<it->string()<<std::endl;}

*/
			files_opened.push_back(it->string());

			std::cout<<"Path = "<<*it<<std::endl;

			FILE *file_ref;
			char line[100];

			file_ref = fopen(it->string().c_str(), "r");

			int r;
				while( (r=fgetc(file_ref) ) != EOF ) {

					//The first line
					if(r=='>') {

						fputc(r,stdout);
						while( (r=fgetc(file_ref) ) !=EOF && r!='\n' ) { fputc(r,stdout); }
						printf("\n");
						continue;
					}

				}

			fclose(file_ref);

			// ICI JE DEVRAIS STOCKER MA SEQUENCE DANS UNE VARIABLE.
			// SS ENTEND JE LUI DONNE DE LA MEMOIRE
				// JE PARCOURS MES LOCS
				// JE MODIFIE CETTE SEQUENCE POUR LES LOCS CORRESPONDANTES
			// JE CREE UN FICHIER OU JE PRINTE CETTE SEQUENCE
			// JE LIBERE LA MEMOIRE

		it++;
	  }
	// Just Print open files
	for(int i=0; i<files_opened.size(); ++i) std::cout << files_opened[i] << std::endl;


 //printer(result_set);

	free(opt);

	locs_destroy(locs,&nb_loc);


	return 0;
}

// Not used
// Tcheck presence of string value in std::vector<std::string>
bool is_value_in_vector(std::string item, std::vector<std::string> *vec){

    int i;
    for (i = 0; i < vec->size(); i++) {
    	if ( std::find(vec->begin(), vec->end(), item)!=vec->end() )
    	    	  return true;
    }
    return false;

}


// This method prints the vector
void printer(std::vector<boost::filesystem::path> pN)
{
	  std::vector<boost::filesystem::path>::iterator it = pN.begin();
	  while(it != pN.end())
	  {
	    std::cout<<"Path = "<<*it<<std::endl;
	    it++;

	  }
}

// Allocation of memory for options
patch_options_t *patch_options_init()
{
	// C++ need casting for malloc/calloc not C
	patch_options_t *o = (patch_options_t*)calloc(1, sizeof(patch_options_t));
	// Could set default value here
	//o->a = 1; o->b = 3; o->h = 0;
	return o;
}
