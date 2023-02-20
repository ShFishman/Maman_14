#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct first_word{
	unsigned int ERA: 2;
	unsigned int dest: 2;
	unsigned int source: 2;
	unsigned int opcode: 4;
	unsigned int param_2: 2;
	unsigned int param_1: 2;
}

struct other_word{
	int ERA: 2; /* will be intialized to the same ERA of its privious word */
	unsigned int val: 12;
}

typedef struct{
	first_word val;
	other_word[3];
	words_list *next;
	int counter;
} words_list ;

struct labels_list{
	char name
}

word_list* head;
head = (words_list)*malloc(sizeof(words_list));

/*functions that analyse the addressing type of the word */
int analyze(char* line){
	char broken_commend[4][20];
	int i, j ;
	i=0;
	char reg[8][2] = {"r0","r1","r2","r3","r4","r5","r6","r7"} ;
	strtok( line , "() ," );
	while( broken_commend[i] = srttok( NULL , "() ," != NULL )
		i++;
/* if the first char of the second part of the commend is '#'
	than it can only be an immediate addressing commend */
	if( broken_commmend[1][0] == "#" )
		add_immediate(line); 
/* if the second string in the broken commend is a label's name than it is 
	a direct addressing commend */
	else{
		while( labels_list->name != NULL){
			if( strcmp( *broken_commend[1] , labels_list->name ){
				add_direct(line); 
			}
			labels_list = labels_list-> &next;
		}
	}
/* checking if it is a jumping addressing */
	else if( broken_commend[2] != NULL && broken_commend[3] != NULL ){
		if( !strcmp(broken_commend[0] , "jmp") ||  !strcmp(broken_commend[0] , "bne") ||
		!strcmp(broken_commend[0] , "jsr") ){
			add_jumping(char* line);
		}
	}
/* checking if it is a register addressing */
	else if( broken_commend[3] == NULL){
		for ( i = 0; i <= 7 ; i++ )
			if(!strcmp(reg[i] , broken_commend[1])
				for (j = 0 ; j <= 7; j++)
					if(!strcmp( reg[j], broken_commend[2]) )
						add_register(line);	
		
	}
	

}
/* after identifying the type of the word, the next 4 functions will add to the words' list
	the commend in 'line' as it should be allocated */
void add_immediate(char* line ){printf("this is an immediate commend:\ns%", line);} /*temp commends for compilation check*/
void add_direct(char* line ) {printf("this is a direct commend:\ns%", line);}
void add_jumping(char* line ) {printf("this is a jumpping commend:\ns%", line);}
void add_register(char* line ) {printf("this is a register commend:\ns%", line);}




