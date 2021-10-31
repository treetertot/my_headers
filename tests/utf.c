#include <stdio.h>
#include "../str_slice.h"
#include "../ustring.h"

int main() {
    struct StrSlice cheesepref = str_slice_from_nulterm("I like cheese");
    wint_t i = str_slice_next_char(&cheesepref);
    if (i != 'I')
        return 1;

    char buf[] = {0b11010001, 0b10100001};
    struct StrSlice duo = str_slice_new_unchecked(bytes_new(buf, 2));
    wint_t val = str_slice_next_char(&duo);
    wint_t target = 0b10001100001;
    if (val != target) {
        return 2;
    }
    struct UString string = ustring_new(8);
    ustring_push(&string, target);
    if (ustring_pop(&string) != target) {
        return 3;
    }
    return 0;
}
