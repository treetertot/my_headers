#include "str_slice.h"

struct UString {
    unsigned char *buf;
    unsigned int len;
    unsigned int cap;
    unsigned int chunk_size;
};

struct UString
ustring_new(unsigned int chunk_size);

// Returns true on success
bool
ustring_push(struct UString *string, wint_t codept);

wint_t
ustring_pop(struct UString *string);

void
ustring_reserve(struct UString *string, unsigned int n);

void
ustring_append(struct UString *string);
