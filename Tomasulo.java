public class Tomasulo
{
    public static void main(String[] args) 
    {
        RegistradorFP[] registradoresFP = new RegistradorFP[6];

        registradoresEndereco[0] = RegistradorFP f0; 
        registradoresEndereco[1] = RegistradorFP f1; 
        registradoresEndereco[2] = RegistradorFP f2; 
        registradoresEndereco[3] = RegistradorFP f3; 
        registradoresEndereco[4] = RegistradorFP f4; 
        registradoresEndereco[5] = RegistradorFP f5; 

        RegistradorEndereco[] registradoresEndereco = new RegistradorEndereco[4];

        RegistradorEndereco r0 = new RegistradorEndereco(42);
        RegistradorEndereco r1 = new RegistradorEndereco(45);
        RegistradorEndereco r2 = new RegistradorEndereco(27);
        RegistradorEndereco r3 = new RegistradorEndereco(56);

        registradoresEndereco[0] = r0;
        registradoresEndereco[1] = r1;
        registradoresEndereco[2] = r2;
        registradoresEndereco[3] = r3;

        Instrucao[] memoriaInstrucoes = new Instrucao[6];

        Instrucao a = new Instrucao("LW", registradoresFP[0], 34, registradoresEndereco[0]);
        Instrucao b = new Instrucao("LW", registradoresFP[1], 45, registradoresEndereco[1]);
        Instrucao c = new Instrucao("MUL", registradoresFP[2], registradoresFP[1], registradoresFP[3]);
        Instrucao d = new Instrucao("SUB", registradoresFP[4], registradoresFP[0], registradoresFP[2]);
        Instrucao e = new Instrucao("DIV", registradoresFP[5], registradoresFP[2], registradoresFP[0]);
        Instrucao f = new Instrucao("ADD", registradoresFP[1], registradoresFP[4],registradoresFP[1]);

        memoriaInstrucoes[0] = a;
        memoriaInstrucoes[1] = b;
        memoriaInstrucoes[2] = c;
        memoriaInstrucoes[3] = d;
        memoriaInstrucoes[4] = e;
        memoriaInstrucoes[5] = f;
    }
}

class Instrucao             
{
    int valor;
    String tipo;
    RegistradorFP fp;
    RegistradorEndereco endereco;

    public Instrucao(String tipo, RegistradorFP fp, int valor, RegistradorEndereco endereco)
    {}
    
    public Instrucao(String tipo, RegistradorFP destino, RegistradorFP registrador1, RegistradorFP resgistrador2)
    {}
}

class RegistradorFP
{
    int valor;
    boolean busy;
    //EstacaoTrabalho ondePegarValor;
    int endereco;//utilizar???

    public RegistradorFP()
    {}
}

class UnidadeMem
{
    RegistradorFP destino, R2, R3;

    public void load();
    public void store();
}

class UnidadeAritm
{
    RegistradorFP destino, R2, R3;

    public void soma();
    public void subtrai();
    public void multiplica();
    public void divide();
}

