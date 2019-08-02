import java.io.IOException;

class Main {
    public static void main(String[] args) throws InterruptedException {

        Placar pl = new Placar();
        Mao m = new Mao();
        
        EntradaTeclado tlc = new EntradaTeclado();
        
        while(pl.getCreditos() > 0) {
        	
        	int aposta = 0;
        	String quaisTrocar = "";
        	
        	System.out.print("Digite o quanto quer apostar: ");
        	
        	while(true) {
        		try {
        			
        			aposta = tlc.leInt();
        			if(aposta <= pl.getCreditos())
        				break;
        			else
        				System.out.println("Você é pobre e não tem tantos creditos assim");
        		} 
        		catch(Exception e) {
        			System.out.println("Entrada invalido");
        		}
        	}
        	
        	pl.apostar(aposta);
        	
        	m.tirarMao();
        	System.out.println("Esta é sua mão atual\n" + m.toString() + '\n');
        	System.out.println("Digite as cartas que gostaria de trocar (1 a 5, separadas por espaço)");
        	System.out.println("Digite 0 se quiser ficar com essa mão");
        
        	while(true){
        		try {
					quaisTrocar = tlc.leString();
					break;
        		} catch (IOException e) {
        			System.out.println("Entrada invalida");
        		}
        	}
        	
        	String[] quais = quaisTrocar.split(" ");

            int[] nums = new int[quais.length];
            for (int i = 0; i < nums.length; i++)
                nums[i] = Integer.parseInt(quais[i]);
        	
        	if(nums[0] != 0) {
        		
        		m.trocar(quaisTrocar);
        		
        		System.out.println("Esta é sua mão atual\n" + m.toString() + '\n');
            	System.out.println("Digite as cartas que gostaria de trocar (1 a 5, separadas por espaço)");
            	System.out.println("Digite 0 se quiser ficar com essa mão");
            	
            	while(true){
            		try {
    					quaisTrocar = tlc.leString();
    					break;
            		} catch (IOException e) {
            			System.out.println("Entrada invalida");
            		}
            	}
            	
            	quais = quaisTrocar.split(" ");

                nums = new int[quais.length];
                for (int i = 0; i < nums.length; i++)
                    nums[i] = Integer.parseInt(quais[i]);
            	
            	if(nums[0] != 0)
            		m.trocar(quaisTrocar);
        		
        	}
        	
        	System.out.println("Esta é sua mão atual\n" + m.toString() + '\n');
        	
        	int creditosGanhos = pl.updateCreditos(m.getMao());
        	
        	System.out.println("\nVocê ganhou " + creditosGanhos + " créditos");
        	
        	System.out.println("Você tem " + pl.getCreditos() + " créditos");
        		
        
        }
    

    }
}