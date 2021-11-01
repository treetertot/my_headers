# include "slice.h"

Bytes
bytes_new(char *buf, int len) {
    Bytes bs;
    bs.buf = buf;
    bs.len = len;
    return bs;
}

Slice
slice_new(void *buf, unsigned int len) {
    Slice slice;
    slice.buf = buf;
    slice.len = len;
    return slice;
}

Slice
slice_from_bytes(Bytes bytes) {
    return slice_new(bytes.buf, bytes.len);
}

Bytes
bytes_from_slice(Slice slice, unsigned int size) {
    return bytes_new(slice.buf, slice.len * size);
}

Slice
reslice(Slice slice, unsigned int size, unsigned int start, unsigned int end) {
    if (start > slice.len || end > slice.len || start > end)
        return slice_new(0, 0);
    return slice_new(slice.buf + (start * size), end - start);
}

Bytes
reslice_bytes(Bytes bytes, unsigned int start, unsigned int end) {
    if (start > bytes.len || end > bytes.len || start > end)
        return bytes_new(0, 0);
    else
        return bytes_new(bytes.buf + start, end - start);
}
