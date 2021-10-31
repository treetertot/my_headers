project('joshmem', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])

lib = library('joshmem',
           'slice.c',
           'str_slice.c',
           'ustring.c')

utf = executable('charex', 'tests/utf.c', link_with : lib)
test('character extraction', utf)
