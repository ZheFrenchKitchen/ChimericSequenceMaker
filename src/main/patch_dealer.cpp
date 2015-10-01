#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <algorithm>
#include <fstream>

#include "../../include/main/patch_dealer.h"
#include "../../include/main/localisation.h"
#include "../../include/main/chromosome.h"

void printer(std::vector<boost::filesystem::path> pN);
bool startsWith(const char *a, const char *b);
void modify_coord(std::string *chr_name,localisation_t *locs,int *index , int *coord_upgrade) ;

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

	boost::filesystem::path someDir(argv[optind]);
	std::string path_to_output = someDir.parent_path().string();

	extern int nb_loc;


	// Sorted by chr ans start
	qsort(locs, nb_loc, sizeof(localisation_t), compare_locations);
	//locs_print(locs,&nb_loc);

	std::vector<boost::filesystem::path> result_set = list_chromosomes(argv[optind+1]);

	std::sort(result_set.begin(), result_set.end());

	extern int nb_chr_file;
	fprintf(stderr, "Nbr Sequences [%d] \n", nb_chr_file);
	fprintf(stderr, "Nbr Loc [%d] \n", nb_loc);

	std::vector<boost::filesystem::path>::iterator it = result_set.begin();

	// Create Direct to ouput Sequence Modified
	boost::filesystem::create_directory(path_to_output+"/chimericSequences");
	boost::filesystem::path dir(path_to_output+"/chimericSequences");

	//locs_print(locs,&nb_loc);

	// FOREACH FILE_PATH
	while(it != result_set.end())
	{
			//std::cout<<"Path = "<<*it<<std::endl;

			ifstream file_ref;    // Create an input file stream.
			file_ref.open(it->string().c_str());  // Use it to

			std::string chr_name,line,sequence;
			getline(file_ref,chr_name);  // Get the first line from the file, if any.

			if (startsWith(chr_name.c_str(),">")) { chr_name.erase(chr_name.begin()); }
			else {
					fprintf(stderr, "The application has stopped unexpectedly \nSequence format is not as expected  ! \n");
					exit(EXIT_FAILURE);
			 }

		    while( std::getline( file_ref, line )){  sequence += line; }

		    int coord_cursor = 0;

		    // First of all , Update of the coordinates
		    for (int i=0; i < nb_loc;i++){

		    	if (chr_name.compare(locs[i].chromosome) == 0) {

		    		if (locs[i].start > locs[i].end ){
		    			fprintf(stderr, "The application has stopped unexpectedly \nPositions are not well formated. End position is inferior to Start position somewhere in your input file  ! \n");
		    			printf("\n");
		    			fprintf(stderr,"Chromosome : [%s]\n", locs[i].chromosome);
		    			fprintf(stderr,"Start : [%d]\n", locs[i].start);
		    			fprintf(stderr,"End : [%d]\n", locs[i].end);
		    			fprintf(stderr,"Sequence : [%s]\n", locs[i].sequence);
		    			exit(EXIT_FAILURE);
		    		}

		    		//printf("\n");
					//printf("Chromosome : [%s]\n", locs[i].chromosome);
					//printf("Start : [%d]\n", locs[i].start);
					//printf("End : [%d]\n", locs[i].end);
					//printf("Sequence : [%s]\n", locs[i].sequence);
					//printf("SizeToRemove : [%d]\n", (locs[i].end -locs[i].start+1));
					//printf("SizeSequence : [%lu]\n", strlen(locs[i].sequence));
					coord_cursor += ( strlen(locs[i].sequence) - (locs[i].end -locs[i].start+1) );
					//printf("NucToAddOrRemoveToNextPositionOnSameChr : [%d]\n" ,coord_cursor);

					// You prevent an segment error caused by array
					if ( i + 1 < nb_loc  ) modify_coord(&chr_name,locs,&i,&coord_cursor);
					//printf("\n");

		    	}

			}

		    // Then we want to change sequence and to save in a new file
			for (int i=0; i < nb_loc;i++){

					if (chr_name.compare(locs[i].chromosome) == 0) 	sequence.replace(locs[i].start,locs[i].end,locs[i].sequence);
			}

			std::string output_new_sequence =    dir.string()+"/"+chr_name+".fa";
			FILE *new_sequence_p = fopen(output_new_sequence.c_str(), "w");
	    	fprintf(new_sequence_p, "%s\n", sequence.c_str());
			fclose(new_sequence_p);

			// TODO : REDECOUPER CORRECTEMENT LA SEQUENCE
			// TODO : FAIRE UN OPTION POUR METTRE A JOUR LA LISTE DES GENES
			// TODO : FAIRE UN SCRIPT POUR COMBINER PLUSIEURS REGIONS A LARRACHE
		it++;
	  }

	path_to_output+="/";
	path_to_output+="new_positions.txt";

	//locs_print(locs,&nb_loc);

	FILE *fp = fopen(path_to_output.c_str(), "w");
	for (int i= 0 ; i < nb_loc;i++) fprintf(fp, "%s\t%d\t%d\t%s\n", locs[i].chromosome,locs[i].start,locs[i].end,locs[i].sequence);
	fclose(fp);
	//printer(result_set);

	free(opt);

	locs_destroy(locs,&nb_loc);


	return 0;
}

void modify_coord(std::string *chr_name,localisation_t *locs,int *index , int *coord_upgrade) {

	if (strcmp(locs[*index+1].chromosome,chr_name->c_str()) == 0 ){
		printf("Index : [%d]\n",*index+1);

		locs[*index+1].start = locs[*index+1].start + *coord_upgrade;
		locs[*index+1].end   = locs[*index+1].end + *coord_upgrade;

	 }

}

bool startsWith(const char *a, const char *b)
{
   if(strncmp(a, b, strlen(b)) == 0) return 1;
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
