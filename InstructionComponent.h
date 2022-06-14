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

void createInstructionsRandom(InstructionComponent *instructionComponent, RecorderPFComponent *recorderPFComponent, MatrixDepedencyRecorder *matrixDepedencyRecorder) 
{
	char types[6][15] = {"add", "sub", "mul", "div", "load", "store"};
	for(int i = 0; i < LENGTH_INSTRUCTIONS; i++) 
	{
		int recorder_00 = rand()%LENGTH_RECORDER;
		int recorder_01 = rand()%LENGTH_RECORDER;
		int recorder_02 = rand()%LENGTH_RECORDER;
		instructionConstructor_01(&instructionComponent->instructions[i], types[rand()%6], &recorderPFComponent->recorders[recorder_00], &recorderPFComponent->recorders[recorder_01], &recorderPFComponent->recorders[recorder_02], false);
		matrixDepedencyRecorder->row[recorder_02].col[i] = 2;
		matrixDepedencyRecorder->row[recorder_01].col[i] = 2;
		matrixDepedencyRecorder->row[recorder_00].col[i] = 1;
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