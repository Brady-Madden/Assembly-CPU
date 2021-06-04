//Brady Madden
//CSI 404: Virtual Machine
//001333820
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
//allocate 1k space on array
#define STACK_SIZE 1024
//memory array holds the stored values after running through the virtual machine
unsigned int memory[STACK_SIZE];
unsigned char str[STACK_SIZE];
unsigned int stack[STACK_SIZE];
//load takes in file and reads
void load(char argv[]) {
	FILE *src = fopen(argv, "rb");
	fread(str,sizeof(char),STACK_SIZE, src);
	printf("%s\n", str);
	fclose(src);
}
//create an array of register names and their values
int regs[16];
char regnames[16] [3] = { 
	{'r' , '0'}, {'r' , '1'},
	{'r' , '2'}, {'r' , '3'},
	{'r' , '4'}, {'r' , '5'},
	{'r' , '6'}, {'r' , '7'},
	{'r' , '8'}, {'r' , '9'},
	{'r' , '1', '0'}, {'r' , '1', '1'},
	{'r' , '1', '2'}, {'r' , '1', '3'},
	{'r' , '1', '4'}, {'r' , '1', '5'}
 };
//program counter
int pc = 0;
//current instruction buffer
int current_instr [4];
int next_instr [4];
int current_op;
//instruction being worked on
int instr;
//second instruction for pipeline
int nextinstr; 
//stack pointer
int sp = -1;
 enum { 
//op1 and op2 and opresult is final op register
 OP1 = 0, OP2 = 0, OPresult = 0,
 //result register
 resultregister = 0,
};
const int FFFF1 = 65535;
 const int FFFF2 = 65535;
