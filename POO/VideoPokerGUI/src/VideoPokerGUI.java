import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.text.NumberFormat;

public class VideoPokerGUI {

    private JPanel panel1;
    private JButton carta1;
    private JButton carta5;
    private JButton carta4;
    private JButton carta3;
    private JButton carta2;
    private JButton trocarCartasButton;
    private JTextPane valoresGanhosPorApostaTextPane;
    private JButton apostarButton;
    private JButton encerrarButton;
    private JTextField apostaTxt;
    private JLabel placarLbl;
    private JLabel apostaLbl;
    private Mao m;
    private JButton[] btnCartas = {carta1, carta2, carta3, carta4, carta5};
    private boolean[] cardIsSelected = {true, true, true, true, true};
    private Placar pl = new Placar();
    private int vezesTrocadas = 0, aposta=0;
    private Cartas[] cartas;
    private boolean hasBet = false;

    /**
     * Define ícone do botão dado de acordo com a carta dada
     * @param button botão a ser alterado
     * @param carta Carta dada
     */
    private void setCardIcon(JButton button, Cartas carta) {
        ImageIcon icon = new ImageIcon("imgs/" + carta.intToCard() + carta.intToNipe() + ".png");
        Image scalled = icon.getImage().getScaledInstance(276, 400, Image.SCALE_SMOOTH);
        icon = new ImageIcon(scalled);
        button.setIcon(icon);
    }

    /**
     * Evento de click dos botões de cartas
     * Troca ícone da carta para a carta de mesma posição ou para a carta virada
     */
    private ActionListener selecionarCartas = e -> {
        if(aposta>0){
            ImageIcon back = new ImageIcon("imgs/back.png");
            Image backScalled = back.getImage().getScaledInstance(276, 400, Image.SCALE_SMOOTH);
            back = new ImageIcon(backScalled);
            JButton btnClicked = (JButton) e.getSource();
            if (!cardIsSelected[Integer.parseInt(btnClicked.getName()) - 1]) {
                btnClicked.setIcon(back);
                cardIsSelected[Integer.parseInt(btnClicked.getName()) - 1] = true;
            } else {
                setCardIcon(btnClicked, cartas[Integer.parseInt(btnClicked.getName()) - 1]);
                cardIsSelected[Integer.parseInt(btnClicked.getName()) - 1] = false;
            }
        }else{
            JOptionPane.showMessageDialog(panel1, "Você deve realizar uma aposta antes.");
        }
    };

    /**
     * Evento de click botão apostar
     * Registra a aposta caso valores sejam válidos e esconde o JTextField e JButton de aposta até terminar o turo
     */
    private ActionListener apostar = e -> {
        if(!apostaTxt.getText().matches("[0-9]+")){
            JOptionPane.showMessageDialog(panel1, "Valor de aposta inválido!");
            apostaTxt.setText("");
            return;
        }
        aposta = Integer.parseInt(apostaTxt.getText());
        if (aposta <= 0) {
            JOptionPane.showMessageDialog(panel1, "Sua aposta deve ser maior que 0!");
        } else {
            if (aposta <= pl.getCreditos()) {
                if (aposta < 10) {
                    JOptionPane.showMessageDialog(panel1, "Aposta mínima de 10 créditos");
                    return;
                }
                apostaLbl.setText("Sua aposta: "+aposta);
                apostaTxt.setText("0");
                changeIcons();
                apostaTxt.setEnabled(false);
                apostaTxt.setVisible(false);
                apostarButton.setEnabled(false);
                apostarButton.setVisible(false);

            } else {
                JOptionPane.showMessageDialog(panel1, "Você não tem créditos suficientes para realizar essa aposta.");
            }
        }
    };

