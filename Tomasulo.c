/*
	-----------------------------------
	Tomasulo.c 
	Author: Ricardo Portilho de Andrade 
	-----------------------------------
	Unidade principal que sera usada
	como partida para testes.
*/

/* Bibliotecas da Linguagem */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <omp.h>

// Valores definidos
#define LENGTH_INSTRUCTIONS 3 
#define LENGTH_RECORDER 6
#define LENGTH_MEMORY 6
#define LENGTH_BUFFER (LENGTH_RECORDER*2)

// Matriz necessaria para tratar dependencias
typedef struct 
{
	int col[LENGTH_INSTRUCTIONS];
} RowMatrixDepedencyRecorder;

typedef struct 
{
	RowMatrixDepedencyRecorder row[LENGTH_RECORDER];
} MatrixDepedencyRecorder;

void createMatrixDepedencyRecorder(MatrixDepedencyRecorder *matrixDepedencyRecorder)
{
	// Linhas 
	for(int i = 0; i < LENGTH_RECORDER; i++) 
	{
		// Colunas
		for(int j = 0; j < LENGTH_INSTRUCTIONS; j++) 
		{
			matrixDepedencyRecorder->row[i].col[j] = 0;
		}
	}
}

void printMatrixDepedencyRecorder(MatrixDepedencyRecorder *matrixDepedencyRecorder)
{
	// Linhas 
	for(int i = 0; i < LENGTH_RECORDER; i++) 
	{
		printf("Recorder(%d)\t| ", i);
		// Colunas
		for(int j = 0; j < LENGTH_INSTRUCTIONS; j++) 
		{
			printf("%d ", matrixDepedencyRecorder->row[i].col[j]);
		}
		printf("|\n");
	}
}

int checkTrueDependency(MatrixDepedencyRecorder *matrixDepedencyRecorder, int positionInstruction, int positionRecorder)
{
	int instructionDependency = -1;

	for(int i = positionInstruction-1; i >= 0 && instructionDependency == -1; i--) 
	{
		if(matrixDepedencyRecorder->row[positionRecorder].col[i] == 1) 
		{
			instructionDependency = i;		
		}
	}

	return instructionDependency;
}

int checkFalseDependency(MatrixDepedencyRecorder *matrixDepedencyRecorder, int positionInstruction, int positionRecorder)
{
	int instructionDependency = -1;

	for(int i = positionInstruction+1; i < LENGTH_INSTRUCTIONS && instructionDependency == -1; i++) 
	{
		if(matrixDepedencyRecorder->row[positionRecorder].col[i] == 1) 
		{
			instructionDependency = i;		
		}
	}

	return instructionDependency;
}


/* Bibliotecas do Projeto */
// Unidedes de componentes
#include "Memory.h"
#include "Recorder.h"
#include "Instruction.h"
// Componentes
#include "RecorderPFComponent.h"
#include "InstructionComponent.h"
#include "MemoryComponent.h"
#include "BufferComponent.h"
// Unidades de operacao
#include "MemoryUnit.h"
#include "ArithmeticUnit.h"

