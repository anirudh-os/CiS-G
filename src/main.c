#include "headers.h"

int main(int argc, char *argv[]) {
    if(argc != 4) {
        fprintf(stderr, "usage %s <content_dir> <template_dir> <output_dir>\n", argv[0]);
        return 1;
    }

    const char *content_dir = argv[1];
    const char *template_dir = argv[2];
    const char *output_dir = argv[3];

    generate_site(content_dir, template_dir, output_dir);

    return 0;
}