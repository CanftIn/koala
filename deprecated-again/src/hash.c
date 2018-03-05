#include "../include/hash.h"
#include "../include/koala.h"

#include <stdint.h>

uint32_t
djb_hash(const void *key, long len, long seed)
{
	int i;
	unsigned int h;
	const unsigned char *p;

	p = key;
	h = ((unsigned int)seed & 0xffffffff);
	for (i = 0; i < len; i++) {
		h = (unsigned int)(33 * (long)h ^ p[i]);
	}

	return h;
}

long
koala_hash(struct koala *koala, const void *key, long len)
{
    return djb_hash(key, len, koala->k_random);
}