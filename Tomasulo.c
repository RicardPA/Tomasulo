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

void recorderToString(Recorder *auxRecorder) {
	printf("Valor: %d | ", auxRecorder->value);
	printf("Usado: %d | ",auxRecorder->busy);
	printf("Endereco: %d", auxRecorder->address);	
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
	char type[15];
	Recorder *recorder_00;
	Recorder *recorder_01;
	Recorder *recorder_02;
} Instruction;

void instructionConstructor_01(Instruction *auxInstruction, char type[], Recorder *recorder_00, Recorder *recorder_01, Recorder *recorder_02) {
	strcpy (auxInstruction->type, type);
	auxInstruction->recorder_00 = recorder_00;
	auxInstruction->recorder_01 = recorder_01;
	auxInstruction->recorder_02 = recorder_02;
}

/*
	Title: Unidades de Armazenamento
	Obs: Abaixo temos structs que representam unidades
	que armazenam informaoes.
*/

/* - - - - - - Banco de Registradores - - - - - - */

typedef struct 
{
	Recorder recorders[LENGTH_RECORDER];
} RecorderPFComponent;

void createRecorderFP(RecorderPFComponent *recorderPFComponent) 
{
	for(int i = 0; i < LENGTH_INSTRUCTIONS; i++) 
	{
		recorderConstructor_01(&recorderPFComponent->recorders[i], i, false, i);
	}
}

/* - - - - - - Lista de Instrucao - - - - - - */

typedef struct 
{
	Instruction instructions[LENGTH_INSTRUCTIONS];
} InstructionComponent;

void instructionUnitToString(InstructionComponent *instructionComponent) 
{
	printf("\n\t --- Instrucoes ---\n");

	for(int i = 0; i < LENGTH_INSTRUCTIONS; i++) 
	{
		printf("Tipo: %s | ", instructionComponent->instructions[i].type); 
		printf("\nDestino \n\t"); 
		recorderToString(instructionComponent->instructions[i].recorder_00);
		printf("\nOperando_01 \n\t");
		recorderToString(instructionComponent->instructions[i].recorder_01);
		printf("\nOperando_02 \n\t");
		recorderToString(instructionComponent->instructions[i].recorder_02);
	}

	printf("\t --- \n");
}

void createInstructions(InstructionComponent *instructionComponent, RecorderPFComponent *recorderPFComponent) 
{
	for(int i = 0; i < LENGTH_INSTRUCTIONS; i = i + 5) 
	{
		instructionConstructor_01(&instructionComponent->instructions[i], "add", &recorderPFComponent->recorders[i], &recorderPFComponent->recorders[i+1], &recorderPFComponent->recorders[i+3]);
		instructionConstructor_01(&instructionComponent->instructions[i+1], "sub", &recorderPFComponent->recorders[i+1], &recorderPFComponent->recorders[i], &recorderPFComponent->recorders[i+2]);
		instructionConstructor_01(&instructionComponent->instructions[i+2], "mul", &recorderPFComponent->recorders[i+2], &recorderPFComponent->recorders[i+2], &recorderPFComponent->recorders[i]);
		instructionConstructor_01(&instructionComponent->instructions[i+3], "div", &recorderPFComponent->recorders[i+3], &recorderPFComponent->recorders[i], &recorderPFComponent->recorders[i+2]);
		instructionConstructor_01(&instructionComponent->instructions[i+4], "add", &recorderPFComponent->recorders[i], &recorderPFComponent->recorders[i+1], &recorderPFComponent->recorders[i+3]);
	}
}

/* - - - - - - Memoria Secundaria - - - - - - */

typedef struct 
{
	Memory data[LENGTH_MEMORY];
} MemoryComponent;

void memoryComponentToString(MemoryComponent *memoryComponent) 
{
	printf("--- Memoria ---\n");
	for(int i = 0; i < LENGTH_MEMORY; i++) 
	{
		printf("Valor: %d | Endereco: %d\n", memoryComponent->data[i].value, memoryComponent->data[i].address);
	}
}

void createMemoryComponent(MemoryComponent *memoryComponent) 
{
	for(int i = 0; i < LENGTH_MEMORY; i++) 
	{
		memoryConstructor_01(&memoryComponent->data[i], 0, i);
	}
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
	Recorder *recorder_00; // unidade de destino
	Recorder *recorder_01; // unidade variavel 
	Recorder *recorder_02; // unidade variavel
	MemoryComponent *memory;
} MemoryUnit;

