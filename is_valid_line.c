#include "is_valid_line.h"
#include "string.h"
#include <stdio.h>
#include <ctype.h>
#define TRUE 0
#define FALSE 1


/* temporary main for checks */
int main(int argc, char* argv[]){

	if (argc < 2) {
		printf("Error: No input provided.\n");
		return 1;
	}
	char* line = argv[1];
	for (int i = 2; i < argc; i++) {
		strcat(line, " ");
		strcat(line, argv[i]);
	}
	return is_valid_line(line);
}





int is_valid_line(char* line){
	char cpy_line[81];
	char *token;
	struct entry_extern_node* ptr = &head;


	strcpy(cpy_line, line );
	token = (strtok(cpy_line , " ") );
	if( is_instruction(token)==FALSE && is_command(token)==FALSE && is_extern(token) ==FALSE && is_entry(token) == FALSE){
		printf("error: first word not a command and not an instruction.");
		token = (strtok(cpy_line , " ") );
		if (is_extern(token) ==TRUE|| is_entry(token) == TRUE )
			printf("NOTE: first word before \".entry\" or \".extern\" is meaningless.\n");
	}
	else if (is_instruction(token) == TRUE )
		return validate_instruction(cpy_line);
	else if (is_command(token) == TRUE )
		return validate_command(cpy_line);
	if (is_extern(token) ==TRUE|| is_entry(token) == TRUE )
		validate_entry_and_extern(ptr , cpy_line);
	return 0;
}

int validate_instruction(char *line){

	char* token;


	token = strtok(line," ");
	if(token == NULL)
		printf("error: no words after label.");
	if( (!is_data(token)) == FALSE && (!is_string(token)) == FALSE ){
		printf("error: first word of label should be \".string\" or \".data\"");
		return 1;
	}
	if( (!is_data(token))== TRUE )
		return validate_data(line);
	if(( !is_string(token))== TRUE )
		return validate_string(line);
	return 0;
}

/* function gets the part of line that starts right after the command*/
int validate_command(char *line){
	char* cmd = strtok(line , " "); /*
	switch( cmd ){
		case mov:
			validate_mov( line);
			break;
		*/

	printf("i am inside validate_command, this is the command:\n %s. \n", cmd);
	return 1;
}
/* function gets the part of line that starts right after .data*/
int validate_data(char* line){
	int index = 0;
	char* token = strtok(line , ", ");
	if( !alternatly_string_comma(line)){ /* checking for invalid commas */
		while( token != NULL && !is_number(token, &index)){ /* checking if strings are numbers */
			token = strtok(NULL, ", ");
			index += 1 ;
		}
		return 0;
	}
	return 1;
}
int is_number(char *token, const int *index){
	int i;
	if (!isdigit(token[0]) && token[0] != '-' && token[0] != '+'){
		printf("error: first string after data. is not a number.");
		return 1;
	}
	else for( i = 1 ; i < strlen(token) ; i++){
			if( !isdigit(token[i]) ){
				printf("error: %d-th element of data not a number." , *index );
				return 1;
			}
		}
	return 0 ;
	}
int alternatly_string_comma(char *line){
	int last; /*last =0 if last word wasn't a comma. last =1 if comma is the last word seen.*/
	char cpy_line[81*3] ;
	char* token = strtok(cpy_line , " ");
	make_cpy_line( line , cpy_line);
	if( strcmp( "," , token ) != 0 ) { /* , before first number */
		printf("error: ',' appears before first string of numbers. \n" );
		return 1;
	}
	last = 0;
	token = strtok(NULL , " ");
	while( token != NULL){
		if( !strcmp( "," , token ) && last == 1){
			printf( "error: two commas in a row." );
			return 1;
		}
		if( strcmp( "," , token ) != 0  && last == 0){
			printf( "error: two strings with no comma in between." );
			return 1;
		}
		else{
			if( last == 0 )
				last = 1;
			else
				last = 0;
			token = strtok(NULL , " ");
		}
	}
	if( last == 1){
		printf("error: last string is a comma.");
		return 1;
	}
	return 0;
}
void make_cpy_line(const char* line, char *cpy_line){

	int i, j; i = j = 0;
	while (line[i] != '\0'){
		if( line[i] != ','){
			cpy_line[j] = line[i];
			i++; j++;
		}
		else{
			cpy_line[j++] = ' ';
			cpy_line[j++] = ',';
			cpy_line[j++] = ' ';
			i++;
		}
	}
}

/* function gets the part of line that starts right after .string
	currently assuming all chars are ascii valid.
*/
int validate_string(char* line){
	char *token = strtok(line , " ");
	int l;
	l = strlen(token);
	if( token[0] == '"' && token[l-1] == '"' ) {
		if( (token = strtok(NULL, " ")) != NULL){
			printf("error: line should end after the string.");
			return 1;
		}
		else return 0;
	}
	printf("error: word after '.string' is not a string.");
	return 1;
}


void validate_entry_and_extern(struct entry_extern_node *ptr, char* line){
	int flag = TRUE;
	char* label = strtok( line , " " );
	while(  ptr != NULL ){
		if( !strcmp( ptr->name , label)){
			printf("error: label already defined as entry/extern");
			flag = FALSE;
		}
		ptr = ptr->next;
	}
	if (flag == TRUE)
		strcpy(ptr-> name , label);
}



