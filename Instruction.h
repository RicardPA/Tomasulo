/*
	-----------------------------------
	Instruction.h 
	Author: Ricardo Portilho de Andrade 
	-----------------------------------
	Objetivo: Esse codigo representa as 
	informacoes necessarias para criar 
	instrucoes.
	-----------------------------------
	Bibliotecas necessarias:
	* Recorder.h
*/

/* - - - - - - Instrucao - - - - - - */
typedef struct 
{
	bool busy;
	char type[15];
	Recorder *recorder_00;
	Recorder *recorder_01;
	Recorder *recorder_02;
} Instruction;

void instructionConstructor_01(Instruction *auxInstruction, char type[], Recorder *recorder_00, Recorder *recorder_01, Recorder *recorder_02, bool busy) 
{
	auxInstruction->busy = busy;
	strcpy (auxInstruction->type, type);
	auxInstruction->recorder_00 = recorder_00;
	auxInstruction->recorder_01 = recorder_01;
	auxInstruction->recorder_02 = recorder_02;
}