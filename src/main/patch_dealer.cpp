#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <sys/stat.h>

#include "../../include/main/patch_dealer.h"
#include "../../include/main/localisation.h"
#include "../../include/main/chromosome.h"


void printer(std::multimap<std::time_t,boost::filesystem::path> pN);

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

	std::multimap<std::time_t,boost::filesystem::path> result_set = list_chromosomes(argv[optind +1]);
	extern int nb_chr_file;
	fprintf(stderr, " Nbr chromosomes [%d]\n", nb_chr_file);

	 std::multimap<std::time_t,boost::filesystem::path>::iterator it = result_set.begin();
	  while(it != result_set.end())
	  {
			//std::cout<<"Key = "<<it->first<<"    Value = "<<it->second<<std::endl;
			std::cout<<"Path = "<<it->second<<std::endl;

			FILE *file_ref;
			char line[100];

			ref = fopen(it->second.string().c_str(), "r");

			int count = 0;

				int r,s;
				while((r=fgetc(ref))!=EOF) {

					if(r=='>') {
						fputc(r,stdout);
						while((r=fgetc(ref))!=EOF && r!='\n') { fputc(r,stdout); }
						printf("\n");
						continue;
					}

					/* Print line feed to keep fasta file readable */
					/* Only if we are not in [start, stop] */
					if(isspace(r)) {
						if ( count < start || count > stop ) {
							fputc(r,stdout);
						}
						continue;
					}

					/* A,C,G,T or N has just been read */
					++count;

			   	    if (count<start) { fputc(r,stdout);  }

			   	    else if (count==start) {
			   	    	/* Insert the provided sequence here */
			   	    	//while((s=fgetc(seq))!=EOF) { fputc(s,stdout);}
			   	    	fputs(s,stdout)
			   	    }
			   	    	else if (count<=stop) { continue; }

			   	    			else {fputc(r,stdout); }

				}

				fclose( seq );
				fclose( ref );

 		fclose(file_ref);

		it++;
	  }

	free(opt);


	extern int nb_loc;

	locs_print(locs,&nb_loc);
	locs_destroy(locs,&nb_loc);

	return 0;
}

//This method prints the vector
void printer(std::multimap<std::time_t,boost::filesystem::path> pN,int *nb_chr)
{
	  std::multimap<std::time_t,boost::filesystem::path>::iterator it = pN.begin();
	  while(it != pN.end())
	  {
	    std::cout<<"Key = "<<it->first<<"    Value = "<<it->second<<std::endl;
	    it++;

	  }
}


patch_options_t *patch_options_init()
{
	// C++ need casting for malloc/calloc not C
	patch_options_t *o = (patch_options_t*)calloc(1, sizeof(patch_options_t));
	// Could set default value here
	//o->a = 1; o->b = 3; o->h = 0;
	return o;
}
