#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

typedef struct Sequence{
	char *name,*header,*atgc_suite;
} sequence;

	// Outside of externC because it uses boost library for C++ so the link stuff related won't be ok boy.
	std::vector<boost::filesystem::path> list_sequences (char * path_to_dir);

#ifdef __cplusplus
extern "C" {
#endif

	Sequence *sequence_init(char *seq_name_file_path);

	void sequence_destroy(sequence *sequence);


#ifdef __cplusplus
}
#endif

#endif
