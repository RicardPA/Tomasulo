/*
	-----------------------------------
	MemoryComponent.h 
	Author: Ricardo Portilho de Andrade 
	-----------------------------------
	Objetivo: Esse codigo representa um
	componente que armazena os dados
	que seram utilizados nas operacoes
	de load e store.
	-----------------------------------
	Bibliotecas necessarias:
	* Memory.h
*/

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