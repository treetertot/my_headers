# include "str_slice.h"
# include <wchar.h>
# include <stdbool.h>

struct StrSlice
str_slice_from_nulterm(char *buf) {
    unsigned int i;
    char current = buf[0];
    for (i = 0; current != '\0'; i++) {
        current = buf[i];
    }
    struct StrSlice str;
    str.bs.buf = buf;
    str.bs.len = i;
    return str;
}

struct StrSlice
str_slice_new_unchecked(struct Bytes bytes) {
    struct StrSlice str;
    str.bs = bytes;
    return str;
}

// Invalid codepoints are returned as errors
// Be sure to check with validate before using
// 1... means oob
// Can be checked by quick_validate_wide
wint_t
str_slice_get(struct StrSlice str, unsigned int n, unsigned char *size) {
    if (n >= str.bs.len) {
        *size = 0;
        return 1 << 31;
    }
    unsigned char first = str.bs.buf[n];
    wint_t shifted = first;

    unsigned char num_bytes = 1;
    shifted = shifted << 24;
    if (__builtin_clz(shifted) == 0) {
        wint_t flipped = ~shifted;
        num_bytes = __builtin_clz(flipped);
        if (num_bytes + n - 1> str.bs.len) {
            *size = 0;
            return 1 << 31;
        }
    }
    unsigned char mask = 255 >> num_bytes;

    wint_t c = first & mask;
    unsigned char i;
    for (i = 1; i < num_bytes; i++) {
        c = c << 8;
        c = c | str.bs.buf[i];
    }
    *size = num_bytes;
    return c;
}

void
shift_str_slice(struct StrSlice *str, unsigned int n) {
    str->bs.buf = &str->bs.buf[n];
    str->bs.len -= n;
}

wint_t
str_slice_next_char(struct StrSlice *str) {
    const unsigned char TMASK = 255 >> 2;
    if (str->bs.len == 0) {
        return ECHAR;
    }

    unsigned char first = str->bs.buf[0];
    wint_t shifted = first;
    shifted = shifted << 24;
    unsigned char num_bytes = __builtin_clz(~shifted);
    switch (num_bytes) {
        case 0:
            shift_str_slice(str, 1);
            return first;
        // 2, 3, and 4 are the only other valid values
        case 2:
        case 3:
        case 4:
            break;
        default:
            return ECHAR;
    }
    if (num_bytes > str->bs.len) {
        return ECHAR;
    }

    unsigned char fmask = 255 >> num_bytes;
    wint_t c = first & fmask;
    unsigned char i;
    for (i = 1; i < num_bytes; i++) {
        c = c << 6;
        unsigned char nb = str->bs.buf[i];
        unsigned char isolated = nb & ~TMASK;
        if (isolated != 128) {
            return ECHAR;
        }
        wint_t t = nb & TMASK;
        c = c | t;
    }

    shift_str_slice(str, num_bytes);
    return c;
}

bool
quick_validate_wide(wint_t c) {
    return __builtin_clz(c) > 11;
}

// Get the number of bytes needed to encode a wide char in UTF-8
// Gives zero for invalid codepoints
unsigned char
wide_length_utf8(wint_t codept) {
    wint_t normalized = codept | 1000000;
    // 0000 0000 0004 4444 3333 3222 2111 1111
    if (__builtin_clz(normalized) == 25) {
        return 1;
    } else if (__builtin_clz(normalized) >= 21) {
        return 2;
    } else if (__builtin_clz(normalized) >= 16) {
        return 3;
    } else if (__builtin_clz(normalized) >= 11) {
        return 4;
    } else {
        return 0;
    }
}