int main(void) 
{
	// Matriz de dependencia
	MatrixDepedencyRecorder matrixDepedencyRecorder;

	// Componentes
	InstructionComponent instructionComponent;
	RecorderPFComponent recorderPFComponent;
	MemoryComponent memoryComponent;
	BufferComponent buffer;

	// Unidades de operacao
	ArithmeticUnit arithmeticSubSumComponent, arithmeticMulDivComponent;
	MemoryUnit memoryLoadStoreComponent;

	// Inicializar unidades de operacoes
	arithmeticSubSumComponent.busy = false;
	arithmeticMulDivComponent.busy = false;
	memoryLoadStoreComponent.busy = false;

	// Inicializar componentes
	createMatrixDepedencyRecorder(&matrixDepedencyRecorder);
	createMemoryComponent(&memoryComponent);
	createBuffer(&buffer);
	createRecorderFP(&recorderPFComponent);
	createInstructionsRandom(&instructionComponent, &recorderPFComponent, &matrixDepedencyRecorder);

	printf("\n\n----------------------------- [Antes] ---------------------------------: \n");
	instructionComponentToString(&instructionComponent);
	recorderFPToString(&recorderPFComponent);
	printf("\n\nBuffer: \n");
	bufferToString(&buffer);
	memoryComponentToString(&memoryComponent);

	#pragma omp parallel for
	for(int i = 0; i < LENGTH_INSTRUCTIONS; i++) 
	{
		// Verificar dependencias
		int instructionTrueDependency[] = {-1, -1, -1};
		int instructionFalseDependency[] = {-1, -1};

		instructionTrueDependency[0] = checkTrueDependency(&matrixDepedencyRecorder, i, instructionComponent.instructions[i].recorder_00->address);
		instructionTrueDependency[1] = checkTrueDependency(&matrixDepedencyRecorder, i, instructionComponent.instructions[i].recorder_01->address);
		instructionTrueDependency[2] = checkTrueDependency(&matrixDepedencyRecorder, i, instructionComponent.instructions[i].recorder_02->address);

		instructionFalseDependency[0] = checkFalseDependency(&matrixDepedencyRecorder, i, instructionComponent.instructions[i].recorder_01->address);
		instructionFalseDependency[1] = checkFalseDependency(&matrixDepedencyRecorder, i, instructionComponent.instructions[i].recorder_02->address);
		
		while(instructionTrueDependency[0] >= 0 && instructionComponent.instructions[instructionTrueDependency[0]].done == false);
		while(instructionTrueDependency[1] >= 0 && instructionComponent.instructions[instructionTrueDependency[1]].done == false);
		while(instructionTrueDependency[2] >= 0 && instructionComponent.instructions[instructionTrueDependency[2]].done == false);
		
		if(instructionFalseDependency[0] != -1)
			alocBuffer(&buffer, &instructionComponent.instructions[i], instructionComponent.instructions[i].recorder_01);
		if(instructionFalseDependency[1] != -1)
			alocBuffer(&buffer, &instructionComponent.instructions[i], instructionComponent.instructions[i].recorder_02);
	
		// Executar instrucoes
		if (strcmp(instructionComponent.instructions[i].type, "add") == 0) 
		{
			while(arithmeticSubSumComponent.busy);

			arithmeticSubSumComponent.busy = true;
			strcpy(arithmeticSubSumComponent.type, "add");
			arithmeticSubSumComponent.recorder_00 = instructionComponent.instructions[i].recorder_00;
			arithmeticSubSumComponent.recorder_01 = instructionComponent.instructions[i].recorder_01;
			arithmeticSubSumComponent.recorder_02 = instructionComponent.instructions[i].recorder_02;

			sum(&arithmeticSubSumComponent);

			arithmeticSubSumComponent.busy = false;
			strcpy(arithmeticSubSumComponent.type, "");
		} 
		else if (strcmp(instructionComponent.instructions[i].type, "sub") == 0) 
		{
			while(arithmeticSubSumComponent.busy);

			arithmeticSubSumComponent.busy = true;
			strcpy(arithmeticSubSumComponent.type, "sub");
			arithmeticSubSumComponent.recorder_00 = instructionComponent.instructions[i].recorder_00;
			arithmeticSubSumComponent.recorder_01 = instructionComponent.instructions[i].recorder_01;
			arithmeticSubSumComponent.recorder_02 = instructionComponent.instructions[i].recorder_02;

			subtraction(&arithmeticSubSumComponent);

			arithmeticSubSumComponent.busy = false;
			strcpy(arithmeticSubSumComponent.type, "");
		} 
		else if (strcmp(instructionComponent.instructions[i].type, "mul") == 0) 
		{
			while(arithmeticMulDivComponent.busy);

			arithmeticMulDivComponent.busy = true;
			strcpy(arithmeticMulDivComponent.type, "mul");
			arithmeticMulDivComponent.recorder_00 = instructionComponent.instructions[i].recorder_00;
			arithmeticMulDivComponent.recorder_01 = instructionComponent.instructions[i].recorder_01;
			arithmeticMulDivComponent.recorder_02 = instructionComponent.instructions[i].recorder_02;

			multiplication(&arithmeticMulDivComponent);

			arithmeticMulDivComponent.busy = false;
			strcpy(arithmeticMulDivComponent.type, "");
		} 
		else if (strcmp(instructionComponent.instructions[i].type, "div") == 0) 
		{
			while(arithmeticMulDivComponent.busy);

			if (instructionComponent.instructions[i].recorder_02->value != 0) 
			{
				arithmeticMulDivComponent.busy = true;
				strcpy(arithmeticMulDivComponent.type, "div");
				arithmeticMulDivComponent.recorder_00 = instructionComponent.instructions[i].recorder_00;
				arithmeticMulDivComponent.recorder_01 = instructionComponent.instructions[i].recorder_01;
				arithmeticMulDivComponent.recorder_02 = instructionComponent.instructions[i].recorder_02;


				division(&arithmeticMulDivComponent);

				arithmeticMulDivComponent.busy = false;
				strcpy(arithmeticMulDivComponent.type, "");
			} 
			else 
			{
				printf("\nERRO: Divisao por zero detectada.\n");
			}
		} 
		else if (strcmp(instructionComponent.instructions[i].type, "load") == 0) 
		{
			while(memoryLoadStoreComponent.busy);

			memoryLoadStoreComponent.busy = true;
			strcpy(memoryLoadStoreComponent.type, "load");
			memoryLoadStoreComponent.recorder_00 = instructionComponent.instructions[i].recorder_00;
			memoryLoadStoreComponent.recorder_01 = instructionComponent.instructions[i].recorder_01;
			memoryLoadStoreComponent.recorder_02 = instructionComponent.instructions[i].recorder_02;
			memoryLoadStoreComponent.memory = &memoryComponent;

			load(&memoryLoadStoreComponent);

			memoryLoadStoreComponent.busy = false;
			strcpy(memoryLoadStoreComponent.type, "");
		} 
		else if (strcmp(instructionComponent.instructions[i].type, "store") == 0) 
		{
			while(memoryLoadStoreComponent.busy);

			memoryLoadStoreComponent.busy = true;
			strcpy(memoryLoadStoreComponent.type, "store");
			memoryLoadStoreComponent.recorder_00 = instructionComponent.instructions[i].recorder_00;
			memoryLoadStoreComponent.recorder_01 = instructionComponent.instructions[i].recorder_01;
			memoryLoadStoreComponent.recorder_02 = instructionComponent.instructions[i].recorder_02;
			memoryLoadStoreComponent.memory = &memoryComponent;

			store(&memoryLoadStoreComponent);

			memoryLoadStoreComponent.busy = false;
			strcpy(memoryLoadStoreComponent.type, "");
		} 
		else 
		{
			printf("\nERRO: Operacao nao reconhecida!\n");
		}

		if(instructionFalseDependency[0] != -1)
			desalocBuffer(&buffer, instructionComponent.instructions[i].recorder_01);
		if(instructionFalseDependency[1] != -1)
			desalocBuffer(&buffer, instructionComponent.instructions[i].recorder_02);

		instructionComponent.instructions[i].done = true;
	}

	printf("\n\n----------------------------- [Depois] ---------------------------------: \n");
	printf("\n\nBuffer: \n");
	bufferToString(&buffer);

	printf("\n\nRegistrador: \n");
	recorderFPToString(&recorderPFComponent);

	memoryComponentToString(&memoryComponent);

	return 0;
}
