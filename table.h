#include "identify.h"

typedef enum addressing_types {
	/** all addressings are valid (0) */
	ALL_BUT_TWO = 0,
	/** no param (1) */
	NO_ADDRESSINGS_TYPES = 1,
	/** all addressings but immediate (2) */
	ONE_AND_THREE = 2,
	/** only immediate and direct addressings are valid */
	ONE_AND_TWO= 3,
	/** only direct addressing is valid */
	ONLY_ONE = 4,
	/** only direct and jumping addressings are valid */

	/** Failed/Not detected addressing */
	NONE_ADDR = -1
} addressing_type;
typedef enum params_nums{
	ONE_PARAM = 0,
	TWO_PARAMS = 1,
	LABEL_NON_OR_TWO_PARAMS =2,
	NO_PARAMS = 3
} param_num;
typedef struct{
	char *cmd;
	char params_num;
	addressing_type source;
	addressing_type dest;
	

}command_table;
extern const command_table table[];
typedef enum registers {
	R0 = 0,
	R1,
	R2,
	R3,
	R4,
	R5,
	R6,
	R7,
	NON_REG = -1
} reg;

