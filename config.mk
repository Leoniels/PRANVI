# stlp version
VERSION = 0.2

# paths
PREFIX = /usr/local
MANPREFIX = $(PREFIX)/share/man

# includes and libs
#INCS = -I./$(SRCD)
GMP = -lgmp
LIBS = $(GMP)

# flags
#CPPFLAGS = -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_XOPEN_SOURCE=700 -D_POSIX_C_SOURCE=200809L -DVERSION=\"$(VERSION)\"
CFLAGS   = -std=c99 -pedantic -Wall -Os #$(INCS) $(CPPFLAGS)
LDFLAGS  = $(LIBS)

# compiler and linker
#CC = tcc
