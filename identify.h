
#ifndef UNTITLED_IDENTIFY_H
#define UNTITLED_IDENTIFY_H

#endif /*UNTITLED_IDENTIFY_H*/
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#define DELIM " \t\n"
#define DELIM_COMMA " \t\n,"
#define DELIM_LABEL ", ()\t\n"
int is_data(char* token);
int is_string(char* token);
int is_command(char* token);
int is_label(char* token);

int is_entry(char* token);
int is_extern(char* token);
int not_reserved(char* str);
int is_reg( char *str);
int is_num(char *token);
int is_immediate(char *str);
int what_command(char *line);

int check_one_param(char* line);
int check_two_params(char* line);
int check_label_and_two_params(char* line);
int check_label_no_params( char *line);
int first_param_types( int cmd_num , char *line);
int second_param_types(int cmd_num , char *line);
char* exclude_first_two_tokens( char* s);
char* exclude_first_token(char* s);
char* exclude_first_two_tokens_and_commas(char* s);
char* exclude_first_token_and_commas(char* s);
int no_trash(char *str);
int is_param( char* str);
int alternatly_string_comma(char *line);
void make_cpy_line(char* line, char *cpy_line);
int check_prn_comma( char* line);
int command_params(int cmd_num, char *line);
int is_note_line(char *line);
int is_white_space_line(char *line);
