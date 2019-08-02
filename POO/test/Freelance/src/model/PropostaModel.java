
package model;

import controller.Persist;
import controller.ServicoController;
import java.sql.SQLException;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Classe responsável pelo manejamento de dados das propostas entre programa e banco de dados
 * @author daniel
 */
public class PropostaModel {
    private ConnectionDb cdb;
    
    /**
     * Insere uma nova proposta de acordo com o serviço passado e as informações que estão na persistência
     * @param sc
     */
    public void enviarProposta(ServicoController sc){
        try {
            cdb = new ConnectionDb();
            String query = "INSERT INTO proposta(fk_idServico, emailDest,emailEnvio, visualizado) VALUES ("+sc.getId()+",'"+sc.getEmailEmpresa()+"','"+Persist.getUser().getEmail()+"',0)";
            cdb.insertQuery(query);
            cdb.getCon().close();
        } catch (SQLException ex) {
            Logger.getLogger(PropostaModel.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    
}
