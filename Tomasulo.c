#include <stdio.h>
#include <stdbool.h>

/*
	Title: Celulas de Componentes
	Obs: Abaixo temos structs que seram utilizadas para
	representar regioes de componentes maiores.
*/

/* - - - - - - Registrador - - - - - - */
typedef struct 
{
	int value;
	bool busy;
	int address;
} Recorder;

Recorder recorderConstructor_00() {
	Recorder auxRecorder;

	auxRecorder.value = -1;
	auxRecorder.busy = false;
	auxRecorder.address = -1;	

	return(auxRecorder);
}

Recorder recorderConstructor_01(int value, bool busy, int address) {
	Recorder auxRecorder;

	auxRecorder.value = value;
	auxRecorder.busy = busy;
	auxRecorder.address = address;	

	return(auxRecorder);
}

/* - - - - - - Memoria - - - - - - */
typedef struct 
{
	int value;
	int address;
} Memory;

/* - - - - - - Instrucao - - - - - - */
typedef struct 
{
	int value;
	int address;
	char type[15];
	Recorder recorder;
} Instruction;

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
	printf("Unidade de destino: %d  Busy: %d \n", memory->recorder_00.value, memory->recorder_00.busy);
	printf("Unidade variavel: %d  Busy: %d \n", memory->recorder_01.value, memory->recorder_01.busy);
	printf("Unidade variavel: %d  Busy: %d \n", memory->recorder_02.value, memory->recorder_02.busy);
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
	Instruction instructions[30];
} InstructionComponent;

typedef struct 
{
	Instruction instructions[30];
} RecorderPFComponent;

typedef struct 
{
	Memory data[30];
} MemoryComponent;

int main(void) 
{

	return 0;
}