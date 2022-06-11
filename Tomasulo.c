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

// Matriz necessaria para tratar dependencias
typedef struct 
{
	int col[LENGTH_INSTRUCTIONS];
} RowMatrixDepedencyRecorder;

typedef struct 
{
	RowMatrixDepedencyRecorder row[LENGTH_RECORDER];
} MatrixDepedencyRecorder;

/* Bibliotecas do Projeto */
// Unidedes de componentes
#include "Memory.h"
#include "Recorder.h"
#include "Instruction.h"
// Componentes
#include "RecorderPFComponent.h"
#include "InstructionComponent.h"
#include "MemoryComponent.h"
// Unidades de operacao
#include "MemoryUnit.h"
#include "ArithmeticUnit.h"

#define NUM_THREADS 2

int main(void) 
{
	// Matriz de dependencia
	MatrixDepedencyRecorder matrixDepedencyRecorder;

	// Componentes
	InstructionComponent instructionComponent;
	RecorderPFComponent recorderPFComponent;
	MemoryComponent memoryComponent;

	// Unidades de operacao
	ArithmeticUnit arithmeticSubSumComponent, arithmeticMulDivComponent;
	MemoryUnit memoryLoadStoreComponent;

	// Inicializar unidades de operacoes
	arithmeticSubSumComponent.busy = false;
	arithmeticMulDivComponent.busy = false;
	memoryLoadStoreComponent.busy = false;

	// Inicializar componentes
	createMemoryComponent(&memoryComponent);
	createRecorderFP(&recorderPFComponent);
	createInstructions(&instructionComponent, &recorderPFComponent, &matrixDepedencyRecorder);

	instructionComponentToString(&instructionComponent);
	recorderFPToString(&recorderPFComponent);
	
	#pragma omp parallel for
	for(int i = 0; i < LENGTH_INSTRUCTIONS; i++) 
	{
		int dependency[2];

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
	}

	recorderFPToString(&recorderPFComponent);
	
	return 0;
}