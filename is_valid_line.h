
#ifndef UNTITLED_IS_VALID_LINE_H
#define UNTITLED_IS_VALID_LINE_H

#endif /*UNTITLED_IS_VALID_LINE_H*/
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#define DELIM " \t\n"
#define DELIM_COMMA " \t\n,"
struct entry_extern_node{ /*creating a list of labels that were defined as extern or entry */
    char name[20];
    struct entry_extern_node* next;
}head = {"\0", NULL};
int is_data(char* token);
int is_string(char* token);
int is_command(char* token);
int is_label(char* token);
int validate_string(char* line);
void make_cpy_line(const char* line, char *cpy_line);
int alternatly_string_comma(char *line);
int is_number(char *token, int index);
int validate_data(char* line);
int validate_command(char *line);
int validate_label(char *line);
int is_valid_line(char* line);
void validate_entry_and_extern( struct entry_extern_node *ptr, char* line);
int is_entry(char* token);
int is_extern(char* token);
