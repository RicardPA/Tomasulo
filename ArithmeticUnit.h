/* - - - - - - Unidade de Aritmetica - - - - - - */
typedef struct 
{
	bool busy;
	char type[15];
	Recorder *recorder_00; // unidade de destino
	Recorder *recorder_01; // unidade variavel 
	Recorder *recorder_02; // unidade variavel
} ArithmeticUnit;

void arithmeticUnitConstructor_01(ArithmeticUnit *auxArithmetic, bool busy, Recorder *recorder_00, Recorder *recorder_01, Recorder *recorder_02) 
{
	auxArithmetic->busy = false;
	auxArithmetic->recorder_00 = recorder_00;
	auxArithmetic->recorder_01 = recorder_01;
	auxArithmetic->recorder_02 = recorder_02;
}

void arithmeticUnitToString(ArithmeticUnit *arithmetic) 
{
	printf("\n|--- Dados da Unidade Aritmetica (%s) ---\n", arithmetic->type);
	printf("| Unidade de destino (Valor: %d | Busy: %d | Address: %d) \n", arithmetic->recorder_00->value, arithmetic->recorder_00->busy, arithmetic->recorder_00->address);
	printf("| Unidade variavel (Valor: %d | Busy: %d | Address: %d) \n", arithmetic->recorder_01->value, arithmetic->recorder_01->busy, arithmetic->recorder_01->address);
	printf("| Unidade variavel (Valor: %d | Busy: %d | Address: %d) \n", arithmetic->recorder_02->value, arithmetic->recorder_02->busy, arithmetic->recorder_02->address);
}

void sum(ArithmeticUnit *arithmetic) 
{
	while(arithmetic->recorder_00->busy || arithmetic->recorder_01->busy || arithmetic->recorder_02->busy);
	
	// Marcar como sendo usado
	arithmetic->recorder_00->busy = true;
	arithmetic->recorder_01->busy = true;
	arithmetic->recorder_02->busy = true;

	// Fazer operacao
	arithmetic->recorder_00->value = arithmetic->recorder_01->value + arithmetic->recorder_02->value;

	// Marcar como nao sendo usado
	arithmetic->recorder_00->busy = false;
	arithmetic->recorder_01->busy = false;
	arithmetic->recorder_02->busy = false;
}

void subtraction(ArithmeticUnit *arithmetic)
{
	while(arithmetic->recorder_00->busy || arithmetic->recorder_01->busy || arithmetic->recorder_02->busy);
	
	// Marcar como sendo usado
	arithmetic->recorder_00->busy = true;
	arithmetic->recorder_01->busy = true;
	arithmetic->recorder_02->busy = true;

	// Fazer operacao
	arithmetic->recorder_00->value = arithmetic->recorder_01->value - arithmetic->recorder_02->value;

	// Marcar como nao sendo usado
	arithmetic->recorder_00->busy = false;
	arithmetic->recorder_01->busy = false;
	arithmetic->recorder_02->busy = false;
}

void multiplication(ArithmeticUnit *arithmetic) 
{
	while(arithmetic->recorder_00->busy || arithmetic->recorder_01->busy || arithmetic->recorder_02->busy);

	// Marcar como sendo usado
	arithmetic->recorder_00->busy = true;
	arithmetic->recorder_01->busy = true;
	arithmetic->recorder_02->busy = true;

	// Fazer operacao
	arithmetic->recorder_00->value = arithmetic->recorder_01->value * arithmetic->recorder_02->value;

	// Marcar como nao sendo usado
	arithmetic->recorder_00->busy = false;
	arithmetic->recorder_01->busy = false;
	arithmetic->recorder_02->busy = false;
}

void division(ArithmeticUnit *arithmetic) 
{
	while(arithmetic->recorder_00->busy || arithmetic->recorder_01->busy || arithmetic->recorder_02->busy);

	// Marcar como sendo usado
	arithmetic->recorder_00->busy = true;
	arithmetic->recorder_01->busy = true;
	arithmetic->recorder_02->busy = true;

	// Fazer operacao
	arithmetic->recorder_00->value = arithmetic->recorder_01->value / arithmetic->recorder_02->value;

	// Marcar como nao sendo usado
	arithmetic->recorder_00->busy = false;
	arithmetic->recorder_01->busy = false;
	arithmetic->recorder_02->busy = false;
}