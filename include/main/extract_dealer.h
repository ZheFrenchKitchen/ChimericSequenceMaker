#ifndef PATCH_EXTRACT_H
#define PATCH_EXTRACT_H

#include <stdint.h>

typedef struct {
	int g;
} extract_options_t;

#ifdef __cplusplus
extern "C" {
#endif

extract_options_t *extract_options_init();


#ifdef __cplusplus
}
#endif

#endif
