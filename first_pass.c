bool first_pass (FILE *input){
	char line[81], cpy_line[81];
	char *cmd, *token ;
	enum commends_type{}; /* will be in the header */	
	while(fgets( line , 81 , input) ){
		strcpy(cpy_line , line );	
		token = strtok(line ," \t\n");
		if(!is_valid_line( cpy_line) || is_comment_or_empty( token) )
			continue;
			
		encode_line(cpy_line);
		
		
	}

}
is_comment_or_empty( char* line ){
	if (token == NULL)
		continue;
	
	if (is_comment( token) )
		continue;
}
	
encode_line( char *line , label **head_label, code_image **code_head , ) {
	if (is_label( token) ){
		cmd = strtok (NULL, delim);
		cmd_type = commend_type(cmd);  /*L1: cmd param1 , param2 */	
		add_label( 	
	}
}
