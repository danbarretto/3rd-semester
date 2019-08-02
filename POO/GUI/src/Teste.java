import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Teste {
    private JPanel MainPanel;
    private JPasswordField senhaTxt;
    private JTextField nomeTxt;
    private JButton okBtn;
    private JButton limpaButton;

    public Teste() {
        okBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JOptionPane.showMessageDialog(null,"Nome: "+nomeTxt.getText()+"\nSenha: "+senhaTxt.getText());
            }
        });
        limpaButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                nomeTxt.setText("");
                senhaTxt.setText("");
            }
        });
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("Teste");
        frame.setContentPane(new Teste().MainPanel);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.pack();
        frame.setVisible(true);
    }
}
