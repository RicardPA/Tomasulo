/* - - - - - - Instrucao - - - - - - */
typedef struct 
{
	char type[15];
	Recorder *recorder_00;
	Recorder *recorder_01;
	Recorder *recorder_02;
} Instruction;

void instructionConstructor_01(Instruction *auxInstruction, char type[], Recorder *recorder_00, Recorder *recorder_01, Recorder *recorder_02) 
{
	strcpy (auxInstruction->type, type);
	auxInstruction->recorder_00 = recorder_00;
	auxInstruction->recorder_01 = recorder_01;
	auxInstruction->recorder_02 = recorder_02;
}