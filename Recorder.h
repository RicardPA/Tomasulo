/*
	-----------------------------------
	Recorder.h 
	Author: Ricardo Portilho de Andrade 
	-----------------------------------
	Objetivo: Esse codigo representa as 
	informacoes necessarias para criar 
	unidades de retencao de dados.
*/

/* - - - - - - Registrador - - - - - - */
typedef struct recorder
{
	int value;
	bool busy;
	int address;
} Recorder;

void recorderConstructor_01(Recorder *auxRecorder, int value, bool busy, int address) 
{
	auxRecorder->value = value;
	auxRecorder->busy = busy;
	auxRecorder->address = address;
}

void recorderToString(Recorder *auxRecorder) 
{
	printf("|--- Registrador: (");
	printf("Valor: %d\t| ", auxRecorder->value);
	printf("Usado: %d\t| ",auxRecorder->busy);
	printf("Endereco: %d) \n", auxRecorder->address);	
}