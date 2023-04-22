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
        for (let i = 0; i < 24; i++) {
            Module[97 + i] = 0;
        }

        function down(e) {
            Module[e.keyCode] = 1;
        }

        function up(e) {
            Module[e.keyCode] = 0;
        }

        document.addEventListener("keydown", down);
        document.addEventListener("keyup", up);

        function _render() {        
            var c = document.getElementById("canvas" ,{"alpha": false});
            var ctx = c.getContext("2d");
            let pixels = Module.ccall('render', // name of C function 
                "number", // return type
                null, // argument types
                null // arguments
            );
            var buffer = new Uint8ClampedArray(Module.HEAPU8.buffer, pixels, width*height*channels);
            var img = new ImageData(buffer, width);   
            ctx.putImageData(img, 0, 0);
            window.requestAnimationFrame(_render);
            Module["key"] = null;
        }

        Module.onRuntimeInitialized = () => {
            Module.ccall("init");
            window.requestAnimationFrame(_render);
        }
    );

    FILE *js_file = fopen("javascript.js", "w");
    fprintf(js_file, javascript);
    fclose(js_file);

    const char *html = "<script src='a.out.js'></script><script>let width = %d;\nlet height = %d;\nlet channels = 4;\n</script><canvas id='canvas' width=%d height=%d></canvas><script src='javascript.js'></script>";
    char string[200];
    snprintf(string, 200, "emcc %s -sEXPORTED_FUNCTIONS=_render,_init -sEXPORTED_RUNTIME_METHODS=ccall,cwrap --preload-file assets/*/*.png", argv[1]);
    system(string);    
    FILE *file = fopen("index.html", "w");
    fprintf(file, html, atoi(argv[2]), atoi(argv[3]), atoi(argv[2]), atoi(argv[3]));
    fclose(file);
    return 0;
}
