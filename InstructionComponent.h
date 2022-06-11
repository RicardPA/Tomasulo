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
	// Caminhar pelas linhas da matriz de dependencia
	for(int i = 0; i < LENGTH_RECORDER; i++) {
		// Caminhar pelas colunas da matriz de dependencia
		for(int j = 0; j < LENGTH_INSTRUCTIONS; j++) {
			matrixDepedencyRecorder->row[i].col[j] = 0;
		}
	}

	char types[6][15] = {"add", "sub", "mul", "div", "load", "store"};
	instructionConstructor_01(&instructionComponent->instructions[0], types[rand()%6], &recorderPFComponent->recorders[0], &recorderPFComponent->recorders[1], &recorderPFComponent->recorders[2], false);
	matrixDepedencyRecorder->row[i].col[j] = 0;
	instructionConstructor_01(&instructionComponent->instructions[1], types[rand()%6], &recorderPFComponent->recorders[3], &recorderPFComponent->recorders[4], &recorderPFComponent->recorders[5], false);
	
	instructionConstructor_01(&instructionComponent->instructions[2], types[rand()%6], &recorderPFComponent->recorders[4], &recorderPFComponent->recorders[0], &recorderPFComponent->recorders[3], false);
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