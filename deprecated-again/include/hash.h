#ifndef KOALA_HASH_H
#define KOALA_HASH_H

struct koala;

long
koala_hash(struct koala *koala, const void *key, long len);

#endif // !KOALA_HASH_H
