#include <stdbool.h>

#define WAPHICS_IMPLEMENTATION
#include "../src/waphics.c"

void test_keys() {
    assert(KEY_A == 65);
}

int main() {
    test_keys();
}