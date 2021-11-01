# include "ustring.h"
# include <stdlib.h>

UString
ustring_new(unsigned int chunk_size) {
    UString string;
    string.buf = NULL;
    string.len = 0;
    string.cap = 0;
    string.chunk_size = chunk_size;
    return string;
}

char
create_tail_byte(wint_t *codept) {
    unsigned char cut = *codept;
    cut = cut & 63;
    *codept >>= 6;
    return cut | 128;
}

char
create_head_byte(unsigned char num_bytes, wint_t codept) {
    unsigned char cut = codept;
    return cut | ~(255 >> num_bytes);
}

bool
ustring_push(UString *string, wint_t codept) {
    unsigned char num_bytes = wide_length_utf8(codept);
    // Exit for errors
    if (num_bytes == 0) {
        return false;
    }

    // Realloc buffer
    if (string->len + 4 > string->cap) {
        ustring_reserve(string, string->chunk_size);
    }

    // Make tail bytes
    unsigned int i;
    for (i = 1; i < num_bytes; i++) {
        // Recalcs so it's never done for ASCII
        // Probably inconsequential and optimized out anyway
        unsigned int idx = (string->len + num_bytes) - i;
        string->buf[idx] = create_tail_byte(&codept);
    }

    // Make head byte
    string->buf[string->len] = create_head_byte(num_bytes, codept);

    // Correct len
    string->len += num_bytes;
    return true;
}

void
ustring_reserve(UString *string, unsigned int n) {
    string->buf = realloc(string->buf, string->cap + n);
}

wint_t
ustring_pop(UString *string) {
    if (string->len == 0) {
        return ECHAR;
    }
    unsigned int num_bytes;
    for (num_bytes = 1; num_bytes < 4; num_bytes++) {
        unsigned char byte = string->buf[string->len - num_bytes];
        // 192 = 11000000
        if ((byte & 192) != 128) {
            break;
        }
    }
    StrSlice str = str_slice_new_unchecked(bytes_new((char *) &string->buf[string->len - num_bytes], num_bytes));
    return str_slice_next_char(&str);
}
