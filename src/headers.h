#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#ifdef _WIN32
#include<windows.h>
#else
#include<dirent.h>
#include<sys/stat.h>
#include<unistd.h>
#endif

void generate_site(const char *content_dir, const char *template_dir, const char *output_dir);
void generate_html(char *content_file, char *template_file, char *output_file);