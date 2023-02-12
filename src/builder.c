#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define JAVASCRIPT(src) #src

void usage(void) {
    printf("Usage: waphics <file.c> <width> <height>\n");
    exit(1);
}

int main(int argc, char **argv) {
    if (argc < 4) {
        usage();
    }

    const char *javascript = JAVASCRIPT(
        function _render(instance, ctx, func) {
            image = get_image(instance, instance.exports.run());
            ctx.putImageData(image, 0, 0);
            window.requestAnimationFrame(func);
        }
        (async () => {
            function render() {
                _render(instance, ctx, render);
            }
            current_key = null;
            function jfloor(x) {
                return Math.floor(x);
            }
            function jsqrt(x) {
                return Math.sqrt(x);
            }
            function jabs(x) {
                return Math.abs(x);
            }
            function jprint(x) {
                console.log(x);
            }
            function jsin(x) {
                return Math.sin(x);
            }
            var keyCode;
            function get_key(key) {
                document.addEventListener(
                    "keydown",
                    function(event) {
                        keyCode = event.keyCode;
                    },
                );
                document.addEventListener(
                    "keyup",
                    function(event) {
                        if (event.keyCode == keyCode) keyCode = null;
                    },
                );
                if (keyCode == key) return 1;
                return 0;
            }
                
            function play_sound(path) {
                var size = 1;
                var array = new Uint8Array(buffer, path, size);
                while (array[array.length - 1] != 0) {
                    size++;
                    array = new Uint8Array(buffer, path, size);
                }
                array = new Uint8Array(buffer, path, size-1);
                const decoder = new TextDecoder();
                const string = decoder.decode(array);
                var audio = new Audio(string);
                audio.play();
            }

            var c = document.getElementById("canvas" ,{"alpha": false});
            var ctx = c.getContext("2d");

            const w = await WebAssembly.instantiateStreaming(fetch("output.wasm"), {"env": {"jsin": jsin, "play_sound": play_sound, "jfloor": jfloor, "jprint": jprint, "jsqrt": jsqrt, "jabs": jabs, "get_key": get_key}});
            const buffer = w.instance.exports.memory.buffer;
            const instance = w.instance;
            instance.exports.init();
            window.requestAnimationFrame(render);

        })();
    );

    FILE *js_file = fopen("javascript.js", "w");
    fprintf(js_file, javascript);
    fclose(js_file);

    const char *html = "<html>\n<body>\n<canvas id=\"canvas\" width=\"%s\" height=\"%s\">\n</canvas>\n<script>\nfunction get_image(instance, pixels)\n{\n    return new ImageData(new Uint8ClampedArray(instance.exports.memory.buffer, pixels, %d*%d*4), %d);\n}\n</script>\n<script src=\"javascript.js\"></script>\n</body>\n</html>";
    char string[200];
    snprintf(string, 200, "clang --target=wasm32 -nostdlib -Wl,--no-entry -Wl,--export-all -Wl,--allow-undefined -o output.wasm %s", argv[1]);
    system(string);    
    FILE *file = fopen("index.html", "w");
    fprintf(file, html, argv[2], argv[3], atoi(argv[2]), atoi(argv[3]), atoi(argv[2]));
    fclose(file);
    return 0;
}
