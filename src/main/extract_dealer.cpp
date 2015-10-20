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

#include "../../include/main/extract_dealer.h"
#include "../../include/main/localisation.h"
#include "../../include/main/sequence.h"


//void printer(std::vector<boost::filesystem::path> pN);
bool startsWithThis(const char *a, const char *b);


int extract(int argc, char *argv[])
{

	//If the resulting value of optind+1 is greater than argc, this indicates a missing option-argument
	// yes we add a file
	if (optind + 2 > argc) {

		fprintf(stderr, "\n");
		fprintf(stderr, "Usage:   chimericSequenceMaker extract [options] </path/to/ListofPositionsToExtract.txt> </path/to/DirectoryContainingSequenceReferenceFiles>\n");
		fprintf(stderr, "\n");

		return 1;
	}

	// Parse file for initiate coordinates to modify
	localisation_t *locs =  localisation_init(argv,&optind);

	// Class variable (incremented each time there is a line - see localisation.h)
	extern int nb_loc;

	// Get path  /path/to/positions.txt
	boost::filesystem::path path_locs_file(argv[optind]);
	std::string path_to_output = path_locs_file.parent_path().string();

	// List of path where to find sequences of reference /path/to/seq1,2,3....txt
	std::vector<boost::filesystem::path> result_set = list_sequences(argv[optind+1]);

	// Directory path with all references
	std::string path_all_sequences = result_set[0].parent_path().string();

	fprintf(stderr,"path_all_sequences : [%s]\n",path_all_sequences.c_str());

	// Class variable (incremented each time there is a sequence reference to treat - see localisation.h)
	extern int nb_file;

	fprintf(stderr, "Nbr Sequences [%d] \n", nb_file);
	fprintf(stderr, "Nbr Loc [%d] \n", nb_loc);


	// Create Direct to Ouput Sequence Modified
	boost::filesystem::create_directory(path_to_output+"/extractedChimericSequences");
	boost::filesystem::path dir(path_to_output+"/extractedChimericSequences");

	std::vector<boost::filesystem::path>::iterator it = result_set.begin();

	// First of all , Update of the coordinates
	for (int i=0; i < nb_loc;i++){

		fprintf(stderr,"seq_name : [%s]\n", locs[i].seq_name);

		std::string path_to_sequence = path_all_sequences+"/"+locs[i].seq_name+".fa";
		fprintf(stderr, "path to sequence [%s] \n", path_to_sequence.c_str());

		ifstream file_ref;    // Create an input file stream.
		file_ref.open(path_to_sequence.c_str());  // Use it to

		if(!file_ref)
		{
			printf( "Extension file for reference sequence file is not supported.  \n");
			printf( "Possible errors.  \n");
			fprintf(stderr,"File doesn't exist :  [%s]\n", locs[i].seq_name);
			fprintf(stderr,"Extension must be .fa for  [%s]\n", locs[i].seq_name);
			exit(EXIT_FAILURE);
		}

		std::string id_name,line,sequence;
		getline(file_ref,id_name);  // Get the first line from the file, if any.

		if (startsWithThis(id_name.c_str(),">")) { id_name.erase(id_name.begin()); }
		else {
				fprintf(stderr, "The application has stopped unexpectedly \nSequence format is not as expected  ! \n");
				exit(EXIT_FAILURE);
		 }

		while( std::getline( file_ref, line )){  sequence += line; }

		if (locs[i].start > locs[i].end ){
			fprintf(stderr, "The application has stopped unexpectedly \nPositions are not well formated. End position is inferior to Start position somewhere in your input file  ! \n");
			printf("\n");
			fprintf(stderr,"seq_name : [%s]\n", locs[i].seq_name);
			fprintf(stderr,"Start : [%d]\n", locs[i].start);
			fprintf(stderr,"End : [%d]\n", locs[i].end);
			fprintf(stderr,"NAME_REGION : [%s]\n", locs[i].sequence); //  I use sequence but i shouldn't...trick that make stuff easier to do but not well designed
			exit(EXIT_FAILURE);
		}

		std::string substring_sequence = sequence.substr (locs[i].start-1,locs[i].end-locs[i].start+1);

		std::string output_new_sequence =    dir.string()+"/"+locs[i].region_name+".fa";
		FILE *new_sequence_p = fopen(output_new_sequence.c_str(), "w");
		fprintf(new_sequence_p, ">");

		fprintf(new_sequence_p, "%s\n",locs[i].region_name);

		for ( int index = 0 ; index < substring_sequence.length(); index+=50)   fprintf(new_sequence_p, "%s\n", substring_sequence.substr(index,50) .c_str());
		fclose(new_sequence_p);

	}

	locs_destroy(locs,&nb_loc);

	return 0;
}

/*
##############################################################################################################
#########################						Methods								##########################
##############################################################################################################
*/

// Tcheck if a string begin with an another string
bool startsWithThis(const char *a, const char *b)
{
   if(strncmp(a, b, strlen(b)) == 0) return 1;
   return 0;
}

// Allocation of memory for options
extract_options_t *extract_options_init()
{
	// C++ need casting for malloc/calloc not C
	extract_options_t *o = (extract_options_t*) calloc(1, sizeof(extract_options_t));
	// Could set default value here
	//o->g = 0;
	//o->a = 1; o->b = 3; o->h = 0;
	return o;
}
