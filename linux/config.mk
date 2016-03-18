PREFIX = /usr

X11INC = /usr/include/X11
X11LIB = /usr/lib/X11

INCS = -I${X11INC}
LIBS = -L${X11LIB} -lX11 -lXrandr

CFLAGS = -Wall -Os ${INCS}
LDFLAGS = ${LIBS}

CC = gcc