const int immediate [2] = {FFFF1, FFFF2}; 
//instruction set 
typedef enum {
 op_HALT = 0, 
 op_ADD = 1, 
 op_AND = 2, 
 op_DIVIDE = 3, 
 op_MULTIPLY = 4, 
 op_SUBTRACT = 5, 
 op_OR = 6, 
 op_PUSH = 7, 
 op_POP = 7, 
 op_RETURN = 7, 
 op_INTERRUPT = 8, 
 op_ADDIMMEDIATE = 9, 
 op_BRANCHIFEQUAL = 10,
 op_BRANCHIFLESS = 11, 
 op_JUMP = 12, 
 op_CALL = 13, 
 op_LOAD = 14, 
 op_STORE = 15,
} InstructionSet;   
//says whether or not the program is runnable
bool running = true; 
//true if instruction is in decode
bool isindecode = false;
bool isinexecute = false;
bool isinstore = false;
void fetch () {
current_instr[0,1,2,3] == str[pc++]; //by byte
current_op == current_instr[0];
instr = str[pc++]; //whole instruction
}
//cases for each opcode, fills in ops and increments pc when necessary
void decode() {
	isindecode = true;
	switch (current_op) { 
		case op_ADD:
		OP1 == current_instr[0] << 1;
		OP1 == OP1 >> 1;
		OP2 == current_instr[1] >> 1;
		OPresult == current_instr[1] << 1;
		OPresult == OPresult >> 1; 
		break; 
		case op_AND:
		OP1 == current_instr[0] << 1;
		OP1 == OP1 >> 1;
		OP2 == current_instr[1] >> 1;
		OPresult == current_instr[1] << 1;
		OPresult == OPresult >> 1; 
		break;
		case op_DIVIDE:
		OP1 == current_instr[0] << 1;
		OP1 == OP1 >> 1;
		OP2 == current_instr[1] >> 1;
		OPresult == current_instr[1] << 1;
		OPresult == OPresult >> 1; 
		break;
		case op_MULTIPLY:
		OP1 == current_instr[0] << 1;
		OP1 == OP1 >> 1;
		OP2 == current_instr[1] >> 1;
		OPresult == current_instr[1] << 1;
		OPresult == OPresult >> 1; 
		break;
		case op_SUBTRACT:
		OP1 == current_instr[0] << 1;
		OP1 == OP1 >> 1;
		OP2 == current_instr[1] >> 1;
		OPresult == current_instr[1] << 1;
		OPresult == OPresult >> 1; 
		break;
		case op_OR:
		OP1 == current_instr[0] << 1;
		OP1 == OP1 >> 1;
		OP2 == current_instr[1] >> 1;
		OPresult == current_instr[1] << 1;
		OPresult == OPresult >> 1; 
		break;
		case 7: //push pop return
		OP1 == current_instr[0] << 1;
		OP1 == OP1 >> 1;
		OP2 == current_instr[1] >> 1;
		pc == pc + 2;
		break;
		case op_INTERRUPT:
		OP1 == current_instr[4] << 1;
		OP1 == OP1 >> 1;
		OP2 == current_instr[4] >> 1;   
		break;
		case op_ADDIMMEDIATE:
		OP1 == current_instr[0] << 1;
		OP1 == OP1 >> 1;
		OP2 == current_instr[1] >> 1;
		OPresult == current_instr[1] << 1;
		OPresult == OPresult >> 1; 
		break; 
		case op_BRANCHIFEQUAL:
		OP1 == current_instr[0] << 1;
		OP1 == OP1 >> 1;
		OP2 == current_instr[1] >> 1;
		pc == pc + 2;  
		break; 
		case op_BRANCHIFLESS:
		OP1 == current_instr[0] << 1;
		OP1 == OP1 >> 1;
		OP2 == current_instr[1] >> 1;
		pc == pc + 2; 
		break; 
		case op_JUMP:
		OP1 == current_instr[0] << 1;
		OP1 == OP1 >> 1;
		OP2 == current_instr[1] >> 1;
		pc == pc + 2; 
		break; 
		case op_CALL:
		OP1 == current_instr[0] << 1;
		OP1 == OP1 >> 1;
		OP2 == current_instr[1] >> 1;
		pc == pc + 2; 
		break; 
		case op_LOAD:
		OP1 == current_instr[0] << 1;
		OP1 == OP1 >> 1;
		OP2 == current_instr[1] >> 1;
		break; 
		case op_STORE:
		OP1 == current_instr[0] << 1;
		OP1 == OP1 >> 1;
		OP2 == current_instr[1] >> 1;
		break; 
	}
}
//does the work and stores in resultregister
void execute() {
	isinexecute = true;
	int x = 0;
	int offset = 0;
	int value = 0; 
	switch (instr) {
		case 1: //add
		current_instr[3] = current_instr[1] + current_instr[2];
		resultregister == current_instr[3];
		regs[resultregister] = resultregister;
		break;
		case 2: //and
		current_instr[3] = current_instr[1] && current_instr[2];
		resultregister == current_instr[3];
		regs[resultregister] = resultregister;
		break;
		case 3: //divide
		current_instr[3] = current_instr[1] / current_instr[2];
		resultregister == current_instr[3];
		regs[resultregister] = resultregister;
		break;
		case 4: //multiply
		current_instr[3] = current_instr[1] * current_instr[2];
		resultregister == current_instr[3];
		regs[resultregister] = resultregister;
		break;
		case 5: //subtract
		current_instr[3] = current_instr[1] - current_instr[2];
		resultregister == current_instr[3];
		regs[resultregister] = resultregister;
		break;
		case 6: //or
		current_instr[3] = current_instr[1] || current_instr[2];
		resultregister == current_instr[3];
		regs[resultregister] = resultregister;
		break;
		case 704: //push
		if (current_op == 7) { //if op7
			if(current_instr[2] == 4) { //if 3rd hex value is 4
		sp++;
		stack[sp] = current_instr[++pc];
		//push value on to the stack
		resultregister == stack[sp];
		regs[resultregister] = resultregister;
			}
		} break;
		case 708: //pop
		if (current_op == 7) { //if op7
			if(current_instr[2] == 8) { //if third hex value in current instruction is 8
		//popped value assigned to resultreg
		resultregister == stack[sp--];
		regs[resultregister] = resultregister;
			}
		} break;
		case 700: //return
		if (current_op == 7) { //push pop or return
			if(current_instr[2] == 0) { //if 3rd hex value is 0
				sp++;
				stack[sp] = stack[sp--];
				resultregister == stack[sp];
				pc = resultregister;
				regs[resultregister] = resultregister;
			}
		}
		printf("Returned value is: %d\n", resultregister);
		break;
		case 8: //interrupt
		if (current_instr[3] = 0) { //if interrupt 0
			for ( x ; x<= 16; x++) {
				printf("%s\t", regnames[x],"%d\n",regs[x]); //print out every value with names in the registers
			}
		}
		if (current_instr[3] = 1) { //if interrupt 1
			for ( x ; x<= STACK_SIZE; x++);
			printf("= %d\n", memory[x]); // print every value stored in mem
		}
		break;
		case 9: //addimmediate
		immediate[0] == current_instr[2];
		immediate[1] == current_instr[3];
		resultregister == current_instr[1];
		regs[resultregister] = resultregister;
		break;
		case 10: //branchifequal
		if (current_instr[1] == current_instr[2]) {
			offset = current_instr[3]; 
			offset*2 == pc; 
			//sets pc to 2 times the offset is reg1 = reg2
		}
		break;
		case 11: //branchifless
		if (current_instr[1] < current_instr[2]) {
			offset = current_instr[3]; 
			offset*2 + pc == pc; 
			//sets pc to 2 times the offset if reg1 is < reg2
		}
		break;
		case 12: //jump
		if (str[pc++] == instr) {
			pc = instr * 2; //sets pc to number indicated *2 ex jump 1000
		}  
		break;
		case 13: //call
		instr = offset;
		sp++;
		stack[sp] = pc + 4;
		//push value on to the stack
		regs[15] == stack[sp];
		offset*2 + pc == pc; //jumps to 2* the specified number ex call 444
		break;
		case 14: //load
		offset = current_instr[2,3];
		offset *2 == pc;
		str[pc] = regs[current_instr[1]];		
		resultregister == current_instr[1]; //loads number from mem and puts it in result register
		break;
		case 15: //store
		offset = current_instr[2,3];
		offset*2 + sp++ == sp;
		current_instr[1] == value;
			for ( x ; x<= 16; x++) {
		if (current_instr[1] == regs[x]) {
			regs[x] = value + sp; //stores number in mem from reg and 2* offset of sp
		}
	}


		break;
}
}
//puts result from execute stage into allocated memory 
void store() {
isinstore = true;
for (int x =0; x <= STACK_SIZE; x++) {
regs[resultregister] == memory[x]; 
}
}
//this is the implemeted pipeline on SIA VM
void pipelineHelperFetch() {
	//when the first instr is in decode fetch the second instruction
	if (isindecode == true) {
		//this is for the whole instr
		nextinstr = instr;
		//this is for the bytes
		next_instr == current_instr;
		fetch();
	}
}
void pipelineHelperDecode() {
	if (isinexecute == true) {
		nextinstr = instr;
		next_instr == current_instr;
		decode();
	}
}
void pipelineHelperExecute() {
	if (isinstore == true) {
		nextinstr = instr;
		next_instr == current_instr;
		execute();
	}
}
//calls fetch, decode, execute and store
//and pipeline helper functions
 void run () { 
//dont run if halt
if (current_instr[0] == op_HALT) {
running = false;
pc == pc + 1; 
}
//if not halt -> run
while (running = true) {
	//if its not equal to a branch opcode run as pipeline
	if (current_op != 10 | 11) {
	fetch();
	pipelineHelperFetch();
	decode();
	pipelineHelperDecode();
	execute();
	pipelineHelperExecute();
	store();
}
if (current_op == 10 | 11) { //if it is branchifless or branchequals
fetch();					//run as single cycle (flush pipeline)
decode();				
execute();
store(); 
}
}
}
//calls load to read in file and run to start VM
int main (int argc, char **argv) {
	load(argv[1]);
	run();
	return 0;
}
