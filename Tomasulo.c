#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
	Title: Variaveis Globais
	OBS.: Abaixo temos variaveis globais imutaveis
	que representam o tamanho dos componenetes da
	aquitetura.
*/

#define LENGTH_MEMORY 30 
#define LENGTH_RECORDER 30
#define LENGTH_INSTRUCTIONS 30

/*
	Title: Celulas de Componentes
	OBS.: Abaixo temos structs que seram utilizadas para
	representar regioes de componentes maiores.
*/

/* - - - - - - Registrador - - - - - - */
typedef struct 
{
	int value;
	bool busy;
	int address;
} Recorder;

void recorderConstructor_00(Recorder *auxRecorder) {
	auxRecorder->value = -1;
	auxRecorder->busy = false;
	auxRecorder->address = -1;	
}

void recorderConstructor_01(Recorder *auxRecorder, int value, bool busy, int address) {
	auxRecorder->value = value;
	auxRecorder->busy = busy;
	auxRecorder->address = address;
}

/* - - - - - - Memoria - - - - - - */
typedef struct 
{
	int value;
	int address;
} Memory;

void memoryConstructor_00(Memory *auxMemory) {
	auxMemory->value = -1;
	auxMemory->address = -1;
}

void memoryConstructor_01(Memory *auxMemory, int value, int address) {
	auxMemory->value = value;
	auxMemory->address = address;
}

/* - - - - - - Instrucao - - - - - - */
typedef struct 
{
	int value;
	int address;
	char type[15];
	Recorder recorder;
} Instruction;

void instructionConstructor_00(Instruction *auxInstruction) {
	auxInstruction->value = -1;
	auxInstruction->address = -1;	
	strcpy (auxInstruction->type, "");
	recorderConstructor_00(&auxInstruction->recorder);
}

void instructionConstructor_01(Instruction *auxInstruction, int value, int address, char type[], Recorder recorder) {
	auxInstruction->value = value;
	auxInstruction->address = address;
	strcpy (auxInstruction->type, type);
	auxInstruction->recorder = recorder;
}

/*
	Title: Unidades de Operacao
	Obs: Abaixo temos structs que representam unidades
	de operacoes, tanto relacionado a memoria quanto para
	operacoes aritmetica.
*/

/* - - - - - - Unidade de Memoria - - - - - - */
typedef struct 
{
	bool busy;
	Recorder recorder_00; // unidade de destino
	Recorder recorder_01; // unidade variavel 
	Recorder recorder_02; // unidade variavel
} MemoryUnit;

void memoryUnitToString(MemoryUnit *memory) 
{
	printf("\n\t --- Dados da Memoria ---\n");
	printf("Unidade de destino: %d | Busy: %d \n", memory->recorder_00.value, memory->recorder_00.busy);
	printf("Unidade variavel: %d | Busy: %d \n", memory->recorder_01.value, memory->recorder_01.busy);
	printf("Unidade variavel: %d | Busy: %d \n", memory->recorder_02.value, memory->recorder_02.busy);
}

void load(MemoryUnit *memory) 
{
	// Marcar como sendo usado
	memory->recorder_00.busy = true;
	memory->recorder_01.busy = true;
	memory->recorder_02.busy = true;

	// Fazer operacao
	memory->recorder_00.value = memory->recorder_01.value + memory->recorder_02.value;

	// Marcar como nao sendo usado
	memory->recorder_00.busy = false;
	memory->recorder_01.busy = false;
	memory->recorder_02.busy = false;
}

void store(MemoryUnit *memory) 
{
	// Marcar como sendo usado
	memory->recorder_00.busy = true;
	memory->recorder_01.busy = true;
	memory->recorder_02.busy = true;

	// Fazer operacao
	memory->recorder_00.value = memory->recorder_01.value + memory->recorder_02.value;

	// Marcar como nao sendo usado
	memory->recorder_00.busy = false;
	memory->recorder_01.busy = false;
	memory->recorder_02.busy = false;
}

