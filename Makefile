# Define default C compiler: CC
CC = clang
# Define destribution folder: DESTDIR
DESTDIR = /usr/bin/

install: src/builder.c
	${CC} -Wall -Wextra -pedantic -o waphics src/builder.c
	${CC} -Wall -Wextra -pedantic -o waphics_image_load tools/image_loader.c -lm
	cp waphics ${DESTDIR}
	cp waphics_image_load ${DESTDIR}
	rm waphics
	rm waphics_image_load

clean:
	rm waphics
	rm waphics_image_load

