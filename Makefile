# Define default C compiler: CC
CC = clang
DESTDIR = $HOME/bin

output.wasm: 
	${CC} --target=wasm32 -nostdlib -Wl,--no-entry -Wl,--export-all -Wl,--allow-undefined -o output.wasm main.c

install: src/builder.c
	${CC} -Wall -Wextra -pedantic -o waphics src/builder.c
	${CC} -Wall -Wextra -pedantic -o waphics_image_load tools/image_loader.c -lm
	# cp waphics ${DESTDIR}
	# cp waphics_image_load ${DESTDIR}
	rm waphics
	rm waphics_image_load

clean:
	rm waphics
	rm waphics_image_load