void memoryUnitToString(MemoryUnit *memory) 
{
	printf("\n\t --- Dados da Memoria ---\n");
	printf("Unidade de destino: %d | Busy: %d | Address: %d \n", memory->recorder_00->value, memory->recorder_00->busy, memory->recorder_00->address);
	printf("Unidade variavel: %d | Busy: %d | Address: %d \n", memory->recorder_01->value, memory->recorder_01->busy, memory->recorder_01->address);
	printf("Unidade variavel: %d | Busy: %d Address: %d \n", memory->recorder_02->value, memory->recorder_02->busy, memory->recorder_02->address);
}

void load(MemoryUnit *memory) 
{
	// Marcar como sendo usado
	memory->recorder_00->busy = true;
	memory->recorder_01->busy = true;
	memory->recorder_02->busy = true;

	// Fazer operacao
	memory->recorder_00->value = memory->memory->data[memory->recorder_01->value + memory->recorder_02->value].value;

	// Marcar como nao sendo usado
	memory->recorder_00->busy = false;
	memory->recorder_01->busy = false;
	memory->recorder_02->busy = false;
}

void store(MemoryUnit *memory) 
{
	// Marcar como sendo usado
	memory->recorder_00->busy = true;
	memory->recorder_01->busy = true;
	memory->recorder_02->busy = true;

	// Fazer operacao
	memory->memory->data[memory->recorder_01->value + memory->recorder_02->value].value = memory->recorder_00->value;

	// Marcar como nao sendo usado
	memory->recorder_00->busy = false;
	memory->recorder_01->busy = false;
	memory->recorder_02->busy = false;
}

/* - - - - - - Unidade de Aritmetica - - - - - - */
typedef struct 
{
	bool busy;
	char type[15];
	Recorder *recorder_00; // unidade de destino
	Recorder *recorder_01; // unidade variavel 
	Recorder *recorder_02; // unidade variavel
} ArithmeticUnit;

void arithmeticUnitConstructor_00(ArithmeticUnit *auxArithmetic) {
	auxArithmetic->busy = false;
	recorderConstructor_00(auxArithmetic->recorder_00);
	recorderConstructor_00(auxArithmetic->recorder_01);
	recorderConstructor_00(auxArithmetic->recorder_02);
}

void arithmeticUnitConstructor_01(ArithmeticUnit *auxArithmetic, bool busy, Recorder *recorder_00, Recorder *recorder_01, Recorder *recorder_02) {
	auxArithmetic->busy = false;
	auxArithmetic->recorder_00 = recorder_00;
	auxArithmetic->recorder_01 = recorder_01;
	auxArithmetic->recorder_02 = recorder_02;
}

void arithmeticUnitToString(ArithmeticUnit *arithmetic) 
{
	printf("\n\t --- Dados da Unidade Aritmetica (%s) ---\n", arithmetic->type);
	printf("Unidade de destino (Valor: %d | Busy: %d | Address: %d) \n", arithmetic->recorder_00->value, arithmetic->recorder_00->busy, arithmetic->recorder_00->address);
	printf("Unidade variavel (Valor: %d | Busy: %d | Address: %d) \n", arithmetic->recorder_01->value, arithmetic->recorder_01->busy, arithmetic->recorder_01->address);
	printf("Unidade variavel (Valor: %d | Busy: %d | Address: %d) \n", arithmetic->recorder_02->value, arithmetic->recorder_02->busy, arithmetic->recorder_02->address);
}

void sum(ArithmeticUnit *arithmetic) 
{
	// Marcar como sendo usado
	arithmetic->recorder_00->busy = true;
	arithmetic->recorder_01->busy = true;
	arithmetic->recorder_02->busy = true;

	// Fazer operacao
	arithmetic->recorder_00->value = arithmetic->recorder_01->value + arithmetic->recorder_02->value;

	// Marcar como nao sendo usado
	arithmetic->recorder_00->busy = false;
	arithmetic->recorder_01->busy = false;
	arithmetic->recorder_02->busy = false;
}

void subtraction(ArithmeticUnit *arithmetic)
{
	// Marcar como sendo usado
	arithmetic->recorder_00->busy = true;
	arithmetic->recorder_01->busy = true;
	arithmetic->recorder_02->busy = true;

	// Fazer operacao
	arithmetic->recorder_00->value = arithmetic->recorder_01->value - arithmetic->recorder_02->value;

	// Marcar como nao sendo usado
	arithmetic->recorder_00->busy = false;
	arithmetic->recorder_01->busy = false;
	arithmetic->recorder_02->busy = false;
}

void multiplication(ArithmeticUnit *arithmetic) 
{
	// Marcar como sendo usado
	arithmetic->recorder_00->busy = true;
	arithmetic->recorder_01->busy = true;
	arithmetic->recorder_02->busy = true;

	// Fazer operacao
	arithmetic->recorder_00->value = arithmetic->recorder_01->value * arithmetic->recorder_02->value;

	// Marcar como nao sendo usado
	arithmetic->recorder_00->busy = false;
	arithmetic->recorder_01->busy = false;
	arithmetic->recorder_02->busy = false;
}

