This repository continues development of the DJGPP run time library.

The original source is available from any mirror of DJGPP as the archives
djcrx205.zip, djlsr205.zip and djtzs205.zip. Goals of this project are:

* to fix any bugs that might be found
* to support all of C99
* to support as much of Posix as is practical in a DOS environment
* to support the GCC \_FORTIFY\_SOURCE facility

I am cross-compiling from Linux Mint using a compiler built from the Github
repository https://github.com/dimkr/build-djgpp.git . Building natively does
not seem to work, at least on FreeDOS; the make utility crashes for no apparent
reason. I have not yet tried it on real MS-DOS.