/* - - - - - - Unidade de Aritmetica - - - - - - */
typedef struct 
{
	bool busy;
	Recorder recorder_00; // unidade de destino
	Recorder recorder_01; // unidade variavel 
	Recorder recorder_02; // unidade variavel
} ArithmeticUnit;

void arithmeticUnitToString(ArithmeticUnit *arithmetic) 
{
	printf("\n\t --- Dados da Unidade Aritmetica ---\n");
	printf("Unidade de destino: %d | Busy: %d \n", arithmetic->recorder_00.value, arithmetic->recorder_00.busy);
	printf("Unidade variavel: %d | Busy: %d \n", arithmetic->recorder_01.value, arithmetic->recorder_01.busy);
	printf("Unidade variavel: %d | Busy: %d \n", arithmetic->recorder_02.value, arithmetic->recorder_02.busy);
}

void sum(ArithmeticUnit *arithmetic) 
{
	// Marcar como sendo usado
	arithmetic->recorder_00.busy = true;
	arithmetic->recorder_01.busy = true;
	arithmetic->recorder_02.busy = true;

	// Fazer operacao
	arithmetic->recorder_00.value = arithmetic->recorder_01.value + arithmetic->recorder_02.value;

	// Marcar como nao sendo usado
	arithmetic->recorder_00.busy = false;
	arithmetic->recorder_01.busy = false;
	arithmetic->recorder_02.busy = false;
}

void subtraction(ArithmeticUnit *arithmetic)
{
	// Marcar como sendo usado
	arithmetic->recorder_00.busy = true;
	arithmetic->recorder_01.busy = true;
	arithmetic->recorder_02.busy = true;

	// Fazer operacao
	arithmetic->recorder_00.value = arithmetic->recorder_01.value - arithmetic->recorder_02.value;

	// Marcar como nao sendo usado
	arithmetic->recorder_00.busy = false;
	arithmetic->recorder_01.busy = false;
	arithmetic->recorder_02.busy = false;
}

void multiplication(ArithmeticUnit *arithmetic) 
{
	// Marcar como sendo usado
	arithmetic->recorder_00.busy = true;
	arithmetic->recorder_01.busy = true;
	arithmetic->recorder_02.busy = true;

	// Fazer operacao
	arithmetic->recorder_00.value = arithmetic->recorder_01.value * arithmetic->recorder_02.value;

	// Marcar como nao sendo usado
	arithmetic->recorder_00.busy = false;
	arithmetic->recorder_01.busy = false;
	arithmetic->recorder_02.busy = false;
}

void division(ArithmeticUnit *arithmetic) 
{
	// Marcar como sendo usado
	arithmetic->recorder_00.busy = true;
	arithmetic->recorder_01.busy = true;
	arithmetic->recorder_02.busy = true;

	// Fazer operacao
	arithmetic->recorder_00.value = arithmetic->recorder_01.value / arithmetic->recorder_02.value;

	// Marcar como nao sendo usado
	arithmetic->recorder_00.busy = false;
	arithmetic->recorder_01.busy = false;
	arithmetic->recorder_02.busy = false;
}

/*
	Title: Unidades de Armazenamento
	Obs: Abaixo temos structs que representam unidades
	que armazenam informaoes.
*/

typedef struct 
{
	Instruction instructions[LENGTH_INSTRUCTIONS];
} InstructionComponent;

void instructionUnitToString(InstructionComponent *instructions) 
{
	printf("\n\t --- Instrucoes ---\n");

	for(int i = 0; i < LENGTH_INSTRUCTIONS; i++) 
	{
		printf("Tipo: %s | ", instructions->instructions[i].type); 
		printf("Endereco: %d | ", instructions->instructions[i].address); 
		printf("Valor: %d", instructions->instructions[i].value);
	}

	printf("\t --- \n");
}

typedef struct 
{
	Instruction instructions[LENGTH_RECORDER];
} RecorderPFComponent;

typedef struct 
{
	Memory data[LENGTH_MEMORY];
} MemoryComponent;

int main(void) 
{

	return 0;
}