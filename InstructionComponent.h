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

void createInstructions(InstructionComponent *instructionComponent, RecorderPFComponent *recorderPFComponent, MatrixDepedencyRecorder *matrixDepedencyRecorder) 
{
	char types[6][15] = {"add", "sub", "mul", "div", "load", "store"};
	instructionConstructor_01(&instructionComponent->instructions[0], types[rand()%6], &recorderPFComponent->recorders[0], &recorderPFComponent->recorders[1], &recorderPFComponent->recorders[2], false);
	matrixDepedencyRecorder->row[1].col[0] = 2;
	matrixDepedencyRecorder->row[2].col[0] = 2;
	matrixDepedencyRecorder->row[0].col[0] = 1;

	instructionConstructor_01(&instructionComponent->instructions[1], types[rand()%6], &recorderPFComponent->recorders[3], &recorderPFComponent->recorders[4], &recorderPFComponent->recorders[5], false);
	matrixDepedencyRecorder->row[4].col[1] = 2;
	matrixDepedencyRecorder->row[5].col[1] = 2;
	matrixDepedencyRecorder->row[3].col[1] = 1;

	instructionConstructor_01(&instructionComponent->instructions[2], types[rand()%6], &recorderPFComponent->recorders[4], &recorderPFComponent->recorders[0], &recorderPFComponent->recorders[3], false);
	matrixDepedencyRecorder->row[0].col[2] = 2;
	matrixDepedencyRecorder->row[3].col[2] = 2;
	matrixDepedencyRecorder->row[4].col[2] = 1;
}

void createInstructionsRandom(InstructionComponent *instructionComponent, RecorderPFComponent *recorderPFComponent) 
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