    /**
     * Evento de click do botão de encerrar turno
     * Realiza a aposta e retorna o resultado do placar para o jogador, caso jogador perca, uma janela de Continua aparecerá
     */
    private ActionListener encerrarTurno = e->{

        pl.apostar(aposta);
        int creditosGanhos = pl.updateCreditos(m.getMao());
        if (creditosGanhos > 0)
            JOptionPane.showMessageDialog(panel1, "Parabéns! Você ganhou " + creditosGanhos + " créditos!");
        else
            JOptionPane.showMessageDialog(panel1, "Você perdeu " + aposta + " créditos.");
        placarLbl.setText("Seus créditos: " + pl.getCreditos());
        if (pl.getCreditos() == 0) {
            Object[] options = {"Sim", "Não"};
            int opcao = JOptionPane.showOptionDialog(null, "Você perdeu! Deseja continuar?", "GAME OVER", JOptionPane.DEFAULT_OPTION, JOptionPane.WARNING_MESSAGE, null, options, options[0]);
            System.out.println(opcao);
            if (opcao == 0) {
                restartGame();
            } else {
                System.exit(0);
            }
        }
        m.tirarMao();
        flipCardsBack();
        vezesTrocadas = 0;
        aposta=0;
        apostaLbl.setText("Sua aposta: 0");
        apostaTxt.setText("0");
        apostaTxt.setEnabled(true);
        apostaTxt.setVisible(true);
        apostarButton.setEnabled(true);
        apostarButton.setVisible(true);
    };

    /**
     * Evento de click do botão de trocar cartas
     * Troca todas as cartas selecionadas por novas cartas não retiradas do baralho
     */
    private ActionListener trocarCartas = e -> {
        String quais = "";
        for (int i = 0; i < 5; i++) {
            if (cardIsSelected[i])
                quais += i + 1 + " ";
        }
        if(aposta == 0 && vezesTrocadas < 2){
            JOptionPane.showMessageDialog(panel1, "Você deve realizar uma aposta antes");
            return;
        }
        if (vezesTrocadas < 2) {
            if (!quais.equals("")) {
                m.trocar(quais);
                changeIcons();
                vezesTrocadas++;
                hasBet=false;
            } else {
                JOptionPane.showMessageDialog(panel1, "Você precisa selecionar pelo menos 1 carta para trocar!");
            }
        } else {
            JOptionPane.showMessageDialog(panel1, "Você não pode mais trocar sua mão!");
            changeIcons();
        }
    };

    /**
     * Reinicia o placar e a mão do jogador caso o jogador perca
     */
    public void restartGame() {
        pl = new Placar();
        m = new Mao();
        updateCards();
        placarLbl.setText(String.valueOf(pl.getCreditos()));
    }

    /**
     * Construtor
     * Configura o jogo e adiciona os eventos aos respectivos componentes
     */
    public VideoPokerGUI() {
        m = new Mao();
        m.tirarMao();
        cartas = m.getMao();
        for (int i = 0; i < 5; i++) {
            btnCartas[i].setName(String.valueOf(i + 1));


        }
        flipCardsBack();
        placarLbl.setText("Seus créditos: " + pl.getCreditos());
        carta1.addActionListener(selecionarCartas);
        carta5.addActionListener(selecionarCartas);
        carta4.addActionListener(selecionarCartas);
        carta3.addActionListener(selecionarCartas);
        carta2.addActionListener(selecionarCartas);

        NumberFormat nf = NumberFormat.getIntegerInstance();
        trocarCartasButton.addActionListener(trocarCartas);
        apostarButton.addActionListener(apostar);

        encerrarButton.addActionListener(encerrarTurno);
    }

    /**
     * Troca o ícone de todas as cartas que estão selecionadas
     */
    private void changeIcons() {
        for (int i = 0; i < 5; i++) {
            if (cardIsSelected[i]) {
                setCardIcon(btnCartas[i], m.getMao()[i]);
                cardIsSelected[i] = false;
            }
        }
    }

    /**
     * Troca o ícone de todas as cartas para uma carta virada pra baixo
     */
    private void flipCardsBack(){
        for(int i=0;i<5;i++){
            ImageIcon icon = new ImageIcon("imgs/back.png");
            Image scalled = icon.getImage().getScaledInstance(276, 400, Image.SCALE_SMOOTH);
            icon = new ImageIcon(scalled);
            btnCartas[i].setIcon(icon);
            cardIsSelected[i] = true;
        }
    }

    /**
     * Atualiza o ícone de todas as cartas de acordo com a mão atual
     */
    private void updateCards() {
        for (int i = 0; i < 5; i++)
            setCardIcon(btnCartas[i], m.getMao()[i]);
    }

    public static void main(String[] args) {
        VideoPokerGUI vg = new VideoPokerGUI();
        JFrame frame = new JFrame("Video Poker");
        frame.setExtendedState(JFrame.MAXIMIZED_BOTH);
        frame.setContentPane(vg.panel1);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.pack();
        frame.setVisible(true);


    }


}
