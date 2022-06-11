#define LENGTH_RECORDER 5

/* - - - - - - Banco de Registradores - - - - - - */

typedef struct 
{
	Recorder recorders[LENGTH_RECORDER];
} RecorderPFComponent;

void createRecorderFP(RecorderPFComponent *recorderPFComponent) 
{
	for(int i = 0; i < LENGTH_RECORDER; i++) 
	{
		recorderConstructor_01(&recorderPFComponent->recorders[i], rand()%(1000*(i+rand()%100)), false, i);
	}
}

void recorderFPToString(RecorderPFComponent *recorderPFComponent) 
{
	printf("|--- Registradores ---\n");
	for(int i = 0; i < LENGTH_RECORDER; i++) 
	{
		printf("| ");
		recorderToString(&recorderPFComponent->recorders[i]);
	}
	printf("|------------------------------\n");
}