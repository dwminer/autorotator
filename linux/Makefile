include config.mk

SRC = autorotator.c
OBJ = ${SRC:.c=.o}

all: autorotator

debug: CFLAGS += -g
debug: all

.c.o:
	@echo ${CC} $<
	@${CC} -c ${CFLAGS} $<

${OBJ}: ar_rotate.h ar_serial.h

rotator: ${OBJ}
	@echo ${CC} $<
	@${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	@rm -f autorotator ${OBJ}
