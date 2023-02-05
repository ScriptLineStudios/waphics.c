output.wasm: main.c renderer.c
	clang --target=wasm32 -nostdlib -Wl,--no-entry -Wl,--export-all -Wl,--allow-undefined -o output.wasm main.c

DESTDIR = $$HOME/bin
install: builder.c
	${CC} -Wall -Wextra -pedantic -o builder builder.c
	${CC} -Wall -Wextra -pedantic -o img_loader tools/image_loader.c -lm
	cp builder ${DESTDIR}
	cp img_loader ${DESTDIR}

clean:
	rm builder
	rm img_loader

