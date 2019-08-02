/**
 * Representa as 5 cartas do jogador, maneja a troca de cartas e o primeiro conjunto tirado
 * @author daniel
 */
public class Mao {
    private Cartas[] mao;
    private Deck d;

    /**
     * Inicia objeto da Classe Deck e todos objetos
     * do array de Cartas
     */
    public Mao() {
        d = new Deck();
        mao = new Cartas[5];
        for (int i = 0; i < 5; i++)
            mao[i] = new Cartas();
    }


    /**
     * Retira o primeiro conjunto de 5 cartas aleatórias e as marca como retiradas do deck
     */
    public void tirarMao() {

        Cartas deck[] = d.getDeck();
        Random rd = new Random();
        int i = 0;
        while (i < 5) {
            int index = rd.getIntRand(0, 52);
            if (!deck[index].getFoiTirada()) {
                mao[i] = deck[index];
                deck[index].setFoiTirada(true);
                i++;
            }
        }
    }

    /**
     * Retorna a mão atual
     * @return array atual de cartas
     */
    public Cartas[] getMao() { return mao; }

    /**
     * Troca cartas selecionadas por novas cartas aleatórias não retiradas anteriormente
     * @param quais string de quais cartas serão trocadas ex: "1 2 3"
     */
    public void trocar(String quais) {
        String[] cartas = quais.split(" "); //separa string de acordo com espaços
        Cartas deck[] = d.getDeck();

        int[] nums = new int[cartas.length];
        for (int i = 0; i < nums.length; i++)
            nums[i] = Integer.parseInt(cartas[i]) - 1; //converte para vetor de inteiros 0 based
        int i = 0;
        //seleciona novas cartas aleatórias que não foi retirada e troca de acordo com os indices passados na string
        while (i < nums.length) {
            Random rd = new Random();
            int index = rd.getIntRand(0, 52);
            if (!deck[index].getFoiTirada()) {
                mao[nums[i]] = deck[index];
                i++;
                deck[index].setFoiTirada(true);
            }

        }

    }

    /**
     * Retorna string com as 5 cartas atuais alinhadas horizontalmente
     * @return String s => ascii art de todas as cartas alinhadas
     */
    @Override
    public String toString() {
        //mao[0] =
        String s = "+-----+    +-----+    +-----+    +-----+    +-----+\n";
        s += "|     |    |     |    |     |    |     |    |     |\n";
        for (int i = 0; i < mao.length; i++) {
            if (mao[i].getNumero() != 9)
                s += "| " + mao[i].intToCard() + mao[i].intToNipe() + "  |    ";
            else
                s += "| " + 10 + mao[i].intToNipe() + " |    ";
        }
        s += "\n|     |    |     |    |     |    |     |    |     |\n";
        s += "+-----+    +-----+    +-----+    +-----+    +-----+\n";

        return s;
    }

}