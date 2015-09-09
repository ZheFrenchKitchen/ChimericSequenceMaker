#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../../include/main/foo.h"
#include "../../include/shared/calc_mean.h"
#include "../../include/static/calc_sum.h"

int main (int argc, char *argv[])
{
  if (argc < 2)
    {
    fprintf(stdout,"Usage: %s number\n",argv[0]);
    return 1;
    }
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
}
