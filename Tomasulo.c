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

#define LENGTH_MEMORY 20
#define LENGTH_RECORDER 5
#define LENGTH_INSTRUCTIONS 500

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

void recorderConstructor_01(Recorder *auxRecorder, int value, bool busy, int address) {
	auxRecorder->value = value;
	auxRecorder->busy = busy;
	auxRecorder->address = address;
}

void recorderToString(Recorder *auxRecorder) {
	printf("|--- Registrador: (");
	printf("Valor: %d\t| ", auxRecorder->value);
	printf("Usado: %d\t| ",auxRecorder->busy);
	printf("Endereco: %d) \n", auxRecorder->address);	
}

/* - - - - - - Memoria - - - - - - */
typedef struct 
{
	int value;
	int address;
	bool busy;
} Memory;

void memoryConstructor_01(Memory *auxMemory, int value, int address, bool busy) {
	auxMemory->value = value;
	auxMemory->address = address;
	auxMemory->busy = busy;
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
	for(int i = 0; i < LENGTH_RECORDER; i++) 
	{
		recorderConstructor_01(&recorderPFComponent->recorders[i], rand()%(1000*(i+rand()%100)), false, i);
	}
}

void recorderFPToString(RecorderPFComponent *recorderPFComponent) 
{
	printf("|--- Registradores ---\n");
	for(int i = 0; i < LENGTH_RECORDER; i++) 
	{
		printf("| ");
		recorderToString(&recorderPFComponent->recorders[i]);
	}
	printf("|------------------------------\n");
}
/* - - - - - - Lista de Instrucao - - - - - - */

typedef struct 
{
	Instruction instructions[LENGTH_INSTRUCTIONS];
} InstructionComponent;

void instructionComponentToString(InstructionComponent *instructionComponent) 
{
	printf("\n|--- Instrucoes --- \n| \n");

	for(int i = 0; i < LENGTH_INSTRUCTIONS; i++) 
	{
		printf("|--- Instrucao --- \n| Tipo: %s", instructionComponent->instructions[i].type); 
		printf("\n(Destino) \n"); 
		recorderToString(instructionComponent->instructions[i].recorder_00);
		printf("(Operando_01) \n");
		recorderToString(instructionComponent->instructions[i].recorder_01);
		printf("(Operando_02)\n");
		recorderToString(instructionComponent->instructions[i].recorder_02);
		printf("|\n|--------------- \n");
	}
}

void createInstructions(InstructionComponent *instructionComponent, RecorderPFComponent *recorderPFComponent) 
{
	char types[6][15] = {"add", "sub", "mul", "div", "load", "store"};
	for(int i = 0; i < LENGTH_INSTRUCTIONS; i++) 
	{
		instructionConstructor_01(&instructionComponent->instructions[i], types[rand()%6], &recorderPFComponent->recorders[rand()%LENGTH_RECORDER], &recorderPFComponent->recorders[rand()%LENGTH_RECORDER], &recorderPFComponent->recorders[rand()%LENGTH_RECORDER]);
	}
}

/* - - - - - - Memoria Secundaria - - - - - - */

typedef struct 
{
	Memory data[LENGTH_MEMORY];
} MemoryComponent;

void createMemoryComponent(MemoryComponent *memoryComponent) 
{
	for(int i = 0; i < LENGTH_MEMORY; i++) 
	{
		memoryConstructor_01(&memoryComponent->data[i], 0, i, false);
	}
}

void memoryComponentToString(MemoryComponent *memoryComponent) 
{
	printf("\n|--- Memoria ---\n");
	for(int i = 0; i < LENGTH_MEMORY; i++) 
	{
		printf("| Valor: %d\t| Endereco: %d\t| Busy: %d\n", memoryComponent->data[i].value, memoryComponent->data[i].address, memoryComponent->data[i].busy);
	}
	printf("|------------------------------\n");
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
	char type[15];
	Recorder *recorder_00; // unidade de destino
	Recorder *recorder_01; // unidade variavel 
	Recorder *recorder_02; // unidade variavel
	MemoryComponent *memory;
} MemoryUnit;

void memoryUnitToString(MemoryUnit *memory) 
{
	// Variaveis
	int position = (abs(memory->recorder_01->value + memory->recorder_02->value))%LENGTH_MEMORY;

	printf("\n|--- Dados da Memoria (%s) ---\n", memory->type);
	printf("| Unidade de destino (Valor: %d | Busy: %d | Address: %d) \n", memory->recorder_00->value, memory->recorder_00->busy, memory->recorder_00->address);
	printf("| Unidade variavel (Valor: %d | Busy: %d | Address: %d) \n", memory->recorder_01->value, memory->recorder_01->busy, memory->recorder_01->address);
	printf("| Unidade variavel (Valor: %d | Busy: %d | Address: %d) \n", memory->recorder_02->value, memory->recorder_02->busy, memory->recorder_02->address);
	printf("| Memoria (Valor: %d | ", memory->memory->data[position].value);
	printf("| Endereco: %d)\n", memory->memory->data[position].address);
}

