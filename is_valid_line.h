
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
    char name[81];
    struct entry_extern_node* next;
} head = {"\0", NULL};
struct label_node{ /*creating a list of labels that were defined */
    char name[20];
    struct label_node* next;
} first_label = {"\0", NULL};

int validating_file(char *fname);
int is_data(char* token);
int is_string(char* token);
int is_command(char* token);
int is_label(char* token);
int is_new_label(struct label_node *ptr, char* line);

void make_cpy_string(char *cpy_line , char *line);
int validate_string(char* line);
void make_cpy_line(char* line, char *cpy_line);
int alternatly_string_comma(char *line);
int is_number(char *token, int index);
int validate_data(char* line);
int validate_command(char *line);
int validate_label(char *line);
int is_valid_line(char* line);
char* exclude_first_two_tokens( char* s);
char* exclude_first_token(char* s);
char* exclude_first_two_tokens_and_commas(char* s);
char* exclude_first_token_and_commas(char* s);
int validate_entry_and_extern( struct entry_extern_node *ptr, char* line);

int is_entry(char* token);
int is_extern(char* token);
int validate_command(char* line);
int is_reg( char *str);
int is_num(char *token);
int is_immediate(char *str);
int not_reserved(char* str);
int no_trash(char *str);
int is_param( char* str);

int check_label_and_two_params(char* line);
int check_prn_comma( char* line);

int command_params(int cmd_num, char *line);

int is_note_line(char *line);
int is_white_space_line(char *line);
void clear_labels_list(struct label_node* first_label);
void clear_entry_extern_list(struct entry_extern_node* head);
