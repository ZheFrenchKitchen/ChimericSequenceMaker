#include <stdarg.h>
#include <stdio.h>
#include "../../include/main/kstring.h"


#ifdef USE_MALLOC_WRAPPERS
#  include "../../include/main/malloc_wrap.h"
#endif

int ksprintf(kstring_t *s, const char *fmt, ...)
{
	va_list ap;
	int l;
	va_start(ap, fmt);
	l = vsnprintf(s->s + s->l, s->m - s->l, fmt, ap);
	va_end(ap);
	if (l + 1 > s->m - s->l) {
		s->m = s->l + l + 2;
		kroundup32(s->m);
		s->s = (char*)realloc(s->s, s->m);
		va_start(ap, fmt);
		l = vsnprintf(s->s + s->l, s->m - s->l, fmt, ap);
	}
	va_end(ap);
	s->l += l;
	return l;
}

