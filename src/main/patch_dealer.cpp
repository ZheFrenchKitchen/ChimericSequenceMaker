#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "../../include/main/patch_dealer.h"
#include "../../include/main/patch.h"

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

	patcher(argv,&optind);

	free(opt);

	return 0;
}

patch_options_t *patch_options_init()
{
	// C++ need casting for malloc/calloc not C
	patch_options_t *o = (patch_options_t*)calloc(1, sizeof(patch_options_t));
	// Could set default value here
	//o->a = 1; o->b = 3; o->h = 0;
	return o;
}
