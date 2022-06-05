/* - - - - - - Registrador - - - - - - */
typedef struct {
	int value;
	bool busy;
	int address;
} RecorderCell;

/* - - - - - - Memoria - - - - - - */
typedef struct {
	int value;
	int address;
} MemoryCell;

/* - - - - - - Instrucao - - - - - - */
typedef struct {
	int value;
	int address;
	char type[15];
	RecorderCell recorder;
} Instruction;

/* - - - - - - Unidade de Memoria - - - - - - */
typedef struct {
	RecorderCell recorder_00; // unidade de destino
	RecorderCell recorder_01; // unidade variavel 
	RecorderCell recorder_02; // unidade variavel
} MemoryUnit;

void load(struct MemoryUnit *memory) {
	// Marcar como sendo usado
	arithmetic->recorder_00->busy = true;
	arithmetic->recorder_01->busy = true;

	// Fazer operacao
	arithmetic->recorder_00->value = arithmetic->recorder_01->value + arithmetic->recorder_02->value;

	// Marcar como nao sendo usado
	arithmetic->recorder_00->busy = false;
	arithmetic->recorder_01->busy = false;
}

void store(struct MemoryUnit *memory) {
	// Marcar como sendo usado
	arithmetic->recorder_00->busy = true;
	arithmetic->recorder_01->busy = true;

	// Fazer operacao
	arithmetic->recorder_00->value = arithmetic->recorder_01->value + arithmetic->recorder_02->value;

	// Marcar como nao sendo usado
	arithmetic->recorder_00->busy = false;
	arithmetic->recorder_01->busy = false;
}

/* - - - - - - Unidade de Aritmetica - - - - - - */
typedef struct {
	RecorderCell recorder_00; // unidade de destino
	RecorderCell recorder_01; // unidade variavel 
	RecorderCell recorder_02; // unidade variavel
} MemoryArithmetic;

void sum(struct MemoryArithmetic *arithmetic) {
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

void subtraction(struct MemoryArithmetic *arithmetic) {
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

void multiplication(struct MemoryArithmetic *arithmetic) {
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

void division(struct MemoryArithmetic *arithmetic) {
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

int main(void) {

}