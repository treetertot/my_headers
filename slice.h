// Don't free a ptr recieved from a slice

// A slice of bytes
struct _Bytes {
    char *buf;
    unsigned int len;
};

typedef struct _Bytes Bytes;

Bytes
bytes_new(char *buf, int len);

// A tool for splitting up memory
struct _Slice {
    void *buf;
    unsigned int len;
};

typedef struct _Slice Slice;

Slice
slice_new(void *buf, unsigned int len);

Slice
slice_from_bytes(Bytes bytes);

Bytes
bytes_from_slice(Slice slice, unsigned int size);

// Can fail. Check if buf is NULL
Slice
reslice(Slice slice, unsigned int size, unsigned int start, unsigned int end);

// Can fail. Check if buf is NULL
Bytes
reslice_bytes(Bytes bytes, unsigned int start, unsigned int end);
