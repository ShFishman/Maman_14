struct first_word{
	unsigned int ERA: 2;
	unsigned int dest: 2;
	unsigned int source: 2;
	unsigned int opcode: 4;
	unsigned int reg_2: 2;
	unsigned int reg_1: 2;
}

struct other_word{
	int ERA: 2; /* will be intialized to the same ERA of its privious word */
	unsigned int val: 12;
}

typedef struct{
	first_word *val;
	other_word[2];
	words_list *next;
	int counter;
} words_list ;

word_list* head;
head = (words_list)*malloc(sizeof(words_list));

/*functions that analyse the addressing type of the word */
int identify(char* line){
	

}
/* after identifying the type of the word, the next 4 functions will add to the words' list
	the commend in 'line' as it should be allocated */
void add_immediate(char* line ) {}
void add_direct(char* line ) {}
void add_jumping(char* line ) {}
void add_register(char* line ) {}




