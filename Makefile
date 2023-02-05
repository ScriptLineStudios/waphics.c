output.wasm: main.c waphics.c
	clang --target=wasm32 -nostdlib -Wl,--no-entry -Wl,--export-all -Wl,--allow-undefined -o output.wasm main.c

DESTDIR = $$HOME/bin
install: src/builder.c
	${CC} -Wall -Wextra -pedantic -o waphics src/builder.c
	${CC} -Wall -Wextra -pedantic -o waphics_extra_img_load tools/image_loader.c -lm
	cp waphics ${DESTDIR}
	cp waphics_extra_img_load ${DESTDIR}
	rm waphics
	rm waphics_extra_img_load

clean:
	rm waphics
	rm waphics_extra_img_load

