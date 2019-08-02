/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package view;

import java.util.ArrayList;
import javax.swing.JOptionPane;

/**
 *
 * @author lucas
 */
public class EmpresaFrame extends javax.swing.JFrame {

    /**
     * Creates new form Empresa
     */
    public EmpresaFrame() {
        initComponents();
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        tituloLabel = new javax.swing.JLabel();
        info1Label = new javax.swing.JLabel();
        info2Label = new javax.swing.JLabel();
        info3Label = new javax.swing.JLabel();
        info4Label = new javax.swing.JLabel();
        info5Label = new javax.swing.JLabel();
        info6Label = new javax.swing.JLabel();
        info8Label = new javax.swing.JLabel();
        info7Label = new javax.swing.JLabel();
        descricaoLabel = new javax.swing.JLabel();
        descricaoScrollPane = new javax.swing.JScrollPane();
        descricaoTextArea = new javax.swing.JTextArea();
        servicosLabel = new javax.swing.JLabel();
        ordenacaoLabel = new javax.swing.JLabel();
        ordenacaoComboBox = new javax.swing.JComboBox<>();
        servicosScrollPane = new javax.swing.JScrollPane();
        servicosJList = new javax.swing.JList<>();
        favoritoToggleButton = new javax.swing.JToggleButton();
        contatarButton = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setBounds(new java.awt.Rectangle(0, 0, 0, 0));
        setSize(new java.awt.Dimension(800, 600));

        tituloLabel.setFont(new java.awt.Font("Cantarell", 1, 36)); // NOI18N
        tituloLabel.setText("Empresa 1");

        info1Label.setFont(new java.awt.Font("Cantarell", 0, 18)); // NOI18N
        info1Label.setText("Área de atuação: Design");

        info2Label.setFont(new java.awt.Font("Cantarell", 0, 18)); // NOI18N
        info2Label.setText("Serviços disponíveis: 8");

        info3Label.setFont(new java.awt.Font("Cantarell", 0, 18)); // NOI18N
        info3Label.setText("Informação 3: ???");

        info4Label.setFont(new java.awt.Font("Cantarell", 0, 18)); // NOI18N
        info4Label.setText("Informação 4: ???");

        info5Label.setFont(new java.awt.Font("Cantarell", 0, 18)); // NOI18N
        info5Label.setText("Informação 5: ???");

        info6Label.setFont(new java.awt.Font("Cantarell", 0, 18)); // NOI18N
        info6Label.setText("Informação 6: ???");

        info8Label.setFont(new java.awt.Font("Cantarell", 0, 18)); // NOI18N
        info8Label.setText("Informação 8: ???");

        info7Label.setFont(new java.awt.Font("Cantarell", 0, 18)); // NOI18N
        info7Label.setText("Informação 7: ???");

        descricaoLabel.setText("Descrição:");

        descricaoTextArea.setEditable(false);
        descricaoTextArea.setColumns(20);
        descricaoTextArea.setRows(3);
        descricaoScrollPane.setViewportView(descricaoTextArea);

        servicosLabel.setText("Serviços disponíveis:");

        ordenacaoLabel.setText("Ordenar por");

        ordenacaoComboBox.setFont(new java.awt.Font("Cantarell", 0, 10)); // NOI18N
        ordenacaoComboBox.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "Item 1", "Item 2", "Item 3", "Item 4" }));

        servicosJList.setModel(new javax.swing.AbstractListModel<String>() {
            String[] strings = { "Serviço 1", "Serviço 2", "Serviço 3", "Serviço 4", "Serviço 5", "Serviço 6", "Serviço 7", "Serviço 8" };
            public int getSize() { return strings.length; }
            public String getElementAt(int i) { return strings[i]; }
        });
        servicosJList.setSelectionMode(javax.swing.ListSelectionModel.SINGLE_SELECTION);
        servicosJList.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                servicosJListMouseClicked(evt);
            }
        });
        servicosScrollPane.setViewportView(servicosJList);

        favoritoToggleButton.setText("Adicionar aos favoritos");

        contatarButton.setText("Contatar");

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(descricaoScrollPane, javax.swing.GroupLayout.Alignment.TRAILING)
                            .addComponent(tituloLabel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addGroup(layout.createSequentialGroup()
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(info1Label, javax.swing.GroupLayout.DEFAULT_SIZE, 409, Short.MAX_VALUE)
                                    .addComponent(info2Label, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                    .addComponent(info3Label, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                    .addComponent(info4Label, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(info5Label, javax.swing.GroupLayout.DEFAULT_SIZE, 359, Short.MAX_VALUE)
                                    .addComponent(info6Label, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                    .addComponent(info7Label, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                    .addComponent(info8Label, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)))
                            .addGroup(layout.createSequentialGroup()
                                .addComponent(servicosLabel)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                .addComponent(ordenacaoLabel)
                                .addGap(3, 3, 3)
                                .addComponent(ordenacaoComboBox, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(9, 9, 9)))
                        .addGap(14, 14, 14))
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                                .addGap(0, 0, Short.MAX_VALUE)
                                .addComponent(favoritoToggleButton)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(contatarButton))
                            .addGroup(layout.createSequentialGroup()
                                .addComponent(descricaoLabel)
                                .addGap(0, 0, Short.MAX_VALUE))
                            .addComponent(servicosScrollPane, javax.swing.GroupLayout.Alignment.TRAILING))
                        .addContainerGap())))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(tituloLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 40, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(18, 18, 18)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(info1Label)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(info2Label)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(info3Label)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(info4Label))
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(info5Label)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(info6Label)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(info7Label)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(info8Label)))
                .addGap(18, 18, 18)
                .addComponent(descricaoLabel)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(descricaoScrollPane, javax.swing.GroupLayout.PREFERRED_SIZE, 76, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(20, 20, 20)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(ordenacaoComboBox, javax.swing.GroupLayout.PREFERRED_SIZE, 20, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(servicosLabel)
                        .addComponent(ordenacaoLabel)))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(servicosScrollPane, javax.swing.GroupLayout.DEFAULT_SIZE, 186, Short.MAX_VALUE)
                .addGap(18, 18, 18)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(contatarButton)
                    .addComponent(favoritoToggleButton))
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void servicosJListMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_servicosJListMouseClicked
        if (evt.getClickCount() == 2) {
             int index = servicosJList.locationToIndex(evt.getPoint());
             JOptionPane.showMessageDialog(this, "Abrir pop-up do serviço " + servicosJList.getSelectedValue());
          }
    }//GEN-LAST:event_servicosJListMouseClicked

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(EmpresaFrame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(EmpresaFrame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(EmpresaFrame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(EmpresaFrame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>
        //</editor-fold>
        //</editor-fold>
        //</editor-fold>
       
        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            @Override
            public void run() {
                new EmpresaFrame().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton contatarButton;
    private javax.swing.JLabel descricaoLabel;
    private javax.swing.JScrollPane descricaoScrollPane;
    private javax.swing.JTextArea descricaoTextArea;
    private javax.swing.JToggleButton favoritoToggleButton;
    private javax.swing.JLabel info1Label;
    private javax.swing.JLabel info2Label;
    private javax.swing.JLabel info3Label;
    private javax.swing.JLabel info4Label;
    private javax.swing.JLabel info5Label;
    private javax.swing.JLabel info6Label;
    private javax.swing.JLabel info7Label;
    private javax.swing.JLabel info8Label;
    private javax.swing.JComboBox<String> ordenacaoComboBox;
    private javax.swing.JLabel ordenacaoLabel;
    private javax.swing.JList<String> servicosJList;
    private javax.swing.JLabel servicosLabel;
    private javax.swing.JScrollPane servicosScrollPane;
    private javax.swing.JLabel tituloLabel;
    // End of variables declaration//GEN-END:variables

    private int id;
    private String nome;
    private int areaDeAtuacaoId;
    private String descricao;
    private ArrayList<ServicoFrame> servicosList = new ArrayList<>();

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public int getAreaDeAtuacaoId() {
        return areaDeAtuacaoId;
    }

    public void setAreaDeAtuacaoId(int areaDeAtuacaoId) {
        this.areaDeAtuacaoId = areaDeAtuacaoId;
    }

    public String getDescricao() {
        return descricao;
    }

    public void setDescricao(String descricao) {
        this.descricao = descricao;
    }
    
    public ArrayList<ServicoFrame> getServicosList() {
        return servicosList;
    }
}