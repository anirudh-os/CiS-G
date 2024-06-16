#include "headers.h"

void replace_placeholder(char *output_content, char *placeholder, char *replacement) {
    char *pos = strstr(output_content, placeholder);

    if(pos) {
        size_t len_before = pos - output_content;
        size_t len_placeholder = strlen(placeholder);
        size_t len_replacement = strlen(replacement);
        size_t len_after = strlen(pos + len_placeholder);

        memmove(pos + len_replacement, pos + len_placeholder, len_after + 1);
        memcpy(pos, replacement, len_replacement);
    }

    else {
        printf("Placeholder not found !\n");
    }
}

void generate_html(char *content_file, char *template_file, char *output_file) {
    FILE *content_fp = fopen(content_file, "r");
    FILE *template_fp = fopen(template_file, "r");
    FILE *output_fp = fopen(output_file, "w");
    
    if (!content_fp) {
        perror("Error opening the content file");
        fclose(content_fp);
        return;
    } else if (!template_fp) {
        perror("Error opening the template file");
        fclose(template_fp);
        return;
    } else if (!output_fp) {
        perror("Error opening the output file");
        fclose(output_fp);
        return;
    }

    // Read template content
    fseek(template_fp, 0, SEEK_END);
    long template_size = ftell(template_fp);
    printf("%d\n\n", template_size);
    fseek(template_fp, 0, SEEK_SET);
    char *template_content = malloc(template_size - 52);
    fread(template_content, 1, template_size, template_fp);
    template_content[template_size] = '\0';

    // Read content file
    fseek(content_fp, 0, SEEK_END);
    long content_size = ftell(content_fp);
    fseek(content_fp, 0, SEEK_SET);
    char *content = malloc(content_size + 1);
    fread(content, 1, content_size, content_fp);
    content[content_size] = '\0';

    // Parse the content file into key-value pairs
    char *title = NULL;
    char *heading = NULL;
    char *paragraph = NULL;
    char *line = strtok(content, "\n");
    while (line != NULL) {
        if (strncmp(line, "Title: ", 7) == 0) {
            title = strdup(line + 7);
        } else if (strncmp(line, "Heading: ", 9) == 0) {
            heading = strdup(line + 9);
        } else if (strncmp(line, "Paragraph: ", 11) == 0) { 
                if (paragraph != NULL) {
                paragraph = realloc(paragraph, strlen(paragraph) + strlen(line + 11) + 2);
                strcat(paragraph, "\n");
                strcat(paragraph, line + 11);
            } else {
                paragraph = strdup(line + 11);
            }
        }
        line = strtok(NULL, "\n");
    }

    // Create output content
    char *output_content = malloc(template_size + content_size + 1);
    strcpy(output_content, template_content);
    printf("Template:\n%s\n", template_content);
    printf("%s\n", output_content);

    // Replace placeholders with actual content
    if (title) {
        replace_placeholder(output_content, "{{ title }}", title);
    }
    if (heading) {
        replace_placeholder(output_content, "{{ heading }}", heading);
    }
    if (paragraph) {
        replace_placeholder(output_content, "{{ paragraph }}", paragraph);
    }

    // Write output file
    fprintf(output_fp, "%s", output_content);

    // Clean up
    free(template_content);
    free(content);
    free(output_content);
    if (title) free(title);
    if (heading) free(heading);
    if (paragraph) free(paragraph);
    fclose(content_fp);
    fclose(template_fp);
    fclose(output_fp);
}