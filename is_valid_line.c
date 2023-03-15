#include "is_valid_line.h"
#include "table.h"
#include "identify.h"
/* temporary main for checks */


int main(int argc, char* argv[]) {
	int i; 
	char line[81] = {0};    
	if (argc < 2) {
	printf("ERROR: No input provided.\n");
	return 1;
	}
	for (i = 1; i < argc; i++) {
	        strcat(line, argv[i]);
	        if (i < argc - 1) {   
        		strcat(line, " ");
		}
	}
	printf("%d\n", validating_file(line));


	return 1;
}


int validating_file(char *fname) {
	FILE *fp;
	int i =1;
	char line[81];

	fp = fopen(fname , "r");
	if (fp == NULL) {
		printf("Error opening file.\n");
	return 1;
	}

	while (fgets(line, 81, fp) != NULL) {
		
		if(is_white_space_line(line) == 0 || is_note_line(line) == 0 ){
			i++;
			continue;
		}
		else {
			is_valid_line(line);
			if( is_valid_line(line)!= 0){
				printf("^ in line %d. ^\n", i);
			i++;	
			}
		}
	}
	/*i=1;
	fseek(fp, 0, SEEK_SET);
	while (fgets(line, 100, fp) != NULL) {
		if( label_exist(line) != 0)
			printf("ERROR: label in line %d. is undefined.\n", i);
		i++;	
	}*/

	fclose(fp);

	return 0;
}



int is_valid_line(char* line){
	char* token, *cpy_line, *line_second;
	struct entry_extern_node* ptr = &head; 
	if(line == NULL)
		return 0;
	cpy_line = (char*)malloc(strlen(line)+1);
	strcpy(cpy_line , line);
	line_second = (char*)malloc(strlen(line)+1);
	if(exclude_first_token(line) != NULL)
		strcpy(line_second , exclude_first_token(line) ); 
	printf("line is:\n %s \n", line);
	token = strtok(cpy_line , DELIM);
	if(is_command(token) == 0)
		return validate_command(line);
	if(is_label(token) == 0)
		return validate_label(line);
	if (is_extern(token) == 0 || is_entry(token) == 0 )
		return validate_entry_and_extern( ptr , line_second);

	printf("ERROR: line doesn't fit any valid line structure.\n");
	return 1;
}






