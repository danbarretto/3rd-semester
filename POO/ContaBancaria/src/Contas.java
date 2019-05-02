import java.lang.reflect.Array;
import java.util.Arrays;

public class Contas {

    private ContaBancaria contas[] = new ContaBancaria[100];
    private int nContas = 0;

    public void sortContas(){
        printSaldos();
        Arrays.sort(contas);
    }

    public static void main(String[] args) throws Exception {
        int op = 0;
        Contas ct = new Contas();

        while (op != 8) {
            op = ct.leOpcao();
            switch (op) {
                case 1:
                    System.out.println("Nome do correntista: ");
                    String s = EntradaTeclado.leString();
                    System.out.println("Dia de vencimento: ");
                    int dia = EntradaTeclado.leInt();
                    PoupancaOuro po = new PoupancaOuro(s, dia);
                    ct.add(po);
                    System.out.println("Número da conta: " + po.getNumConta());
                    System.out.println("************ Conta criada.**************");
                    break;
                case 2:
                    System.out.println("Nome do correntista: ");
                    s = EntradaTeclado.leString();
                    System.out.println("Dia de vencimento: ");
                    dia = EntradaTeclado.leInt();
                    PoupancaSimples ps = new PoupancaSimples(s, dia);
                    ct.add(ps);
                    System.out.println("Número da conta: " + ps.getNumConta());
                    System.out.println("************ Conta criada.**************");
                    break;
                case 3:
                    System.out.println("Nome do correntista: ");
                    s = EntradaTeclado.leString();
                    System.out.println("Limite de saque: ");
                    double limite = EntradaTeclado.leDouble();
                    ContaEspecial ce = new ContaEspecial(s, limite);
                    ct.add(ce);
                    System.out.println("Número da conta: " + ce.getNumConta());
                    System.out.println("************ Conta criada.**************");
                    break;
                case 4:
                    System.out.println("Numero da conta: ");
                    int conta = EntradaTeclado.leInt();
                    System.out.println("Valor a sacar: ");
                    double valor = EntradaTeclado.leDouble();
                    ContaBancaria cb = ct.procura(conta);
                    if (cb == null) {
                        System.out.println("************* Conta não existe **************");
                        break;
                    }
                    try {
                        cb.saca(valor);
                        System.out.println("****************** Saque realizado ***********");
                    } catch (Exception e) {
                        System.out.println("****************** Saque não realizado ***********");
                        System.out.println(e.getMessage());
                    }
                    break;
                case 5:
                    System.out.println("Numero da conta: ");
                    conta = EntradaTeclado.leInt();
                    System.out.println("Valor a depositar: ");
                    valor = EntradaTeclado.leDouble();
                    cb = ct.procura(conta);
                    if (cb == null) {
                        System.out.println("************* Conta não existe **************");
                        break;
                    }
                    cb.deposita(valor);
                    System.out.println("****************** Depósito realizado ***********");
                    break;
                case 7:
                    ct.printSaldos();
                    break;
                case 6:
                    System.out.println("Qual o valor da taxa? ");
                    double tx = EntradaTeclado.leDouble();
                    ct.atualizaPoupança(tx);
                    System.out.println("Saldos atualizados");
                    break;

                case 8:
                    ct.sortContas();
                    break;
                case 9:
                    System.out.println("Terminando o programa....");
                    return;
            }
            System.out.println("Digite ENTER para continuar");
            EntradaTeclado.leString();
            System.out.println("\n\n");
        }

    }

    private static int leOpcao() {
        System.out.println("1) Criar poupança ouro\n2) Criar poupança simples\n3) Criar conta especial\n4) Realizar saque\n5) Realizar deposito\n"
                + "6) Atualizar poupanças\n7) Mostrar saldos\n8) Comparar contas\n9) Sair");
        int k = -1;
        while (true) {
            System.out.println("Digite a opção desejada ===> ");
            try {
                k = EntradaTeclado.leInt();
                if (k > 0 && k <= 9)
                    return k;
            } catch (Exception e) {
                ;
            }
        }
    }

    private void add(ContaBancaria cb) {
        contas[nContas++] = cb;
    }

    private void printSaldos() {
        for (ContaBancaria ctb : contas) {
            if (ctb == null) break;
            System.out.println("Numero da conta:" + ctb.getNumConta());
            System.out.println("Titular: " + ctb.getNomeCliente());
            System.out.println("Saldo: " + ctb.getSaldo());
            System.out.println();
        }

    }

    private void atualizaPoupança(double tx) {
        for (ContaBancaria ctb : contas) {
            if (ctb == null) break;

            if (ctb instanceof ContaPoupanca) {
                ContaPoupanca cp = (ContaPoupanca) ctb;
                cp.atualiza(tx);
            }
        }
    }

    private ContaBancaria procura(int conta) {
        for (ContaBancaria ctb : contas) {
            if (ctb == null) break;

            if (conta == ctb.getNumConta())
                return ctb;
        }
        return null;
    }

}
