#ifndef TEST_MAIN_H
#define TEST_MAIN_H

#include <stdint.h>

typedef struct {
	int a, b, h;
} patch_options_t;

#ifdef __cplusplus
extern "C" {
#endif

	patch_options_t *patch_options_init();


#ifdef __cplusplus
}
#endif


#endif
