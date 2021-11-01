#include "str_slice.h"

struct uString {
    unsigned char *buf;
    unsigned int len;
    unsigned int cap;
    unsigned int chunk_size;
};

typedef struct uString UString;

UString
ustring_new(unsigned int chunk_size);

// Returns true on success
bool
ustring_push(UString *string, wint_t codept);

wint_t
ustring_pop(UString *string);

void
ustring_reserve(UString *string, unsigned int n);

void
ustring_append(UString *string);
