/*
	-----------------------------------
	InstructionComponent.h 
	Author: Ricardo Portilho de Andrade 
	-----------------------------------
	Objetivo: Esse codigo representa um
	componente que armazena as instrucoes
	que seram utilizados nos testes.
	-----------------------------------
	Bibliotecas necessarias:
	* Instruction.h
*/

/* - - - - - - Lista de Instrucao - - - - - - */

typedef struct 
{
	Instruction instructions[LENGTH_INSTRUCTIONS];
} InstructionComponent;

void createInstructions(InstructionComponent *instructionComponent, RecorderPFComponent *recorderPFComponent) 
{
	char types[6][15] = {"add", "sub", "mul", "div", "load", "store"};
	for(int i = 0; i < LENGTH_INSTRUCTIONS; i++) 
	{
		instructionConstructor_01(&instructionComponent->instructions[i], types[rand()%6], &recorderPFComponent->recorders[rand()%LENGTH_RECORDER], &recorderPFComponent->recorders[rand()%LENGTH_RECORDER], &recorderPFComponent->recorders[rand()%LENGTH_RECORDER], false);
	}
}

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