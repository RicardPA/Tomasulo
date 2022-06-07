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
	char type[15];
	Recorder recorder_00;
	Recorder recorder_01;
	Recorder recorder_02;
} Instruction;

void instructionConstructor_00(Instruction *auxInstruction) {
	strcpy (auxInstruction->type, "");
	recorderConstructor_00(&auxInstruction->recorder_00);
	recorderConstructor_00(&auxInstruction->recorder_01);
	recorderConstructor_00(&auxInstruction->recorder_02);
}

void instructionConstructor_01(Instruction *auxInstruction, char type[], Recorder *recorder_00, Recorder *recorder_01, Recorder *recorder_02) {
	strcpy (auxInstruction->type, type);

	auxInstruction->recorder_00.busy = recorder_00->busy;
	auxInstruction->recorder_00.value = recorder_00->value;
	auxInstruction->recorder_00.address = recorder_00->address;

	auxInstruction->recorder_01.busy = recorder_01->busy;
	auxInstruction->recorder_01.value = recorder_01->value;
	auxInstruction->recorder_01.address = recorder_01->address;

	auxInstruction->recorder_02.busy = recorder_02->busy;
	auxInstruction->recorder_02.value = recorder_02->value;
	auxInstruction->recorder_02.address = recorder_02->address;
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
		printf("Tipo: %s | ", instructionComponent->instructions[i].type); 
		printf("Endereco: %d | ", instructionComponent->instructions[i].address); 
		printf("Valor: %d", instructionComponent->instructions[i].value);
	}

	printf("\t --- \n");
}

void createInstructions(InstructionComponent *instructionComponent) 
{
	for(int i = 0; i < LENGTH_INSTRUCTIONS; i = i + 5) 
	{
		instructionConstructor_01(instructionComponent->instructions[i], "add", );
		instructionConstructor_01(instructionComponent->instructions[i+1], "subtraction", );
		instructionConstructor_01(instructionComponent->instructions[i+2], "multiplication", );
		instructionConstructor_01(instructionComponent->instructions[i+3], "division", );
		instructionConstructor_01(instructionComponent->instructions[i+4], "add", );
	}
}

typedef struct 
{
	Recorder recorders[LENGTH_RECORDER];
} RecorderPFComponent;

void createRecorderFP(RecorderPFComponent *recorderPFComponent) 
{
	for(int i = 0; i < LENGTH_INSTRUCTIONS; i = i + 5) 
	{
		recorderConstructor_01(instructionComponent->instructions[i], "add", );
		recorderConstructor_01(instructionComponent->instructions[i+1], "subtraction", );
		recorderConstructor_01(instructionComponent->instructions[i+2], "multiplication", );
		recorderConstructor_01(instructionComponent->instructions[i+3], "division", );
	}
}

typedef struct 
{
	Memory data[LENGTH_MEMORY];
} MemoryComponent;

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
	MemoryComponent memory;
} MemoryUnit;

void memoryUnitToString(MemoryUnit *memory) 
{
	printf("\n\t --- Dados da Memoria ---\n");
	printf("Unidade de destino: %d | Busy: %d | Address: %d \n", memory->recorder_00.value, memory->recorder_00.busy, memory->recorder_00.address);
	printf("Unidade variavel: %d | Busy: %d | Address: %d \n", memory->recorder_01.value, memory->recorder_01.busy, memory->recorder_01.address);
	printf("Unidade variavel: %d | Busy: %d Address: %d \n", memory->recorder_02.value, memory->recorder_02.busy, memory->recorder_02.address);
}

void load(MemoryUnit *memory) 
{
	// Marcar como sendo usado
	memory->recorder_00.busy = true;
	memory->recorder_01.busy = true;
	memory->recorder_02.busy = true;

	// Fazer operacao
	memory->recorder_00.value = memory->memory[memory->recorder_01.value + memory->recorder_02.address];

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
	memory->memory[memory->recorder_01.value + memory->recorder_02.address] = memory->recorder_00.value;

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

void arithmeticUnitConstructor_00(ArithmeticUnit *auxArithmetic) {
	auxArithmetic->busy = false;
	recorderConstructor_00(&auxArithmetic->recorder_00);
	recorderConstructor_00(&auxArithmetic->recorder_01);
	recorderConstructor_00(&auxArithmetic->recorder_02);
}

void arithmeticUnitConstructor_01(ArithmeticUnit *auxArithmetic, bool busy, Recorder *recorder_00, Recorder *recorder_01, Recorder *recorder_02) {
	auxArithmetic->busy = false;

	auxArithmetic->recorder_00.busy = recorder_00->busy;
	auxArithmetic->recorder_00.value = recorder_00->value;
	auxArithmetic->recorder_00.address = recorder_00->address;

	auxArithmetic->recorder_01.busy = recorder_01->busy;
	auxArithmetic->recorder_01.value = recorder_01->value;
	auxArithmetic->recorder_01.address = recorder_01->address;

	auxArithmetic->recorder_02.busy = recorder_02->busy;
	auxArithmetic->recorder_02.value = recorder_02->value;
	auxArithmetic->recorder_02.address = recorder_02->address;
}

void arithmeticUnitToString(ArithmeticUnit *arithmetic) 
{
	printf("\n\t --- Dados da Unidade Aritmetica ---\n");
	printf("Unidade de destino: %d | Busy: %d | Address: %d \n", arithmetic->recorder_00.value, arithmetic->recorder_00.busy, arithmetic->recorder_00.address);
	printf("Unidade variavel: %d | Busy: %d | Address: %d \n", arithmetic->recorder_01.value, arithmetic->recorder_01.busy, arithmetic->recorder_01.address);
	printf("Unidade variavel: %d | Busy: %d | Address: %d \n", arithmetic->recorder_02.value, arithmetic->recorder_02.busy, arithmetic->recorder_01.address);
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

int main(void) 
{
	char type[15];
	Instruction instruction_01, instruction_02, instruction_03, instruction_04;

	createInstructions();

	instructionConstructor_01(&instruction_01, "add", &recorder_01, &recorder_02, &recorder_03)
	instructionConstructor_01(&instruction_02, "subtraction", &recorder_01, &recorder_02, &recorder_03)
	instructionConstructor_01(&instruction_02, "multiplication", &recorder_01, &recorder_02, &recorder_03)
	instructionConstructor_01(&instruction_02, "division", &recorder_01, &recorder_02, &recorder_03)

	strcpy(type, instruction_01.type)

	switch() {
		case :
			break;
		case :
			break;
		case :
			break;
		case :
			break;
		default:
			printf("ERRO: Operacao nao reconhecida!!! \n");
	}

	return 0;
}