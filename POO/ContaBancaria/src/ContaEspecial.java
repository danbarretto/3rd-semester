
public class ContaEspecial extends ContaBancaria implements Comparable<ContaBancaria>{
private double limite;

	public ContaEspecial(String n, double l) {
		super(n);
		limite = l;
	}
	
	@Override
	public void saca(double qto) {
		double s = getSaldo();
		if ( qto > s + limite )
			throw new IllegalArgumentException("Limite excedido para esse saque");
		setSaldo( s - qto );
	}
	@Override
	public void atualiza(double taxa){
		return;
	}

	@Override
	public int compareTo(ContaBancaria obj) {
		if(obj instanceof ContaEspecial){
			if(getSaldo()<obj.getSaldo()){
				return -1;
			}else if(getSaldo()==obj.getSaldo()){
				return 0;
			}else{
				return 1;
			}
		}else{
			return -1;
		}

	}
}
