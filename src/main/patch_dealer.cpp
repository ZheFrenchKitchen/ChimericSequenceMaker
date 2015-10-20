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
#include "../../include/main/sequence.h"


void printer(std::vector<boost::filesystem::path> pN);
bool startsWith(const char *a, const char *b);
void modify_coord(std::string *id_name,localisation_t *locs,int *index , int *coord_upgrade) ;


int patch(int argc, char *argv[])
{
	patch_options_t *opt;
	opt = patch_options_init();

	int c;
	while ((c = getopt(argc, argv, "g")) >= 0) {
		switch (c) {
		//case 'g': opt->g = atoi(optarg); break;
		case 'g': opt->g  =1;  break;
		default: return 1;
		}
	}
	//If the resulting value of optind+1 is greater than argc, this indicates a missing option-argument
	// yes we add a file
	if (optind + 2 > argc) {

		fprintf(stderr, "\n");
		fprintf(stderr, "Usage:   chimericSequenceMaker patch [options] </path/to/ListofPositionsToTransform.txt> </path/to/DirectoryContainingSequenceReferenceFiles> \n\n");
		//fprintf(stderr, "Options: -g  Transform genetic coordinates in a file located in the same directory as </path/to/ListofPositionsToTransform.txt> [%d]\n", opt->g);
		fprintf(stderr, "\n");

		return 1;
	}

	// Parse file for initiate coordinates to modify
	localisation_t *locs =  localisation_init(argv,&optind);

	// Get path  /path/to/positions.txt
	boost::filesystem::path dirToLocs(argv[optind]);
	std::string path_to_output = dirToLocs.parent_path().string();

	// Class variable (incremented each time there is a line - see localisation.h)
	extern int nb_loc;

	// Sorted coordinates by chr and start
	qsort(locs, nb_loc, sizeof(localisation_t), compare_locations);

	// List of path where to find sequences of reference /path/to/seq1,2,3....txt
	std::vector<boost::filesystem::path> result_set = list_sequences(argv[optind+1]);

	std::sort(result_set.begin(), result_set.end());

	// Class variable (incremented each time there is a sequence reference to treat - see localisation.h)
	extern int nb_file;

	fprintf(stderr,"\n");
	fprintf(stderr, "Nbr Sequences [%d] \n", nb_file);
	fprintf(stderr, "Nbr Locations [%d] \n", nb_loc);
	fprintf(stderr,"\n");

	// Create Direct to Ouput Sequence Modified
	boost::filesystem::create_directory(path_to_output+"/chimericSequences");
	boost::filesystem::path dir(path_to_output+"/chimericSequences");

	locs_print(locs,&nb_loc);

	std::vector<boost::filesystem::path>::iterator it = result_set.begin();

	// FOREACH FILE_PATH
	while(it != result_set.end())
	{
			std::cout<<"Path = "<<*it<<std::endl;

			ifstream file_ref;    // Create an input file stream.
			file_ref.open(it->string().c_str());  // Use it to

			std::string id_name,line,sequence;
			getline(file_ref,id_name);  // Get the first line from the file, if any.

			if (startsWith(id_name.c_str(),">")) { id_name.erase(id_name.begin()); }
			else {
					fprintf(stderr, "The application has stopped unexpectedly \nSequence format is not as expected  ! \n");
					exit(EXIT_FAILURE);
			 }

		    while( std::getline( file_ref, line )){  sequence += line; }

		    int coord_cursor = 0;

		    // First of all , Update of the coordinates
		    for (int i=0; i < nb_loc;i++){


		    	if (id_name.compare(locs[i].seq_name) == 0) {

		    		if (locs[i].start > locs[i].end ){
		    			fprintf(stderr, "The application has stopped unexpectedly \nPositions are not well formated. End position is inferior to Start position somewhere in your input file  ! \n");
		    			printf("\n");
		    			fprintf(stderr,"seq_name : [%s]\n", locs[i].seq_name);
		    			fprintf(stderr,"Start : [%d]\n", locs[i].start);
		    			fprintf(stderr,"End : [%d]\n", locs[i].end);
		    			fprintf(stderr,"Sequence : [%s]\n", locs[i].sequence);
		    			exit(EXIT_FAILURE);
		    		}

		    		coord_cursor += ( strlen(locs[i].sequence) - (locs[i].end -locs[i].start+1) );

		    		//printf("\n");
					//printf("seq_name : [%s]\n", locs[i].seq_name);
					//printf("Start : [%d]\n", locs[i].start);
					//printf("End : [%d]\n", locs[i].end);
					//printf("Sequence : [%s]\n", locs[i].sequence);
					//printf("SizeToRemove : [%d]\n", (locs[i].end -locs[i].start+1));
					//printf("SizeSequence : [%lu]\n", strlen(locs[i].sequence));
		    		//printf("NucToAddOrRemoveToNextPositionOnSameChr : [%d]\n" ,coord_cursor);
		    		//printf("\n");

					// You prevent an segment error caused by array
					if ( i + 1 < nb_loc  ) modify_coord(&id_name,locs,&i,&coord_cursor);

		    	}

			}
		    printf("Avt Seq : [%lu]\n", sequence.length());
		    printf("Avt Seq : [%s]\n", sequence.c_str());

		    // Then we want to change sequence and to save in a new file
			for (int i=0; i < nb_loc;i++){

					if (id_name.compare(locs[i].seq_name) == 0) {
						printf("seq_name : [%s]\n", locs[i].seq_name);
						printf("Start : [%d]\n", locs[i].start);
						printf("End : [%d]\n", locs[i].end);
						printf("Sequence : [%s]\n", locs[i].sequence);

						sequence.replace(locs[i].start-1,locs[i].end-locs[i].start+1,locs[i].sequence);
						printf("Sequence : [%s]\n", sequence .c_str());

					}

			}

			std::string output_new_sequence =    dir.string()+"/"+id_name+".fa";
			FILE *new_sequence_p = fopen(output_new_sequence.c_str(), "w");
			fprintf(new_sequence_p, ">");
			fprintf(new_sequence_p, "%s\n", id_name.c_str());
			printf("Aps Seq : [%lu]\n", sequence.length());
			printf("Aps Seq : [%s]\n", sequence.c_str());

			for ( int index = 0 ; index < sequence.length(); index+=50)   fprintf(new_sequence_p, "%s\n", sequence.substr(index,50) .c_str());
			fclose(new_sequence_p);

			 // TODO : FAIRE UN OPTION POUR METTRE A JOUR LA LISTE DES GENES - I M GETTING CRAZY ON THIS BUT IT SHOULD BE EASY

		it++;
	}

	path_to_output+="/";
	path_to_output+="new_positions.txt";

	//locs_print(locs,&nb_loc);

	FILE *fp = fopen(path_to_output.c_str(), "w");
	for (int i= 0 ; i < nb_loc;i++) fprintf(fp, "%s\t%d\t%d\t%s\t%s\n", locs[i].seq_name,locs[i].start,locs[i].end,locs[i].sequence,locs[i].region_name);
	fclose(fp);
	//printer(result_set);

	free(opt);
	// duplicate/derivate struct...duplicate function...ugly ugly ugly...should do some refactorisation
	locs_destroy(locs,&nb_loc);

	return 0;
}

/*
##############################################################################################################
#########################						Methods								##########################
##############################################################################################################
*/

// Tcheck if a string begin with an another string
bool startsWith(const char *a, const char *b)
{
   if(strncmp(a, b, strlen(b)) == 0) return 1;
   return 0;
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
	patch_options_t *o = (patch_options_t*) calloc(1, sizeof(patch_options_t));
	// Could set default value here
	o->g = 0;
	//o->a = 1; o->b = 3; o->h = 0;
	return o;
}