void load(MemoryUnit *memory) 
{
	// Variaveis 
	int position = (abs(memory->recorder_01->value + memory->recorder_02->value))%LENGTH_MEMORY;

	while(memory->memory->data[position].busy || memory->recorder_00->busy || memory->recorder_01->busy || memory->recorder_02->busy);

	// Marcar como sendo usado
	memory->recorder_00->busy = true;
	memory->recorder_01->busy = true;
	memory->recorder_02->busy = true;
	memory->memory->data[position].busy = true;

	// Fazer operacao
	memory->recorder_00->value = memory->memory->data[position].value;

	// Marcar como nao sendo usado
	memory->recorder_00->busy = false;
	memory->recorder_01->busy = false;
	memory->recorder_02->busy = false;
	memory->memory->data[position].busy = false;
}

void store(MemoryUnit *memory) 
{
	// Variaveis
	int position = (abs(memory->recorder_01->value + memory->recorder_02->value))%LENGTH_MEMORY;
	
	while(memory->memory->data[position].busy || memory->recorder_00->busy || memory->recorder_01->busy || memory->recorder_02->busy);
	
	// Marcar como sendo usado
	memory->recorder_00->busy = true;
	memory->recorder_01->busy = true;
	memory->recorder_02->busy = true;
	memory->memory->data[position].busy = true;

	// Fazer operacao
	memory->memory->data[position].value = memory->recorder_00->value;

	// Marcar como nao sendo usado
	memory->recorder_00->busy = false;
	memory->recorder_01->busy = false;
	memory->recorder_02->busy = false;
	memory->memory->data[position].busy = false;
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

void arithmeticUnitConstructor_01(ArithmeticUnit *auxArithmetic, bool busy, Recorder *recorder_00, Recorder *recorder_01, Recorder *recorder_02) {
	auxArithmetic->busy = false;
	auxArithmetic->recorder_00 = recorder_00;
	auxArithmetic->recorder_01 = recorder_01;
	auxArithmetic->recorder_02 = recorder_02;
}

void arithmeticUnitToString(ArithmeticUnit *arithmetic) 
{
	printf("\n|--- Dados da Unidade Aritmetica (%s) ---\n", arithmetic->type);
	printf("| Unidade de destino (Valor: %d | Busy: %d | Address: %d) \n", arithmetic->recorder_00->value, arithmetic->recorder_00->busy, arithmetic->recorder_00->address);
	printf("| Unidade variavel (Valor: %d | Busy: %d | Address: %d) \n", arithmetic->recorder_01->value, arithmetic->recorder_01->busy, arithmetic->recorder_01->address);
	printf("| Unidade variavel (Valor: %d | Busy: %d | Address: %d) \n", arithmetic->recorder_02->value, arithmetic->recorder_02->busy, arithmetic->recorder_02->address);
}

void sum(ArithmeticUnit *arithmetic) 
{
	while(arithmetic->recorder_00->busy || arithmetic->recorder_01->busy || arithmetic->recorder_02->busy);
	
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
	while(arithmetic->recorder_00->busy || arithmetic->recorder_01->busy || arithmetic->recorder_02->busy);
	
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
	while(arithmetic->recorder_00->busy || arithmetic->recorder_01->busy || arithmetic->recorder_02->busy);

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
	while(arithmetic->recorder_00->busy || arithmetic->recorder_01->busy || arithmetic->recorder_02->busy);

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
	// Componentes
	InstructionComponent instructionComponent;
	RecorderPFComponent recorderPFComponent;
	MemoryComponent memoryComponent;

	// Unidades de operacao
	ArithmeticUnit arithmeticSubSumComponent, arithmeticMulDivComponent;
	MemoryUnit memoryLoadStoreComponent;

	// Inicializar unidades de operacoes
	arithmeticSubSumComponent.busy = false;
	arithmeticMulDivComponent.busy = false;
	memoryLoadStoreComponent.busy = false;

	// Inicializar componentes
	createMemoryComponent(&memoryComponent);
	createRecorderFP(&recorderPFComponent);
	createInstructions(&instructionComponent, &recorderPFComponent);
	
	memoryComponentToString(&memoryComponent);
    // instructionComponentToString(&instructionComponent);

	for(int i = 0; i < LENGTH_INSTRUCTIONS; i++) 
	{
		printf("\n_____________________________________________________________\n");
		
		recorderFPToString(&recorderPFComponent);

		if (strcmp(instructionComponent.instructions[i].type, "add") == 0) {
			while(arithmeticSubSumComponent.busy);

			arithmeticSubSumComponent.busy = true;
			strcpy(arithmeticSubSumComponent.type, "add");
			arithmeticSubSumComponent.recorder_00 = instructionComponent.instructions[i].recorder_00;
			arithmeticSubSumComponent.recorder_01 = instructionComponent.instructions[i].recorder_01;
			arithmeticSubSumComponent.recorder_02 = instructionComponent.instructions[i].recorder_02;

			arithmeticUnitToString(&arithmeticSubSumComponent);
			sum(&arithmeticSubSumComponent);
			arithmeticUnitToString(&arithmeticSubSumComponent);

			arithmeticSubSumComponent.busy = false;
			strcpy(arithmeticSubSumComponent.type, "");
		} else if (strcmp(instructionComponent.instructions[i].type, "sub") == 0) {
			while(arithmeticSubSumComponent.busy);

			arithmeticSubSumComponent.busy = true;
			strcpy(arithmeticSubSumComponent.type, "sub");
			arithmeticSubSumComponent.recorder_00 = instructionComponent.instructions[i].recorder_00;
			arithmeticSubSumComponent.recorder_01 = instructionComponent.instructions[i].recorder_01;
			arithmeticSubSumComponent.recorder_02 = instructionComponent.instructions[i].recorder_02;

			arithmeticUnitToString(&arithmeticSubSumComponent);
			subtraction(&arithmeticSubSumComponent);
			arithmeticUnitToString(&arithmeticSubSumComponent);

			arithmeticSubSumComponent.busy = false;
			strcpy(arithmeticSubSumComponent.type, "");
		} else if (strcmp(instructionComponent.instructions[i].type, "mul") == 0) {
			while(arithmeticMulDivComponent.busy);

			arithmeticMulDivComponent.busy = true;
			strcpy(arithmeticMulDivComponent.type, "mul");
			arithmeticMulDivComponent.recorder_00 = instructionComponent.instructions[i].recorder_00;
			arithmeticMulDivComponent.recorder_01 = instructionComponent.instructions[i].recorder_01;
			arithmeticMulDivComponent.recorder_02 = instructionComponent.instructions[i].recorder_02;

			arithmeticUnitToString(&arithmeticMulDivComponent);
			multiplication(&arithmeticMulDivComponent);
			arithmeticUnitToString(&arithmeticMulDivComponent);

			arithmeticMulDivComponent.busy = false;
			strcpy(arithmeticMulDivComponent.type, "");
		} else if (strcmp(instructionComponent.instructions[i].type, "div") == 0) {
			while(arithmeticMulDivComponent.busy);

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
				strcpy(arithmeticMulDivComponent.type, "");
			} else {
				printf("\nERRO: Divisao por zero detectada.\n");
			}
		} else if (strcmp(instructionComponent.instructions[i].type, "load") == 0) {
			while(memoryLoadStoreComponent.busy);

			memoryLoadStoreComponent.busy = true;
			strcpy(memoryLoadStoreComponent.type, "load");
			memoryLoadStoreComponent.recorder_00 = instructionComponent.instructions[i].recorder_00;
			memoryLoadStoreComponent.recorder_01 = instructionComponent.instructions[i].recorder_01;
			memoryLoadStoreComponent.recorder_02 = instructionComponent.instructions[i].recorder_02;
			memoryLoadStoreComponent.memory = &memoryComponent;

			memoryUnitToString(&memoryLoadStoreComponent);
			load(&memoryLoadStoreComponent);
			memoryUnitToString(&memoryLoadStoreComponent);

			memoryLoadStoreComponent.busy = false;
			strcpy(memoryLoadStoreComponent.type, "");
		} else if (strcmp(instructionComponent.instructions[i].type, "store") == 0) {
			while(memoryLoadStoreComponent.busy);

			memoryLoadStoreComponent.busy = true;
			strcpy(memoryLoadStoreComponent.type, "store");
			memoryLoadStoreComponent.recorder_00 = instructionComponent.instructions[i].recorder_00;
			memoryLoadStoreComponent.recorder_01 = instructionComponent.instructions[i].recorder_01;
			memoryLoadStoreComponent.recorder_02 = instructionComponent.instructions[i].recorder_02;
			memoryLoadStoreComponent.memory = &memoryComponent;

			memoryUnitToString(&memoryLoadStoreComponent);
			store(&memoryLoadStoreComponent);
			memoryUnitToString(&memoryLoadStoreComponent);

			memoryLoadStoreComponent.busy = false;
			strcpy(memoryLoadStoreComponent.type, "");
		} else {
			printf("\nERRO: Operacao nao reconhecida!\n");
		}
	}

	memoryComponentToString(&memoryComponent);
	
	return 0;
}