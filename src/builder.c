#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main(int argc, char **argv) {
    assert(argc == 3);
    const char *html = "<html>\n<body>\n<canvas id=\"canvas\" width=\"%s\" height=\"%s\">\n</canvas>\n<script>\nfunction get_image(instance, pixels)\n{\n    return new ImageData(new Uint8ClampedArray(instance.exports.memory.buffer, pixels, %d*%d*4), %d);\n}\n</script>\n<script src=\"javascript.js\"></script>\n</body>\n</html>";
    system("clang --target=wasm32 -nostdlib -Wl,--no-entry -Wl,--export-all -Wl,--allow-undefined -o output.wasm main.c");    
    FILE *file = fopen("index.html", "w");
    fprintf(file, html, argv[1], argv[2], atoi(argv[1]), atoi(argv[2]), atoi(argv[1]));
    fclose(file);
    return 0;
}