void division(ArithmeticUnit *arithmetic) 
{
	// Marcar como sendo usado
	arithmetic->recorder_00->busy = true;
	arithmetic->recorder_01->busy = true;
	arithmetic->recorder_02->busy = true;

	// Fazer operacao
	arithmetic->recorder_00->value = arithmetic->recorder_01->value / arithmetic->recorder_02->value;

	// Marcar como nao sendo usado
	arithmetic->recorder_00->busy = false;
	arithmetic->recorder_01->busy = false;
	arithmetic->recorder_02->busy = false;
}

int main(void) 
{
	printf("Aqui 1\n");
	InstructionComponent instructionComponent;
	RecorderPFComponent recorderPFComponent;
	ArithmeticUnit arithmeticSubSumComponent, arithmeticMulDivComponent;
	MemoryComponent memoryComponent;

	createMemoryComponent(&memoryComponent);
	createRecorderFP(&recorderPFComponent);
	createInstructions(&instructionComponent, &recorderPFComponent);
	
	printf("Aqui 2\n"); 

	for(int i = 0; i < LENGTH_INSTRUCTIONS; i++) 
	{
		printf("Aqui FOR(%d)\n", i);
		if (strcmp(instructionComponent.instructions[i].type, "add") == 0) {
			arithmeticSubSumComponent.busy = true;
			strcpy(arithmeticSubSumComponent.type, "add");
			arithmeticSubSumComponent.recorder_00 = instructionComponent.instructions[i].recorder_00;
			arithmeticSubSumComponent.recorder_01 = instructionComponent.instructions[i].recorder_01;
			arithmeticSubSumComponent.recorder_02 = instructionComponent.instructions[i].recorder_02;

			arithmeticUnitToString(&arithmeticSubSumComponent);
			sum(&arithmeticSubSumComponent);
			arithmeticUnitToString(&arithmeticSubSumComponent);

			arithmeticSubSumComponent.busy = false;
		} else if (strcmp(instructionComponent.instructions[i].type, "sub") == 0) {
			arithmeticSubSumComponent.busy = true;
			strcpy(arithmeticSubSumComponent.type, "sub");
			arithmeticSubSumComponent.recorder_00 = instructionComponent.instructions[i].recorder_00;
			arithmeticSubSumComponent.recorder_01 = instructionComponent.instructions[i].recorder_01;
			arithmeticSubSumComponent.recorder_02 = instructionComponent.instructions[i].recorder_02;

			arithmeticUnitToString(&arithmeticSubSumComponent);
			subtraction(&arithmeticSubSumComponent);
			arithmeticUnitToString(&arithmeticSubSumComponent);

			arithmeticSubSumComponent.busy = false;
		} else if (strcmp(instructionComponent.instructions[i].type, "mul") == 0) {
			arithmeticMulDivComponent.busy = true;
			strcpy(arithmeticMulDivComponent.type, "mul");
			arithmeticMulDivComponent.recorder_00 = instructionComponent.instructions[i].recorder_00;
			arithmeticMulDivComponent.recorder_01 = instructionComponent.instructions[i].recorder_01;
			arithmeticMulDivComponent.recorder_02 = instructionComponent.instructions[i].recorder_02;

			arithmeticUnitToString(&arithmeticMulDivComponent);
			multiplication(&arithmeticMulDivComponent);
			arithmeticUnitToString(&arithmeticMulDivComponent);

			arithmeticMulDivComponent.busy = false;
		} else if (strcmp(instructionComponent.instructions[i].type, "div") == 0) {
			if (instructionComponent.instructions[i].recorder_02->value != 0) {
				arithmeticMulDivComponent.busy = true;
				strcpy(arithmeticMulDivComponent.type, "div");
				arithmeticMulDivComponent.recorder_00 = instructionComponent.instructions[i].recorder_00;
				arithmeticMulDivComponent.recorder_01 = instructionComponent.instructions[i].recorder_01;
				arithmeticMulDivComponent.recorder_02 = instructionComponent.instructions[i].recorder_02;

				arithmeticUnitToString(&arithmeticMulDivComponent);
				division(&arithmeticMulDivComponent);
				arithmeticUnitToString(&arithmeticMulDivComponent);

				arithmeticMulDivComponent.busy = false;
			} else {
				printf("\nERRO: Divisao por zero detectada.\n");
			}
		} else if (strcmp(instructionComponent.instructions[i].type, "load") == 0) {

		} else if (strcmp(instructionComponent.instructions[i].type, "store") == 0) {

		} else {
			printf("\nERRO: Operacao nao reconhecida!\n");
		}
	}

	memoryComponentToString(&memoryComponent);

	printf("Aqui 3\n");

	return 0;
}