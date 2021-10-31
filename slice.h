// Don't free a ptr recieved from a slice

// A slice of bytes
struct Bytes {
    char *buf;
    unsigned int len;
};

struct Bytes
bytes_new(char *buf, int len);

// A tool for splitting up memory
struct Slice {
    void *buf;
    unsigned int len;
};

struct Slice
slice_new(void *buf, unsigned int len);

struct Slice
slice_from_bytes(struct Bytes bytes);

struct Bytes
bytes_from_slice(struct Slice slice, unsigned int size);

// Can fail. Check if buf is NULL
struct Slice
reslice(struct Slice slice, unsigned int size, unsigned int start, unsigned int end);

// Can fail. Check if buf is NULL
struct Bytes
reslice_bytes(struct Bytes bytes, unsigned int start, unsigned int end);
