public class PoupancaSimples extends ContaPoupanca implements Comparable<ContaBancaria>{
    public PoupancaSimples(String n, int dia) {
        super(n, dia);
    }

    @Override
    public void atualiza(double taxa){
        setSaldo(getSaldo() * (1.0+ taxa));
    }

    @Override
    public int compareTo(ContaBancaria obj) {
        if(obj instanceof PoupancaOuro){
            return -1;
        }else if(obj instanceof PoupancaSimples){
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
