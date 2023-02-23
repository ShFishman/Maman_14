#include "is_valid_line.h"
/* temporary main for checks */
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
	int i;
	char line[1024] = {0};    
	if (argc < 2) {
	printf("Error: No input provided.\n");
	return 1;
	}
	for (i = 1; i < argc; i++) {
	        strcat(line, argv[i]);
	        if (i < argc - 1) {   
        		strcat(line, " ");
		}
	}
    
	printf("%s\n", line);

	return validate_data(line);
}


int is_valid_line(char* line){
	char cpy_line[81];
	char *token;
	struct entry_extern_node* ptr = &head;
	strcpy(cpy_line, line );
	token = (strtok(cpy_line , DELIM) ); 
	if(token == NULL)
		printf("error: no words after label.\n");
		return 1;
	if( is_label(token) != 0 && is_command(token)!= 0 && is_extern(token) !=0 && is_entry(token) != 0){ 
		printf("error: first word not a command and not an instruction.\n");

		if (is_extern(token) == 0 || is_entry(token) == 0 )
			printf("NOTE: first word before \".entry\" or \".extern\" is meaningless.\n");
	}
	else if (is_label(token) == 0){
			printf("i am an label\n");
		return validate_label(cpy_line);
	}
	else if (is_command(token) == 0 )
		return validate_command(cpy_line);
	if (is_extern(token) ==0 || is_entry(token) == 0 )
		validate_entry_and_extern(ptr , cpy_line);
	return 0;
}
/* fuction gets a line that starts after a label 'label1:' ... */
int validate_label(char *line){
	char* token;
	char cpy_line[81];
	if (line == NULL)
		return 1;
	strcpy(cpy_line, line );
	printf("i am inside validate_label\n");
	token = strtok(cpy_line, DELIM);
	if(token == NULL)
		printf("error: no words after label.\n");
	if( (!is_data(token)) != 0 && (!is_string(token)) != 0 ){
		printf("error: first word of label should be \".string\" or \".data\"\n");
		return 1;
	}
	if( (!is_data(token))== 0 )
		return validate_data(line);
	if(( !is_string(token))== 0 )
		return validate_string(line);
	return 0;
}
/* function gets the part of line that starts right after .data*/
int validate_data(char* line){
	int count = 1 ;
	char* token = strtok(line , DELIM); 
	if (token == NULL) {
		printf("Error: no tokens found in input string.\n");
	return 1;
	}

	if( token != NULL)
		if( !alternatly_string_comma(line)){ /* checking for invalid commas */
			while( token != NULL && !is_number(token, count)){ /* checking if strings are numbers */ 			
				count++;
				token = strtok(NULL, ", ");	
			}
			return 0;
		}
	return 1;
}
int is_number(char *token, int index){
	int i;
	if (!isdigit(token[0]) && token[0] != '-' && token[0] != '+'){
		printf("error: first string after data. is not a number.\n");
		return 1;
	}
	else for( i = 1 ; i < strlen(token) ; i++){
			if( !isdigit(token[i]) ){
				printf("error: %d-th element of data not a number.\n" , index );
				return 1;
			}
		}
	return 0 ;
	}
int alternatly_string_comma(char *line){
	int last; /*last =0 if last word wasn't a comma. last =1 if comma is the last word seen.*/
	char cpy_line[81*3] ;
	char* token;
	memset(cpy_line, 0, sizeof(cpy_line));
	make_cpy_line( line , cpy_line);
	token = strtok(cpy_line , DELIM);
	if( strcmp( "," , token ) == 0 ) { /* , before first number */
		printf("error: ',' appears before first string. \n" );
		return 1;
	}

	last = 0;
	token = strtok(NULL , DELIM);
	while( token != NULL){ 
		if( !strcmp( "," , token ) && last == 1){
			printf( "error: a few commas in a row.\n" );
			return 1;
		} 
		if( strcmp( "," , token ) != 0  && last == 0){
			printf( "error: two strings with no comma in between.\n" );
			return 1;
		}
		else{
			if( last == 0 )
				last = 1;
			else
				last = 0;
			token = strtok(NULL , DELIM);
		}
	}
	if( last == 1){
		printf("error: last string is a comma.\n");
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
	char *token = strtok(line , DELIM);
	int l;
	l = strlen(token);
	if(l < 2 || token[0] != '"' || token[l-1] != '"'){
		printf("error: word after '.string' is not a string.\n");	
		return 0;
	}
	else if( (token = strtok(NULL, DELIM)) != NULL){
		printf("error: line should end after the string.\n");
		return 1;
	}
	return 1;
}


void validate_entry_and_extern(struct entry_extern_node *ptr, char* line){
	int flag = 0;
	char* label = strtok( line , DELIM );
	while(  ptr != NULL ){
		if( !strcmp( ptr->name , label)){
			printf("error: label already defined as entry/extern.\n");
			flag = 1;
		}
		ptr = ptr->next;
	}
	if (flag == 0)
		strcpy(ptr-> name , label);
}



