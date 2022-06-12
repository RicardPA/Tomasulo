/*
	-----------------------------------
	BufferComponent.h 
	Author: Ricardo Portilho de Andrade 
	-----------------------------------
	Objetivo: Esse codigo representa um
	componente que armazena registradores
	quando houver uma dependencia falsa.
	-----------------------------------
	Bibliotecas necessarias:
	* Recorder.h
*/

/* - - - - - - Banco de Registradores - - - - - - */

typedef struct 
{
	bool IsUsed[LENGTH_BUFFER];
	Recorder recorderDestiny[LENGTH_BUFFER];
	Recorder *recorderOrigin[LENGTH_BUFFER];
} BufferComponent;

void createBuffer(BufferComponent *buffer) 
{
	for(int i = 0; i < LENGTH_BUFFER; i++) 
	{
		recorderConstructor_01(&buffer->recorderDestiny[i], 0, false, i);
	}
}

void bufferToString(BufferComponent *buffer) 
{
	printf("|--- Registradores ---\n");
	for(int i = 0; i < LENGTH_RECORDER; i++) 
	{
		printf("| ");
		recorderToString(&buffer->recorderDestiny[i]);
	}
	printf("|------------------------------\n");
}

void alocBuffer(BufferComponent *buffer, Instruction *instruction, Recorder *recorder) 
{
	bool booleanAlocBuffer = false;

	while (!booleanAlocBuffer) 
	{
		for(int i = 0; i < LENGTH_BUFFER && !booleanAlocBuffer; i++) 
		{
			if(buffer->IsUsed[i] == false) 
			{
				buffer->IsUsed[i] = true;

				buffer->recorderDestiny[i].value = recorder->value;
				buffer->recorderOrigin[i] = recorder;	
				booleanAlocBuffer = true;

				if(instruction->recorder_00->address == recorder->address)
					instruction->recorder_00 = &buffer->recorderDestiny[i];
				if(instruction->recorder_01->address == recorder->address)
					instruction->recorder_01 = &buffer->recorderDestiny[i];
				if(instruction->recorder_02->address == recorder->address)
					instruction->recorder_02 = &buffer->recorderDestiny[i];
			}
		}
	}
}

void desalocBuffer(BufferComponent *buffer, Recorder *recorder) 
{
	if(buffer->IsUsed[recorder->address] == true)
	{
		buffer->recorderOrigin[recorder->address]->value = buffer->recorderDestiny[recorder->address].value;
		buffer->IsUsed[recorder->address] = false;
	}
}