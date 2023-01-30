/*
 ============================================================================
	Name        : C_Project.c
	Author      : Andy
	Version     :
	Copyright   : Your copyright notice
	Description :
	This program reads lines from a file specified in the command line and processes
	the lines based on their contents. If the line starts with the string "mcr",
	the line is processed as a macro definition and the macro name is stored.
	If the line starts with any other string, the program checks if the string is a macro name.
	If it is, the corresponding macro definition is retrieved and written to another file named "result".
	If it's not, the line is written as is to the "result" file.
	The program uses a linked list to store the macro definitions,
	and frees up memory used by the linked list before it terminates.
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

  struct macro {
    char* name;
    char* macro_line;
    struct macro* next;
} head ={"\0","\0", NULL};

typedef enum {normal,read_macro} state;

/*function deceleration*/
void analyze_line(char* line,state *current_state,FILE* fpn);
void insert_link(const char* name);
struct macro* get_link(const char* name);
void macro_line_to_last_link(char* current_macro_line);
void free_macro_list();
void analyze_file(FILE* fp,FILE* fpn);
/*This C program opens a file specified in the command line,
 * checks for proper arguments and file opening,
 * performs processing on the input file through a function call, frees a macro list,
 * closes the files, and returns success or failure based on execution.*/
int main(int argc, char *argv[])
{
	FILE *fp = fopen(argv[1],"r");
	FILE *fpn = fopen("result","w");
	if(argc!=2)
	{
		printf("Missing file name in command line\n");
		return EXIT_FAILURE;
	}
	if(fp==NULL)
	{
		printf("Failed to open file\n");
		return EXIT_FAILURE;
	}

	analyze_file(fp,fpn);
	free_macro_list();
	fclose(fp);
	fclose(fpn);
	return EXIT_SUCCESS;
}
/* This function reads characters from a file fp and analyzes each line by calling the analyze_line function.
 * The analyzed lines are then written to another file fpn.
 * The current_state variable tracks the state of the analysis as it processes each line.
 *  The function continues to read and analyze lines until it reaches the end of the file (EOF).*/
void analyze_file(FILE* fp,FILE* fpn)
{
	char c;
	char line[81] = {0};
	int i =0;
	state current_state = normal;
	while((c=fgetc(fp))!=EOF)
	{
		if(c=='\n')
		{
			line[i]='\0';
			i=0;
			analyze_line(line,&current_state,fpn);
		}
		else
		{
			line[i]=c;
			i++;
		}
	}

}
/*The function "analyze_line" takes a line of text, the current state and a file pointer,
 * and either copies the line to the file or treats it as a macro definition or a macro line.
 * If the state is normal, it checks if the line starts with a macro identifier or a macro definition command,
 *  and acts accordingly. If the state is in macro definition mode,
 it adds the line as a macro line or terminates the definition mode based on "endmcr".*/
void analyze_line(char* line,state *current_state,FILE* fpn)
{
	char line_cpy[82]={0};
	strcpy(line_cpy,line);
	char* token = strtok(line," \t\n"); // first token
	struct macro* tmp_link =NULL;
	if(*current_state==normal)
	{
		if(token==NULL)
		{
			fprintf(fpn,"%s\n",line_cpy);
			return;
		}
		if((tmp_link=get_link(token))!=NULL)
		{
			fprintf(fpn,"%s\n",tmp_link->macro_line);
			return;
		}
		if(!strcmp(token,"mcr"))
		{
 			token= strtok(NULL," \t\n");

			insert_link(token);
			*current_state = read_macro;
			return;
		}
		fprintf(fpn,"%s\n",line_cpy);
	}
	else
	{
		if(token ==NULL)
			macro_line_to_last_link(line_cpy);
		else if(!strcmp(token,"endmcr"))
			*current_state =normal;
		else
			macro_line_to_last_link(line_cpy);
	}
}
/*function creates a new linked list node and inserts it at the end of the linked list, representing a macro with the given name.*/
void insert_link(const char* name)
{
	struct macro* ptr = &head;
	struct macro* new = (struct macro*) malloc(sizeof(struct macro));
	char* new_macro_name = (char*)malloc(sizeof(char)*strlen(name)+1);
	strcpy(new_macro_name,name);
	while(ptr->next!=NULL)
		ptr = ptr->next;
	ptr->next = new;
	new->name=new_macro_name;
	new->next=NULL;
}
/*This function returns the linked list node representing the macro with the given name.
 * If there is no such node, the function returns NULL.*/
struct macro* get_link(const char* name)
{
	struct macro* ptr = &head;
	while(ptr!=NULL)
	{
		if(strcmp(name,ptr->name)==0)
			return ptr;
		ptr = ptr->next;
	}
	return NULL;
}
/*This function add a line to the "macro_line" of the last node in the linked list.*/
void macro_line_to_last_link(char* current_macro_line)
{
	struct macro* ptr = &head;
	char* new_macro_line = NULL;
	while(ptr->next!=NULL)
		ptr = ptr->next;
	if(ptr->macro_line==NULL)
	{
		new_macro_line = (char*)malloc(sizeof(char)*strlen(current_macro_line)+1);
		strcpy(new_macro_line,current_macro_line);
		ptr->macro_line = new_macro_line;
	}
	else
	{
		ptr->macro_line = (char*)realloc(ptr->macro_line,strlen(ptr->macro_line)+strlen(current_macro_line)+2);
		strcat(ptr->macro_line,"\n");
		strcat(ptr->macro_line,current_macro_line);
		ptr->macro_line[strlen(ptr->macro_line)]='\0';
	}
}
/*This frees all memory used by the linked list and its nodes, releasing the memory back to the system.*/
void free_macro_list()
{
		struct macro* current = head.next;
	    struct macro* next = NULL;
	    while (current != NULL)
	    {
	    	next = current->next;
			free(current->name);
			current->name=NULL;
			free(current->macro_line);
			current->macro_line=NULL;
			free(current);
	        current = next;
	    }
}
