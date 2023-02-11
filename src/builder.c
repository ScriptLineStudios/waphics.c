#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void usage(void) {
    printf("Usage: waphics <file.c> <width> <height>\n");
    exit(1);
}

int main(int argc, char **argv) {
    if (argc < 4) {
        usage();
    }
    const char *html = "<html>\n<body>\n<canvas id=\"canvas\" width=\"%s\" height=\"%s\">\n</canvas>\n<script>\nfunction get_image(instance, pixels)\n{\n    return new ImageData(new Uint8ClampedArray(instance.exports.memory.buffer, pixels, %d*%d*4), %d);\n}\n</script>\n<script src=\"javascript.js\"></script>\n</body>\n</html>";
    char string[200];
    snprintf(string, 200, "clang --target=wasm32 -nostdlib -Wl,--no-entry -Wl,--export-all -Wl,--allow-undefined -o output.wasm %s", argv[1]);
    system(string);    
    FILE *file = fopen("index.html", "w");
    fprintf(file, html, argv[2], argv[3], atoi(argv[2]), atoi(argv[3]), atoi(argv[2]));
    fclose(file);
    return 0;
}
