public class PoupancaOuro extends ContaPoupanca implements Comparable<ContaBancaria>{


    public PoupancaOuro(String n, int dia) {
        super(n, dia);
    }

    @Override
    public void atualiza(double taxa){
        setSaldo(getSaldo() * (1.5+ taxa));
    }

    @Override
    public int compareTo(ContaBancaria obj) {
        if(obj instanceof PoupancaSimples){
            return 1;
        }else if(obj instanceof PoupancaOuro){
            if(getSaldo() < obj.getSaldo()){
                return -1;
            }else if(getSaldo()==obj.getSaldo()){
                return 0;
            }else{
                return 1;
            }
        }else{
            return 1;
        }
    }
}
