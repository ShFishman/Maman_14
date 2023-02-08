#include "string.h"
#include <stdio.h>
#include <ctype.h>

int is_data(char* token);
int is_string(char* token);
int is_command(char* token);
int is_instruction(char* token);
int validate_string(char* line);
void make_cpy_line(char* line, char *cpy_line);
int alternatly_string_comma(char *line);
int is_number(char *token, int *index);
int validate_data(char* line);
int validate_command(char *line);
int validate_instruction(char *line);
int is_valid_line(char* line);


/* temporary main for checks */
int main(int argc, char* argv[]){
	char* line = argv[1];
	return is_valid_line( line) ;

}





int is_valid_line(char* line){
	char cpy_line[81];
	char *token;
	strcpy(cpy_line, line );
	token = (strtok(cpy_line , " ") );
	if( !is_instruction(token) && !is_command(token) ){
		printf("error: first word not a commend and not an instruction.");
		return 1;	
	}
	else if (is_instruction(token) )
		return validate_instruction(cpy_line);
	else if (is_command(token) )
		return validate_command(cpy_line);
	return 0;
}

int validate_instruction(char *line){
	char cpy_line[81];
	char* token;
	strcpy(cpy_line , line);
	token = strtok(line," ");
	if( is_data(token) && is_string(token) && is_command(token) ){
		printf("error: first word of label should be \".string\" or \".data\" or a 			commend");
		return 1;
	}
	if( !is_data(token) )
		return validate_data(cpy_line);
	if( !is_string(token) )
		return validate_string(cpy_line);
	if( !is_command(token) )
		return validate_command(cpy_line);
	return 0;		
}

/* function gets the part of line that starts right after the command*/
int validate_command(char *line){
	char* cmd = strtok(line , " "); /*
	switch( cmd ){
		case mov:
			validate_mov( line);
			break;
		case cmp:
			validate_cmp( &line);
			break;
		case add:
			validate_add( &line);
			break;
		case sub:
			validate_sub( &line);
			break;
		case not:
			validate_not( &line);
			break;
		case clr:
			validate_clr( &line);
			break;
		case lea:
			validate_lea( &line);
			break;
		case inc:
			validate_inc( &line);
			break;
		case dec:
			validate_dec( &line);
			break;
		case jmp:
			validate_jmp( &line);
			break;
		case bne:
			validate_bne( &line);
			break;
		case red:
			validate_red( &line);
			break;
		case prn:
			validate_prn( &line);
			break;
		case jsr:
			validate_jsr( &line);
			break;
		case rts:
			validate_rts( &line);
			break;
		case stop:
			validate_stop( &line);
			break;
	} */
	printf("i am inside validate_command, this is the command:\n %s. ", cmd);
	return 1;
}
/* function gets the part of line that starts right after .data*/
int validate_data(char* line){
	int index = 0;
	char* token = strtok(line , ", ");
	if( !alternatly_string_comma(line)){ /* checking for invalid commas */
		while( token != NULL && is_number(token, &index)){ /* checking if strings are numbers */
			token = strtok(NULL, ", ");
			index += 1 ;
		}
		return 0;
	}
	return 1;
}
int is_number(char *token, int *index){
	int i;
	if ( isdigit(token[0]) || token[0] == '-' || token[0] == '+' ){
		for( i = 1 ; i < strlen(token) ; i++){
			if( !isdigit(token[i]) ){
				printf("eror: %d-th element of data not a number." , *index );
				return 1;
			}
		}
	printf("eror: first string after data. is not a number.");
				return 1;
	}
	return 0 ;
	}
int alternatly_string_comma(char *line){
	int last; /*last =0 if last word wasn't a comma. last =1 if comma is the last word seen.*/
	char cpy_line[81*3] ;
	char* token = strtok(cpy_line , " ");
	make_cpy_line( line , cpy_line);
	if( strcmp( "," , token ) ) { /* , before first number */
		printf("eror: ',' apears befor first string of numbers. \n" );
		return 1;
	}
	last = 0;
	token = strtok(NULL , " ");
	while( token != NULL){
		if( !strcmp( "," , token ) && last == 1){
			printf( "eror: two commas in a row." );
			return 1;
		}
		if( strcmp( "," , token )  && last == 0){
			printf( "eror: two strings with no comma in between." );
			return 1;			
		}
		else{
			if( last == 0)
				last = 1;
			if( last == 1)
				last = 0;
			token = strtok(NULL , " ");
		}
	}
	if( last == 1){
		printf("eror: last string is a comma.");
		return 1;
	}
	return 0;
}
void make_cpy_line(char* line, char *cpy_line){
	
	int i, j; i = j = 0;
	while( line[i] != EOF ){
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
			printf("eror: line should end after the string.");
			return 1;
		}
		else return 0;
		}
	else{
		printf("eror: word after '.string' is not a string.");
	return 1;
	}
}
int is_instruction(char* token){
	int l;
	l = strlen( token);
	return token[l-1] == ':';
}

int is_command(char* token)
{
	int i = 0, flag = 1 ;	
	char commands[15][3] = { "mov" , "cmp" , "add" , "sub" , "not" , "clr" , "lea" , 
		"inc" , "dec" , "jmp" , "bne" , "red" , "prn" , "jsr" , "rts" } ; 
	while( flag != 0 && i <= 15  ){	
		if ( !strcmp( token , commands[i] ) )
			flag = 0;
		i++;  
	}
		if ( !strcmp( token , "stop" ) )
			flag = 0;
	return flag;
}
int is_string(char* token){
	return strcmp(token, ".string");
}
int is_data(char* token){
	return strcmp(token, ".data"); 
}


/*
int validate_mov(char *line){
	//needs to have 2 words after the commend separated by ','
	words should be: a lable name/register name/  
	

}
*/

