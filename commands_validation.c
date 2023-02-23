#include "is_valid_line.h"

/* function gets the part of line that starts right after the command*/
int validate_command(char *line){
	char cpy_line[81*3] ;
	char*  temp; 
	make_cpy_line(line, cpy_line);
	if( alternatly_string_comma(cpy_line) == 1)
		return 1;
	temp = strtok(cpy_line , DELIM_COMMA);
	
	




}
