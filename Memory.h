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