# ifndef STR_SLICE
# define STR_SLICE

# include "slice.h"
# include <wchar.h>
# include <stdbool.h>

struct strSlice {
    Bytes bs;
};

typedef struct strSlice StrSlice;

// I might split ECHAR into multiple values
// For now it covers oob & invalid bytes
# define ECHAR 2147483648;

StrSlice
str_slice_from_nulterm(char *buf);

StrSlice
str_slice_new_unchecked(Bytes bytes);

bool
quick_validate_wide(wint_t c);

wint_t
str_slice_next_char(StrSlice *str);

unsigned char
wide_length_utf8(wint_t c);

#endif /* end of include guard: STR_SLICE */