/* fuction gets a line that starts with a label like 'label1:' ... */
int validate_label(char *line){ /*verified function*/
	struct entry_extern_node* entry_extern_ptr = &head;
	struct label_node* label_ptr = &first_label; 
		
	char* token, *line_second = NULL, *line_third = NULL, *cpy_line = NULL;
	size_t l;

	if (line == NULL)
		return 1;
	l = strlen(line);
	cpy_line = (char*)malloc((l+1)*sizeof(char));
	strcpy(cpy_line , line);
	line_second = (char*)malloc((l+1)*sizeof(char));
	if(is_new_label( label_ptr ,line) != 0)
		return 1;
	if(exclude_first_token(line) != NULL)
		strcpy(line_second , exclude_first_token(line));

	line_third = (char*)malloc((l+1)*sizeof(char));
	if(exclude_first_two_tokens(line) != NULL)
		strcpy(line_third , exclude_first_two_tokens(line));

	token = strtok(cpy_line , DELIM);
	if(token == NULL)
		printf("ERROR: no words.\n");

	token = strtok(NULL , DELIM);		
	if(token == NULL){
		printf("ERROR: no words after label.\n");
		return 1;
	}

	if( is_entry(token) == 0 || is_extern(token) == 0){
		printf("NOTE: line starts with LABEL: and than- .extern or .entry.\n");
		validate_entry_and_extern(entry_extern_ptr , line_third);
	}

	if( is_data(token) != 0 && is_string(token) != 0 && is_command(token) != 0){
		printf("ERROR: first word of label should be \".string\" or \".data\"\n or a command.");
		return 1;
	}
	if( is_data(token) == 0 )
		return validate_data(line_third);
	if( is_string(token)== 0 )
		return validate_string(line_third);
	if( is_command(token) == 0)
		return validate_command(line_second);
	return 0;
}
/* function gets the part of line that starts right after .data*/
int validate_data(char* line){ /*varified function*/
	int count = 0, flag = 1 ;
	char cpy_line[81];
	char* token;
	memset(cpy_line, 0, sizeof(cpy_line));
	if(line != NULL){
	strcpy(cpy_line , line);
	flag = alternatly_string_comma(line);
	}
	token = strtok(cpy_line , DELIM_COMMA); 
	if (token == NULL) {
		printf("ERROR: no tokens found in input string.\n");
	return 1;
	}

	if( token != NULL)
		if( flag == 0){ /* checking for invalid commas */
			while( token != NULL ){ /* checking if strings are numbers */ 		
				count++;
				if(is_number(token, count)!= 0)
					return 1;
				token = strtok(NULL, DELIM_COMMA );	
			}
		
			return 0;
		}

	return 1;
}
int is_number(char *token, int index){/*varified function*/
	int i;
	if (!isdigit(token[0]) && token[0] != '-' && token[0] != '+'){
		printf("ERROR: %d-th element of data not a number.\n" , index );
		return 1;
	}
	else for( i = 1 ; i < strlen(token) ; i++){
			if( isdigit(token[i])==0 ){
				printf("ERROR: %d-th element of data not a number.\n" , index );
				return 1;
			}
		}
	return 0 ;
}
int alternatly_string_comma(char *line){ /*varified function*/
	int last; /*last =0 if last word wasn't a comma. last =1 if comma is the last word seen.*/
	char cpy_line[81*3] ;
	char* token;
	memset(cpy_line, 0, sizeof(cpy_line));
	make_cpy_line( line , cpy_line);
	token = strtok(cpy_line , DELIM);
	if( strcmp( "," , token ) == 0 ) { /* , before first number */
		printf("ERROR: ',' appears before first string. \n" );
		return 1;
	}

	last = 0;
	token = strtok(NULL , DELIM);
	while( token != NULL){ 
		if( !strcmp( "," , token ) && last == 1){
			printf( "ERROR: a few commas in a row.\n" );
			return 1;
		} 
		if( strcmp( "," , token ) != 0  && last == 0){
			printf( "ERROR: two strings with no comma in between.\n" );
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
		printf("ERROR: last string is a comma.\n");
		return 1;
	}
	
	return 0;
}
void make_cpy_line(char* line, char *cpy_line){/*varified function*/

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
	cpy_line[j] = '\0';
}

/* function gets the part of line that starts right after .string
	currently assuming all chars are ascii valid.
*/
int validate_string(char* line){ /*need fixes*/
	char *token , *cpy_line; 
	/*int l;*/
	if(line == NULL)
		return 1;
	cpy_line = (char*)malloc((strlen(line)+1)*2);
	make_cpy_string(cpy_line, line);
	token = strtok(cpy_line , "*");
	if (token == NULL){
		printf("ERROR: no word after .string\n");
		return 1;
	}
	
	if(strcmp(token , "\"") != 0){
		printf("ERROR: word after .string doesn't start with double quote.\n");
		return 1;
	}
	token = strtok(NULL , "*");
	if (token == NULL){
		printf("ERROR: word after .string is just double quote.\n");
		return 1;
	}

	token = strtok(NULL , "*");
	if (token == NULL){
		printf("ERROR: word after .string has no double quote at the end.\n");
		return 1;
	}
	
	if(strcmp(token , "\"") != 0){
		printf("ERROR: word after .string doesn't start with double quote.\n");
		return 1;
	}
	token = strtok(NULL , DELIM);
	if (token != NULL){
		printf("ERROR: line should end after the string.");
		return 1;
	}

	/*
	l = strlen(token);
	if(l < 2 || token[0] != '"' || token[l-1] != '"'){
		printf("error: word after '.string' is not a string.\n");	
		return 1;
	}
	else {
		token = strtok(NULL, DELIM);
		if(token != NULL)
		printf("ERROR: line should end after \"STRING\".\n");
		return 1;
	}*/
	
	return 0;
}
void make_cpy_string(char *cpy_line , char *line){
	int i, j; i = j = 0;

	while (line[i] != '\0'){
		if( line[i] != '"'){
			cpy_line[j] = line[i];
			i++; j++;
		}
		else{
			cpy_line[j++] = '*';
			cpy_line[j++] = '"';
			cpy_line[j++] = '*';
			i++;
		}
	}
	cpy_line[j] = '\0';
	printf("%s\n",cpy_line);

}

int validate_entry_and_extern(struct entry_extern_node *ptr, char* line){
	int flag = 0;
	char* token , *cpy_line;
	struct entry_extern_node *prev = NULL;
	struct entry_extern_node *new_node = malloc(sizeof(struct entry_extern_node));
	if(line == NULL)
		return 1;
	cpy_line = (char*)malloc(strlen(line)+1);
	strcpy(cpy_line, line);
	token = strtok(cpy_line , DELIM);
	if(token == NULL)
		return 1;
	while(  ptr != NULL && flag == 0 ){
		if( strcmp( ptr->name , token) ==0){
			printf("ERROR: label already defined as entry / extern.\n");
			flag = 1;
		}
		prev = ptr;
		ptr = ptr->next;
	}
	strcpy(new_node->name, token);
	new_node->next = NULL;
	if (flag == 0){
		if (prev == NULL)
			ptr = new_node;
		else
			prev->next = new_node;
	}
	token = strtok(NULL , DELIM);
	if(token != NULL){
		printf("ERROR: line has too many tokens.\n");
		return 1;
	}
	free(cpy_line);
	return flag;
}
int is_new_label(struct label_node *ptr, char* line){
	int flag = 0;
	struct label_node *prev = NULL;
	struct label_node *new_node = malloc(sizeof(struct label_node));
	char* token , *cpy_line;
	if(line == NULL)
		return 1;
	cpy_line = (char*)malloc(strlen(line)+1);
	strcpy(cpy_line, line);
	token = strtok(cpy_line , DELIM);
	if(token == NULL)
		return 1;
	while(  ptr != NULL && flag == 0 ){
		if( strcmp( ptr->name , token) ==0){
			printf("ERROR: label already defined.\n");
			flag = 1;
			
		}
		prev = ptr;
		ptr = ptr->next;
	}
	strcpy(new_node->name, token);
	new_node->next = NULL;
	if (flag == 0){
		if (prev == NULL)
			ptr = new_node;
		else
			prev->next = new_node;
	}
	free(cpy_line);
	return flag;
}

char* exclude_first_two_tokens(char* s) { /*varified function*/
    char* copy = NULL;
    char* token, *cpy_line= NULL;
    int i = 0;
    cpy_line = (char*)malloc(strlen(s) + 1);
        strcpy(cpy_line , s);
    /* Get first two tokens*/
    for (i = 0; i < 2; i++) {
        token = strtok(i == 0 ? (char*)cpy_line : NULL, DELIM);
        if (token == NULL) {
            /* Less than two words in the string*/
            return NULL;
        }
    }

    /* Copy the rest of the string*/
    while ((token = strtok(NULL, DELIM)) != NULL) {
        if (copy == NULL) {
            copy = (char*)malloc(strlen(token) + 1);
            strcpy(copy, token);
        } else {
            copy = (char*)realloc(copy, strlen(copy) + strlen(token) + 2);
            strcat(copy, " ");
            strcat(copy, token);
        }
    }

    return copy;
}
char* exclude_first_token(char* s) {/*varified function*/
	char* copy = NULL;
	char* token, *cpy_line= NULL;
    
	cpy_line = (char*)malloc(strlen(s) + 1);
	strcpy(cpy_line , s);
    /* Get first token*/
        token = strtok(cpy_line, DELIM);
        if (token == NULL) {
		return NULL;
        }

    /* Copy the rest of the string*/
	while ((token = strtok(NULL, DELIM)) != NULL) {
		if (copy == NULL) {
			copy = (char*)malloc(strlen(token) + 1);
			strcpy(copy, token);
		} else {
			copy = (char*)realloc(copy, strlen(copy) + strlen(token) + 2);
			strcat(copy, " ");
			strcat(copy, token);
		}
	}

	return copy;
}
char* exclude_first_two_tokens_and_commas(char* s) { /*varified function*/
    char* copy = NULL;
    char* token, *cpy_line= NULL;
    int i = 0;
    cpy_line = (char*)malloc(strlen(s) + 1);
        strcpy(cpy_line , s);
    /* Get first two tokens*/
    for (i = 0; i < 2; i++) {
        token = strtok(i == 0 ? (char*)cpy_line : NULL, DELIM_COMMA);
        if (token == NULL) {
            /* Less than two words in the string*/
            return NULL;
        }
    }

    /* Copy the rest of the string*/
    while ((token = strtok(NULL, DELIM_COMMA)) != NULL) {
        if (copy == NULL) {
            copy = (char*)malloc(strlen(token) + 1);
            strcpy(copy, token);
        } else {
            copy = (char*)realloc(copy, strlen(copy) + strlen(token) + 2);
            strcat(copy, " ");
            strcat(copy, token);
        }
    }

    return copy;
}
char* exclude_first_token_and_commas(char* s) {/*varified function*/
	char* copy = NULL;
	char* token, *cpy_line= NULL;
    
	cpy_line = (char*)malloc(strlen(s) + 1);
	strcpy(cpy_line , s);
    /* Get first token*/
        token = strtok(cpy_line, DELIM_COMMA);
        if (token == NULL) {
		return NULL;
        }

    /* Copy the rest of the string*/
	while ((token = strtok(NULL, DELIM_COMMA)) != NULL) {
		if (copy == NULL) {
			copy = (char*)malloc(strlen(token) + 1);
			strcpy(copy, token);
		} else {
			copy = (char*)realloc(copy, strlen(copy) + strlen(token) + 2);
			strcat(copy, " ");
			strcat(copy, token);
		}
	}

	return copy;
}
int is_note_line(char *line){
	if(line[0] == '#')
		return 0;
	return 1; 
}
int is_white_space_line(char *line){
	char *token , *cpy_line;
	if(line == NULL)
		return 1;
	cpy_line = (char*)malloc(strlen(line) + 1);
	strcpy(cpy_line , line);
	token = strtok(cpy_line, DELIM); /*DELIM includes all white spaces, if line is only
					white spaces then token would be null. */
	if(token == NULL)
		return 0;
	return 1;
}
void clear_labels_list(struct label_node* first_label){
    struct label_node* current = first_label;
    struct label_node* temp = NULL;

    while(current != NULL){
        temp = current;
        current = current->next;
        free(temp);
    }
}
void clear_entry_extern_list(struct entry_extern_node* head){
    struct entry_extern_node* current = head;
    struct entry_extern_node* temp = NULL;

    while(current != NULL){
        temp = current;
        current = current->next;
        free(temp);
    }
}








