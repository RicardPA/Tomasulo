/*
	-----------------------------------
	Memory.h 
	Author: Ricardo Portilho de Andrade 
	-----------------------------------
	Objetivo: Esse codigo representa as 
	informacoes necessarias para criar 
	um componente de memoria.
*/

/* - - - - - - Memoria - - - - - - */
typedef struct 
{
	int value;
	int address;
	bool busy;
} Memory;

void memoryConstructor_01(Memory *auxMemory, int value, int address, bool busy) 
{
	auxMemory->value = value;
	auxMemory->address = address;
	auxMemory->busy = busy;
}