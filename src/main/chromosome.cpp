#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#include "../../include/main/chromosome.h"

//Chromosome *chromosome_init(char *chrom_name_file_path){

//	return;
//}
int nb_chr_file = 0;

std::multimap<std::time_t,boost::filesystem::path> list_chromosomes(char *path_to_dir)
{
		  boost::filesystem::path someDir(path_to_dir);
		  boost::filesystem::directory_iterator end_iter;
		  typedef std::multimap<std::time_t, boost::filesystem::path> result_set_t;
		  result_set_t result_set;

		  if ( boost::filesystem::exists(someDir) && boost::filesystem::is_directory(someDir))
		  {
		    for( boost::filesystem::directory_iterator dir_iter(someDir) ; dir_iter != end_iter ; ++dir_iter)
		    {
		      if (boost::filesystem::is_regular_file(dir_iter->status()) )
		      {
		    	  const char *cstr = dir_iter->path().stem().string().c_str();

		    	   if(strstr(cstr, "chr") != NULL) {
		    		   nb_chr_file++;
		    		   result_set.insert(result_set_t::value_type(boost::filesystem::last_write_time(dir_iter->path()), *dir_iter));

		    	  }

		      }
		    }
		  }

	return result_set;

}

void chromosome_print(Chromosome *chromosome)
{
	printf("Chromosome : [%s]\n", chromosome->name);

}

void chromosome_destroy(Chromosome *chromosome)
{
		 assert(chromosome != NULL);

		 free(chromosome->name);
		 free(chromosome->sequence);

	free(chromosome);
}
