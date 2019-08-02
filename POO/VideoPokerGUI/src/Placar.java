
/**
 * Representa o placar
 * Controla quantos créditos um jogador tem, manejando apostas, ganhos e perdas
 * @author ferfa
 *
 */
public class Placar {

	private int creditos = 200;
	
	private int aposta = 0;
	
	private int[] numeros = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	private int[] nipes = { 0, 0, 0, 0 };
	
	/**
	 * 
	 * @return os créditos do jogador
	 */
	public int getCreditos() { return creditos; }
	/**
	 * 
	 * @return a aposta atual
	 */
	public int getAposta() { return aposta; }
	
	/**
	 * Retira do saldo do jogador o valor a ser apostado
	 * @param valor a ser apostado
	 */
	public void apostar(int aposta) { 
		
		if(aposta <= creditos) {
			this.aposta = aposta;
			creditos -= aposta;
		}
		else
			throw (new IllegalArgumentException());
	}
	
	/**
	 * Analisa uma mão de cartas, procura por combinações e atualiza os créditos do jogador
	 * de acordo com as combinações encontradas
	 * @param mao do jogador
	 * @return o valor de créditos ganhos. 0 se nenhuma combinação foi encontrada
	 */
	public int updateCreditos(Cartas[] mao) {
		
		int multiplicador = 0;

		insertionSortCartas(mao);						//ordena o vetor
		
		for(int i = 0; i < 13; i++)
			numeros[i] = 0;
		for(int i = 0; i < 4; i++)
			nipes[i] = 0;
		
		for(int i = 0; i < 5; i++) {					//conta a ocorrencia de cada numero e nipe
			numeros[mao[i].getNumero()-1]++;			//+
			nipes[mao[i].getNipe()]++;					//+
		}
		
		int numerosIguais = 0;
		int nipesIguais = 0;							//encontra qual o maior numero de nipes
		for(int i = 0; i < 13; i++) {					//e numeros iguais
			if(numeros[i] > numerosIguais)				//+
				numerosIguais = numeros[i];				//+
		}												//+
		for(int i = 0; i < 4; i++) {					//+
			if(nipes[i] > nipesIguais)					//+	
				nipesIguais = nipes[i];					//+
		}
		
		//CHECA POR "Royal Straight Flush",  "Straight Flush" ou "Straight"
		if(mao[1].getNumero() == mao[0].getNumero() + 1 && mao[2].getNumero() == mao[0].getNumero() + 2 
				&& mao[3].getNumero() == mao[0].getNumero() + 3	
				&& mao[4].getNumero() == mao[0].getNumero() + 4) {
			
			multiplicador = 5;
			
			if(nipesIguais == 5) {
				
				multiplicador = 100;
				
				if(mao[0].getNumero() == 9)
					multiplicador = 200;
			}
		}
		
		//CHECA POR "Flush"
		else if(nipesIguais == 5)
			multiplicador = 10;
		
		//CHECA POR "Quadra"
		else if(numerosIguais == 4)
			multiplicador = 50;
		
		//CHECA POR "Full Hand" ou "Trinca"
		else if(numerosIguais == 3) {
			multiplicador = 2;
			for(int i = 0; i < 13; i++)
				if(numeros[i] == 2)
					multiplicador = 20;
		}
		
		//CHECA POR "Dois Pares"
		else {
			
			boolean umPar = false;
			
			for(int i = 0; i < 13; i++) {
				if(numeros[i] == 2) {
					
					if(umPar == true) 
						
						multiplicador = 1;
					else 
						umPar = true;
				}
			}
		}
		
		creditos += aposta * multiplicador;			//atualiza os créditos do jogador
		
		return aposta * multiplicador;				//retorna a quantidade de créditos ganhos
													//naquela rodada
	}
	
	/**
	 * ordena uma mão de cartas de acordo com o valor numérico de cada carta
	 * @param a mão a ser ordenada
	 */
	private void insertionSortCartas(Cartas[] mao) {
		
		Cartas carta;
		
		for(int j = 0; j < 5; j++) {
			for(int i = 0; i < 5; i++) {
				
				if(i < 4) {
					if(mao[i].getNumero() > mao[i+1].getNumero()) {
						carta = mao[i];
						mao[i] = mao[i+1];
						mao[i+1] = carta;
					}
				}
			}
		}
		
	}
	
	
}
