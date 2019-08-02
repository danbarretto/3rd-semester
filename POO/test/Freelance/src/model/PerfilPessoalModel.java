
package model;

import java.sql.SQLException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JOptionPane;
import controller.Persist;
/**
 * Classe responsável pelo manejamento dos dados do perfil pessoal entre programa e banco de dados
 * @author daniel
 */
public class PerfilPessoalModel {
    private ConnectionDb cdb;
    
    /**
     * Atualiza informações do perfil pessoal de acordo com o que foi passado para a classe de Persistência
     */
    public void updatePerfilPessoal(){
        try {
            cdb = new ConnectionDb();
            cdb.insertQuery("UPDATE perfil set name='"+Persist.getPerfilModel().getNome()+"',"
                    + "cep='"+Persist.getPerfilModel().getCep()+"',"
                    + "cidade='"+Persist.getPerfilModel().getCidade()+"',"
                    + "estado='"+Persist.getPerfilModel().getEstado()+"' WHERE cpf_cnpj='"+controller.Persist.getPerfilModel().getCpf_cnpj()+"'");
            cdb.getCon().close();
            JOptionPane.showMessageDialog(null, "Perfil alterado com sucesso");
        } catch (SQLException ex) {
            Logger.getLogger(PerfilProfissionalModel.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
