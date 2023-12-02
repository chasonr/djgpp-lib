#!/bin/sh

# It is easiest to build djlsr206.zip from a clean directory

make clean
rm -f djlsr206.zip
zip -9rD djlsr206.zip \
copying \
copying.dj \
copying.lib \
info/dir.txi \
manifest/djlsr206.mft \
manifest/djlsr206.ver \
readme.1st \
src \
utils \
-x src/libc/c99/math/.gitignore \
-x src/libc/stubs/.gitignore \
-x src/libc/.gitignore \
-x src/dxe/.gitignore \
-x src/stub/.gitignore \
-x src/djasm/.gitignore \
-x src/.gitignore \
-x src/debug/fsdb/.gitignore \
-x src/libm/math/.gitignore
