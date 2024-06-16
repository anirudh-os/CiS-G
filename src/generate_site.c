#include "headers.h"

void generate_site(const char *content_dir, const char *template_dir, const char *output_dir) {

    printf("%s\n%s\n%s\n", content_dir, template_dir, output_dir);

    #ifdef _WIN32
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;
    char content_file[MAX_PATH];
    char template_file[MAX_PATH];
    char output_file[MAX_PATH];
    char* content_pattern = strcat(strcpy(malloc(strlen(content_dir) + 3), content_dir), "\\*");
    #else
    DIR *d;
    struct dirent *dir;
    char content_file[256];
    char template_file[256];
    char output_file[256];
    #endif

    #ifdef _WIN32
    hFind = FindFirstFile(content_pattern, &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Error opening directory.\n");
    }

    do {
        if (strcmp(findFileData.cFileName, ".") != 0 && strcmp(findFileData.cFileName, "..") != 0) {
            snprintf(content_file, sizeof(content_file), "%s\\%s", content_dir, findFileData.cFileName);
            snprintf(template_file, sizeof(template_file), "%s/template.html", template_dir);
            snprintf(output_file, sizeof(output_file), "%s\\output.html", output_dir);
            generate_html(content_file, template_file, output_file);
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
    #else
    d = opendir(content_dir);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (dir->d_type == DT_REG) { // Check if it is a regular file
                snprintf(content_file, sizeof(content_file), "%s/%s", content_dir, dir->d_name);
                snprintf(template_file, sizeof(template_file), "%s/template.html", template_dir);
                snprintf(output_file, sizeof(output_file), "%s/%s.html", output_dir, dir->d_name);
                generate_html(content_file, template_file, output_file);
            }
        }
        closedir(d);
    } else {
        perror("opendir");
    }
    #endif

    #ifdef _WIN32
    free(content_pattern);
    #endif
}