#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

typedef struct Chromosome{
	char *name,*header,*sequence;
} chromosome;

	// Outside of externC because it uses boost library for C++ so the link stuff related won't be ok boy.
	std::vector<boost::filesystem::path> list_chromosomes (char * path_to_dir);

#ifdef __cplusplus
extern "C" {
#endif


	Chromosome *chromosome_init(char *chrom_name_file_path);

	void chromosome_destroy(chromosome *chromosome);


#ifdef __cplusplus
}
#endif

#endif
