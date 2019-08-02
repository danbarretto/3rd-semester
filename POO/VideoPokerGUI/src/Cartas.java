/**
 * Classe representa uma carta de baralho individual, com seu número e naipe.
 * @author daniel e fernando
 */

public class Cartas {

    private Random rd;

    private int numero = 0;

    private boolean foiTirada;

    private String[] tradNumeros = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    private String[] tradNipes = {"♦", "♠", "♥", "♣"};

    private int nipe = 0;
    //0 - ouro
    //1 - espadas
    //2 - copas
    //3 - paus

    /**
     * Cria carta com naipe e número randômicos
     */
    public Cartas(){
        rd = new Random();
        numero = rd.getIntRand(1, 14);
        nipe = rd.getIntRand(0, 4);
        foiTirada = false;
    }

    /**
     *
     * @return int numero -> numero da classe atual
     */
    public int getNumero() {
        return numero;
    }

    /**
     *
     * @return int naipe -> naipe da carta atual
     */
    public int getNipe() {
        return nipe;
    }

    /**
     * @param nipe o nipe a ser escolhido
     */
    public void setNipe(int nipe) {
        this.nipe = nipe;
    }

    /**
     * @param numero o numero a ser escolhido
     */
    public void setNumero(int numero) {
        this.numero = numero;
    }

    /**
     *
     * @return o naipe da carta como caracter ascii do naipe
     */
    public String intToNipe() {
        return tradNipes[nipe];
    }

    /**
     *
     * @return o naipe da carta atual como string
     */
    public String intToCard() {
        return tradNumeros[numero - 1];
    }

    /**
     *
     * @return boolean foiTirada -> estado de permanência da carta em um Deck
     */
    public boolean getFoiTirada() {
        return foiTirada;
    }

    /**
     *
     * @param foiTirada o estado da carta a ser escolhido
     */
    public void setFoiTirada(boolean foiTirada) {
        this.foiTirada = foiTirada;
    }


    /**
     * Cria string com a ascii art da carta
     * @return String s -> string que contém a ascii art
     */
    @Override
    public String toString() {

        String carta = "";

        if (numero != 9) {
            carta = "+-----+    \r\n" +
                    "|     |    \r\n" +
                    "| " + tradNumeros[numero - 1] + tradNipes[nipe] + "  |\t\n" +
                    "|     |    \r\n" +
                    "+-----+ " + numero;
        } else {
            carta = "+-----+    \r\n" +
                    "|     |    \r\n" +
                    "| " + 10 + tradNipes[nipe] + " |\t\n" +
                    "|     |    \r\n" +
                    "+-----+ " + numero;


        }

        return carta;
    }
}
