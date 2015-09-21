#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

#include "../../include/shared/calc_mean.h"
#include "../../include/static/calc_sum.h"
#include "../../include/main/foo.h"
#include "../../include/main/kstring.h"
#include "../../include/main/utils.h"

#ifndef PACKAGE_VERSION
#define PACKAGE_VERSION "1.0"
#endif

//valgrind --leak-check=yes ./install/bin/ChimericGenomeMaker patch -a 10 -b 13 /Users/JP/Desktop/positions.txt /kikou

char *bwa_pg;

int patch(int argc, char *argv[]);

/*void printer(std::multimap<std::time_t,boost::filesystem::path> pN);*/
static int usage()
{
	fprintf(stderr, "\n");
	fprintf(stderr, "Program: chimericGenomeMaker \n");
	fprintf(stderr, "Version: %s\n", PACKAGE_VERSION);
	fprintf(stderr, "Usage:   chimericGenomeMaker <command> [options]\n\n");
	fprintf(stderr, "Command: patch         patch sequences of the chromosomes \n");
	fprintf(stderr, "         reshape       modify sequence length of each line in chromosome file\n");
	fprintf(stderr, "\n");
	fprintf(stderr,
"Note: To use CGM, you need to first download each chromosome sequence for your genome of interest.\n"
"      You must use first 'patch' and then 'reshape'.\n"
"      first. For more documentation , 'See github https://github.com/ZheFrenchKitchen'.\n\n");
	return 1;
}


int main (int argc, char *argv[])
{

	int i, ret;
	double t_real;
	t_real = realtime();

	// Don't understand what 'ksprintf' is used for
	kstring_t pg = {0,0,0};
	for (i = 1; i < argc; ++i) ksprintf(&pg, " %s", argv[i]);
	bwa_pg = pg.s;

    if (argc < 2) return usage();

	else if (strcmp(argv[1], "patch") == 0) ret = patch(argc-1, argv+1);
	else {
			fprintf(stderr, "[main] unrecognized command '%s'\n", argv[1]);
			return 1;
		}

    err_fflush(stdout);
    err_fclose(stdout);

    if (ret == 0) {
    		fprintf(stderr, "[%s] Version: %s\n", __func__, PACKAGE_VERSION);
    		fprintf(stderr, "[%s] CMD:", __func__);
    		for (i = 0; i < argc; ++i)
    			fprintf(stderr, " %s", argv[i]);
    		fprintf(stderr, "\n[%s] Real time: %.3f sec; CPU: %.3f sec\n\n", __func__, realtime() - t_real, cputime());
    	}

	free(bwa_pg);

	return ret;

/*
 * Old stuff i keep to have  a trace on how doing dynamic or static librairies
 *
  double inputValue = atof(argv[1]);
  double outputValue = sqrt(inputValue);

  fprintf(stdout,"The square root of %g is %g\n", inputValue, outputValue);

  double v1, v2, m;
  v1 = 5.2;
  v2 = 7.9;

  m  = mean(v1, v2);
  printf("The mean of %3.2f and %3.2f is %3.2f\n", v1, v2, m);
  m  = sum(v1, v2);
  printf("The sum of %3.2f and %3.2f is %3.2f\n", v1, v2, m);

  return 0;
*/
}

