
package model;

import controller.Persist;
import java.sql.SQLException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JOptionPane;

/**
 * Classe responsável pelo manejamento de dados do perfil profissional entre o programa e o banco de dados
 * @author daniel
 */
public class PerfilProfissionalModel {
    
    private ConnectionDb cdb;

    /**
     * Atualiza perfil pessoal de acordo com o que foi passado para a classe de persistência
     */
    public void updatePerfilProfissional(){
        try {
            cdb = new ConnectionDb();
            cdb.insertQuery("UPDATE perfil set escolaridade='"+Persist.getPerfilModel().getEscolaridade()+
                    "', anoFormacao="+Persist.getPerfilModel().getAnoFormacao()+
                    ", especializacao='"+Persist.getPerfilModel().getEspecializacao()+
                    "', experiencias='"+Persist.getPerfilModel().getExperiencia()+
                    "', motivacao='"+Persist.getPerfilModel().getMotivacoes()+
                    "', university='"+Persist.getPerfilModel().getUniversidade()+
                    "', professionalDesc='"+Persist.getPerfilModel().getDescricaoProf()+
                    "' WHERE cpf_cnpj='"+Persist.getPerfilModel().getCpf_cnpj()+"'");
            cdb.getCon().close();
            JOptionPane.showMessageDialog(null, "Perfil alterado com sucesso");
        } catch (SQLException ex) {
            Logger.getLogger(PerfilProfissionalModel.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
}
