
package model;

import controller.NotificacaoController;
import controller.Persist;
import controller.ServicoController;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Classe responsável por manejar propostas de serviços (notificações) entre programa e banco de dados
 * @author daniel
 */
public class NotificacaoModel {
    
    private ConnectionDb cdb;
    
    /**
     * Popula lista de notificações com resultados do banco de dados
     */
    public void populateNotificacoes(){
        try {
            cdb = new ConnectionDb();
            ResultSet rs = cdb.selectQuery("SELECT * FROM servico LEFT JOIN proposta ON servico.id=proposta.fk_idServico AND proposta.emailDest='"+Persist.getUser().getEmail()+"' AND proposta.visualizado=false");
            NotificacaoController nc = new NotificacaoController();
            while(rs.next()){
                
                ServicoController sc = new ServicoController(
                        rs.getString("descricao"),
                        rs.getString("servico"),
                        rs.getString("dataAnuncio"),
                        rs.getString("cidade"),
                        rs.getString("estado"),
                        rs.getString("emailEmpresa"),
                        rs.getString("entrega"),
                        rs.getString("categorias"),
                        rs.getString("nomeEmpresa"),
                        rs.getInt("id"),
                        rs.getBoolean("presenca"),
                        rs.getBoolean("transporte"));
                nc.setServicoController(sc);
                nc.setEmailRemetente(rs.getString("emailEnvio"));
            }
            cdb.getCon().close();
            
            Persist.getListNotificacao().add(nc);
        } catch (SQLException ex) {
            Logger.getLogger(NotificacaoModel.class.getName()).log(Level.SEVERE, null, ex);
        }
        
    }
    
    /**
     * Altera status da notificação de visualizado para verdadeiro para então não precisar ser carregada novamente 
     * @param nc Informações da notificação a ser alterada
     */
    public void dismissNotificacao(NotificacaoController nc){
        try {
            cdb = new ConnectionDb();
            String query ="update proposta set visualizado=true where fk_idServico="+nc.getServicoController().getId();
            System.out.println(query);
            cdb.insertQuery(query);
            cdb.getCon().close();
            
        } catch (SQLException ex) {
            Logger.getLogger(NotificacaoModel.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
}
