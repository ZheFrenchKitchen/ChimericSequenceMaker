#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#include "../../include/main/sequence.h"

//Chromosome *chromosome_init(char *chrom_name_file_path){

//	return;
//}
int nb_file = 0;

std::vector<boost::filesystem::path> list_sequences(char *path_to_dir)
{
		  boost::filesystem::path someDir(path_to_dir);
		  boost::filesystem::directory_iterator end_iter;
		  typedef std::vector<boost::filesystem::path> result_set_t;
		  result_set_t result_set;

		  if ( boost::filesystem::exists(someDir) && boost::filesystem::is_directory(someDir))
		  {
		    for( boost::filesystem::directory_iterator dir_iter(someDir) ; dir_iter != end_iter ; ++dir_iter)
		    {
		      if (boost::filesystem::is_regular_file(dir_iter->status()) )
		      {
		    	  const char *cstr = dir_iter->path().stem().string().c_str();
		    	  // user can define 3 types of sequence reference followed by a number
		    	   if ( (strstr(cstr, "chr") != NULL) or (strstr(cstr, "exon") != NULL) or (strstr(cstr, "seq") != NULL) ){
		    		   nb_file++;
		    		   result_set.push_back(*dir_iter);

		    	  }

		      }
		    }
		  }

	return result_set;

}

void sequence_reference_print(sequence *sequence)
{
	printf("SequenceReference : [%s]\n", sequence->name);

}

void  sequence_destroy(sequence *sequence)
{
		 assert(sequence != NULL);

		 free(sequence->name);
		 free(sequence->atgc_suite);

	free(sequence);
}
