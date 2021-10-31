# include "slice.h"

struct Bytes
bytes_new(char *buf, int len) {
    struct Bytes bs;
    bs.buf = buf;
    bs.len = len;
    return bs;
}

struct Slice
slice_new(void *buf, unsigned int len) {
    struct Slice slice;
    slice.buf = buf;
    slice.len = len;
    return slice;
}

struct Slice
slice_from_bytes(struct Bytes bytes) {
    return slice_new(bytes.buf, bytes.len);
}

struct Bytes
bytes_from_slice(struct Slice slice, unsigned int size) {
    return bytes_new(slice.buf, slice.len * size);
}

struct Slice
reslice(struct Slice slice, unsigned int size, unsigned int start, unsigned int end) {
    if (start > slice.len || end > slice.len || start > end)
        return slice_new(0, 0);
    return slice_new(slice.buf + (start * size), end - start);
}

struct Bytes
reslice_bytes(struct Bytes bytes, unsigned int start, unsigned int end) {
    if (start > bytes.len || end > bytes.len || start > end)
        return bytes_new(0, 0);
    else
        return bytes_new(bytes.buf + start, end - start);
}
