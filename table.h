typedef struct{
	char *cmd;
	char params_num;
	addressing_type parm1;
	addressing_type parm2;
	

}command_table;

typedef enum addressing_types {
	/** all addressings are valid (0) */
	ALL_ADDRESSINGS_TYPES = 0,
	/** no param (1) */
	NO_ADDRESSINGS_TYPES = 1,
	/** all addressings but immediate (2) */
	NO_IMMEDIATE = 2,
	/** only immediate and direct addressings are valid */
	ONE_AND_TWO_TYPES = 3,
	/** Failed/Not detected addressing */
	NONE_ADDR = -1
} addressing_type;
/** Commands opcode */
typedef enum opcodes {
	/* First Group */
	MOV_OP = 0,
	CMP_OP = 1,

	ADD_OP = 2,
	SUB_OP = 2,

	LEA_OP = 4,
	/* END First Group */

	/* Second Group */
	CLR_OP = 5,
	NOT_OP = 5,
	INC_OP = 5,
	DEC_OP = 5,

	JMP_OP = 9,
	BNE_OP = 9,
	JSR_OP = 9,

	RED_OP = 12,
	PRN_OP = 13,
	/* END Second Group */

	/* Third Group */
	RTS_OP = 14,
	STOP_OP = 15,
	/* END Third Group */

	/** Failed/Error */
	NONE_OP = -1
} opcode;
typedef enum registers {
	R0 = 0,
	R1,
	R2,
	R3,
	R4,
	R5,
	R6,
	R7,
	NONE_REG = -1
} reg;

