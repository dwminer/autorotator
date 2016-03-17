include config.mk

SRC = rotator.c
OBJ = ${SRC:.c=.o}

all: rotator

.c.o:
	@echo ${CC} $<
	@${CC} -c ${CFLAGS} $<

${OBJ}: rotate.h

rotator: ${OBJ}
	@echo ${CC} $<
	@${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	@rm -f rotator ${OBJ}
