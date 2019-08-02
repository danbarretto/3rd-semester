/**
 * Classe representa deck tradicional de 52 cartas
 * @author daniel
 */

public class Deck {
    private Cartas[] deck;

    /**
     * Inicializa o deck com 52 cartas, sendo 4 naipes diferentes com 13 números cada
     * @throws InterruptedException
     */
    public Deck() {
        deck = new Cartas[52];

        int k = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = 1; j <= 13; j++) {
                deck[k] = new Cartas();
                deck[k].setNumero(j);
                deck[k].setNipe(i);
                k++;
            }
        }
    }

    /**
     *
     * @return o array de cartas atual
     */
    public Cartas[] getDeck() {
        return deck;
    }

    /**
     *
     * @param deck o array de cartas escolhido
     */
    public void setDeck(Cartas[] deck) {
        this.deck = deck;
    }


    /**
     * Cria a string com a ascii art de todas as cartas alinhadas horizontalmente
     * @return
     */
    @Override
    public String toString() {
        //deck[0] =
        String s = "";
        for (int i = 0; i < deck.length; i++) {
            s += "+-----+    ";
        }
        s += "\n";
        for (int i = 0; i < deck.length; i++) {
            s += "|     |    ";
        }
        s += "\n";
        for (int i = 0; i < deck.length; i++) {
            if (deck[i].getNumero() != 10)
                s += "| " + deck[i].intToCard() + deck[i].intToNipe() + "  |    ";
            else
                s += "| " + 10 + deck[i].intToNipe() + " |    ";
        }
        s += "\n";
        for (int i = 0; i < deck.length; i++) {
            s += "|     |    ";
        }
        s += "\n";
        for (int i = 0; i < deck.length; i++) {
            s += "+-----+    ";
        }
        s += "\n";
        return s;
    }

}