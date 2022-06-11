/*
	-----------------------------------
	MemoryUnit.h 
	Author: Ricardo Portilho de Andrade 
	-----------------------------------
	Objetivo: Esse codigo representa a
	unidade que faz operacoes de acesso
	e memoria.
	-----------------------------------
	Bibliotecas necessarias:
	* Recorder.h
	* MemoryComponent.h
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