output.wasm: main.c waphics.c
	clang --target=wasm32 -nostdlib -Wl,--no-entry -Wl,--export-all -Wl,--allow-undefined -o output.wasm main.c

DESTDIR = $$HOME/bin
install: builder.c
	${CC} -Wall -Wextra -pedantic -o waphics builder.c
	${CC} -Wall -Wextra -pedantic -o waphics_extra_img_load tools/image_loader.c -lm
	cp waphics ${DESTDIR}
	cp waphics_extra_img_load ${DESTDIR}

clean:
	rm waphics
	rm waphics_extra_img_load

