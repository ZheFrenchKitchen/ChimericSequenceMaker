#ifndef PATCH_DEALER_H
#define PATCH_DEALER_H

#include <stdint.h>

typedef struct {
	int g;
} patch_options_t;

#ifdef __cplusplus
extern "C" {
#endif

	patch_options_t *patch_options_init();


#ifdef __cplusplus
}
#endif

#endif
