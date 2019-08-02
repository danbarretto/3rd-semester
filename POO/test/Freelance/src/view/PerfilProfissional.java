
package view;

import javax.swing.DefaultComboBoxModel;
import controller.Persist;
import model.PerfilProfissionalModel;

/**
 * Classe responsável pelo manejamento do forms de perfil pessoal
 * @author lucas
 */
public class PerfilProfissional extends javax.swing.JPanel {
   
    /**
     * Creates new form PerfilPessoal
     */
    public PerfilProfissional() {
        initComponents();
        txtArea.setText(Persist.getPerfilModel().getAreaAtuacao());
        txtDesc.setText(Persist.getPerfilModel().getDescricaoProf());
        txtEspecializacao.setText(Persist.getPerfilModel().getEspecializacao());
        txtUniversidade.setText(Persist.getPerfilModel().getUniversidade());
        txtExp.setText(Persist.getPerfilModel().getExperiencia());
        txtMotivacao.setText(Persist.getPerfilModel().getMotivacoes());
        DefaultComboBoxModel model = (DefaultComboBoxModel) comboEsc.getModel();
        comboEsc.setSelectedIndex(model.getIndexOf(Persist.getPerfilModel().getEscolaridade()));
        dataTxt.setText(String.valueOf(Persist.getPerfilModel().getAnoFormacao()));
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jLabel1 = new javax.swing.JLabel();
        jLabel2 = new javax.swing.JLabel();
        dataTxt = new javax.swing.JTextField();
        jLabel3 = new javax.swing.JLabel();
        txtEspecializacao = new javax.swing.JTextField();
        jLabel4 = new javax.swing.JLabel();
        comboEsc = new javax.swing.JComboBox<>();
        jScrollPane1 = new javax.swing.JScrollPane();
        txtMotivacao = new javax.swing.JTextArea();
        jLabel6 = new javax.swing.JLabel();
        jLabel7 = new javax.swing.JLabel();
        jScrollPane2 = new javax.swing.JScrollPane();
        txtExp = new javax.swing.JTextArea();
        desbloquearToggleButton = new javax.swing.JToggleButton();
        descartarButton = new javax.swing.JButton();
        salvarButton = new javax.swing.JButton();
        jScrollPane3 = new javax.swing.JScrollPane();
        txtDesc = new javax.swing.JTextArea();
        jLabel8 = new javax.swing.JLabel();
        txtArea = new javax.swing.JTextField();
        jLabel5 = new javax.swing.JLabel();
        txtUniversidade = new javax.swing.JTextField();

        jLabel1.setText("Escolaridade:");

        jLabel2.setText("Ano de formação:");

        dataTxt.setEditable(false);
        dataTxt.setPreferredSize(new java.awt.Dimension(90, 32));

        jLabel3.setText("Área de atuação");

        txtEspecializacao.setEditable(false);
        txtEspecializacao.setPreferredSize(new java.awt.Dimension(90, 32));

        jLabel4.setText("Especialização:");

        comboEsc.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "Ensino Médio", "Ensino Superior", "Mestrado", "Doutorado" }));
        comboEsc.setPreferredSize(new java.awt.Dimension(101, 32));

        txtMotivacao.setEditable(false);
        txtMotivacao.setColumns(20);
        txtMotivacao.setRows(5);
        jScrollPane1.setViewportView(txtMotivacao);

        jLabel6.setText("Experiências:");

        jLabel7.setText("Motivação:");

        txtExp.setEditable(false);
        txtExp.setColumns(20);
        txtExp.setRows(5);
        jScrollPane2.setViewportView(txtExp);

        desbloquearToggleButton.setText("Desbloquear");
        desbloquearToggleButton.addItemListener(new java.awt.event.ItemListener() {
            public void itemStateChanged(java.awt.event.ItemEvent evt) {
                desbloquearToggleButtonItemStateChanged(evt);
            }
        });
        desbloquearToggleButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                desbloquearToggleButtonActionPerformed(evt);
            }
        });

        descartarButton.setText("Descartar alterações");
        descartarButton.setEnabled(false);

        salvarButton.setText("Salvar");
        salvarButton.setEnabled(false);
        salvarButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                salvarButtonActionPerformed(evt);
            }
        });

        txtDesc.setEditable(false);
        txtDesc.setColumns(20);
        txtDesc.setRows(5);
        jScrollPane3.setViewportView(txtDesc);

        jLabel8.setText("Descrição profissional:");

        txtArea.setEditable(false);

        jLabel5.setText("Universidade:");

        txtUniversidade.setEditable(false);
        txtUniversidade.setPreferredSize(new java.awt.Dimension(90, 32));

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jScrollPane3, javax.swing.GroupLayout.Alignment.TRAILING)
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                        .addGap(0, 0, Short.MAX_VALUE)
                        .addComponent(desbloquearToggleButton)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(descartarButton)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(salvarButton))
                    .addComponent(jScrollPane1)
                    .addComponent(jScrollPane2, javax.swing.GroupLayout.Alignment.TRAILING)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(jLabel6)
                        .addGap(0, 0, Short.MAX_VALUE))
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                            .addGroup(layout.createSequentialGroup()
                                .addComponent(jLabel8)
                                .addGap(135, 135, 135)
                                .addComponent(jLabel5)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(txtUniversidade, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                            .addGroup(layout.createSequentialGroup()
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                                    .addGroup(layout.createSequentialGroup()
                                        .addComponent(jLabel3)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(txtArea))
                                    .addGroup(layout.createSequentialGroup()
                                        .addComponent(jLabel1)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(comboEsc, javax.swing.GroupLayout.PREFERRED_SIZE, 130, javax.swing.GroupLayout.PREFERRED_SIZE))
                                    .addComponent(jLabel7))
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 61, Short.MAX_VALUE)
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                                    .addGroup(layout.createSequentialGroup()
                                        .addComponent(jLabel2)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(dataTxt, javax.swing.GroupLayout.PREFERRED_SIZE, 180, javax.swing.GroupLayout.PREFERRED_SIZE))
                                    .addGroup(layout.createSequentialGroup()
                                        .addComponent(jLabel4)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(txtEspecializacao, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)))))
                        .addGap(0, 10, Short.MAX_VALUE)))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel1)
                    .addComponent(dataTxt, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jLabel2)
                    .addComponent(comboEsc, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(18, 18, 18)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel3)
                    .addComponent(txtEspecializacao, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jLabel4)
                    .addComponent(txtArea, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(jLabel8)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED))
                    .addGroup(layout.createSequentialGroup()
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(txtUniversidade, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(jLabel5))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 8, Short.MAX_VALUE)))
                .addComponent(jScrollPane3, javax.swing.GroupLayout.PREFERRED_SIZE, 46, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jLabel6)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jScrollPane2, javax.swing.GroupLayout.PREFERRED_SIZE, 117, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jLabel7)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 117, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(descartarButton)
                    .addComponent(salvarButton)
                    .addComponent(desbloquearToggleButton))
                .addContainerGap())
        );
    }// </editor-fold>//GEN-END:initComponents

    private void desbloquearToggleButtonItemStateChanged(java.awt.event.ItemEvent evt) {//GEN-FIRST:event_desbloquearToggleButtonItemStateChanged
        //Altera propriedade Enabled dos campos para permitir ou não edição
        if(desbloquearToggleButton.isSelected()) {
            desbloquearToggleButton.setText("Bloquear");
            descartarButton.setEnabled(true);
            salvarButton.setEnabled(true);
        } else {
            desbloquearToggleButton.setText("Desbloquear");
            descartarButton.setEnabled(false);
            salvarButton.setEnabled(false);
        }
    }//GEN-LAST:event_desbloquearToggleButtonItemStateChanged

    private void salvarButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_salvarButtonActionPerformed
        //Salva as informações editadas na persistência e no banco de dados
        desbloquearToggleButton.setSelected(false);
        Persist.getPerfilModel().setAnoFormacao(Integer.parseInt(dataTxt.getText()));
        Persist.getPerfilModel().setAreaAtuacao(txtArea.getText());
        Persist.getPerfilModel().setDescricaoProf(txtDesc.getText());
        Persist.getPerfilModel().setEscolaridade(comboEsc.getSelectedItem().toString());
        Persist.getPerfilModel().setEspecializacao(txtEspecializacao.getText());
        Persist.getPerfilModel().setExperiencia(txtExp.getText());
        Persist.getPerfilModel().setMotivacoes(txtMotivacao.getText());
        Persist.getPerfilModel().setUniversidade(txtUniversidade.getText());
        PerfilProfissionalModel pfm = new PerfilProfissionalModel();
        pfm.updatePerfilProfissional();
    }//GEN-LAST:event_salvarButtonActionPerformed

    private void desbloquearToggleButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_desbloquearToggleButtonActionPerformed
        //Altera propriedade de editable dos campos abaixo
        txtArea.setEditable(!txtArea.isEditable());
        txtDesc.setEditable(!txtDesc.isEditable());
        txtEspecializacao.setEditable(!txtEspecializacao.isEditable());
        txtExp.setEditable(!txtExp.isEditable());
        txtMotivacao.setEditable(!txtMotivacao.isEditable());
        dataTxt.setEditable(!dataTxt.isEditable());
        comboEsc.setEditable(!comboEsc.isEditable());
        txtUniversidade.setEditable(!txtUniversidade.isEditable());
    }//GEN-LAST:event_desbloquearToggleButtonActionPerformed


    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JComboBox<String> comboEsc;
    private javax.swing.JTextField dataTxt;
    private javax.swing.JToggleButton desbloquearToggleButton;
    private javax.swing.JButton descartarButton;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JLabel jLabel5;
    private javax.swing.JLabel jLabel6;
    private javax.swing.JLabel jLabel7;
    private javax.swing.JLabel jLabel8;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JScrollPane jScrollPane2;
    private javax.swing.JScrollPane jScrollPane3;
    private javax.swing.JButton salvarButton;
    private javax.swing.JTextField txtArea;
    private javax.swing.JTextArea txtDesc;
    private javax.swing.JTextField txtEspecializacao;
    private javax.swing.JTextArea txtExp;
    private javax.swing.JTextArea txtMotivacao;
    private javax.swing.JTextField txtUniversidade;
    // End of variables declaration//GEN-END:variables
}