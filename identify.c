#include "string.h"
#include <stdio.h>
#include <ctype.h>
#define TRUE 0
#define FALSE 1
int is_instruction(char* token){/* return 0 for true, 1 for false */
	int l;
	l = strlen( token);
	return !(token[l-1] == ':');
}

int is_command(char* token) /* return 0 for true, 1 for false */
{
	int i = 0, flag = 1 ;
	
	char commands[16][4] = { "mov" , "cmp" , "add" , "sub" , "not" , "clr" , "lea" , 
		"inc" , "dec" , "jmp" , "bne" , "red" , "prn" , "jsr" , "rts" } ; 
	while( flag != 0 && i < 15  ){		
			
		if ( strcmp( token , commands[i] )==0  )
			flag = 0;
		i++;
	}
		if ( strcmp( token , "stop" )==0 )
			flag = 0;
	return flag;
}
int is_string(char* token){
	return strcmp(token, ".string");
}
int is_data(char* token){
	return strcmp(token, ".data"); 
}
int is_entry(char* token){
	return strcmp(token, ".entry");								
}

int is_extern(char* token){
	return strcmp(token, ".extern");								
}
