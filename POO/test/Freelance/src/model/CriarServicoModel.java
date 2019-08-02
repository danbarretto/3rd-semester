
package model;

/**
 * Classe responsável pelo manejamento de novos serviços entre o programa e o bd
 * @author daniel
 */
import controller.Persist;
import controller.ServicoController;
import java.sql.SQLException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JOptionPane;
public class CriarServicoModel {
    
    private ConnectionDb cdb;
    
    /**
     * Registra novos serrviços no banco de dados
     * @param sc Informações do serviço a serem cadastradas
     */
    public void createServico(ServicoController sc){
        try {
            String query = "INSERT INTO servico(descricao,valor,nomeEmpresa, servico,"
                    + " dataAnuncio, cidade, estado, emailEmpresa, entrega, presenca,"
                    + " transporte, categorias)"
                    + " VALUES ('"+sc.getDescricao()+"',"
                    + ""+sc.getValor()+","
                    + "'"+Persist.getPerfilModel().getNome()+"',"
                    + "'"+sc.getServico()+"',"
                    + "'"+sc.getDataAnuncio()+"',"
                    + "'"+sc.getCidade()+"',"
                    + "'"+sc.getEstado()+"',"
                    + "'"+sc.getEmailEmpresa()+"',"
                    + "'"+sc.getEntrega()+"',"
                    + ""+sc.isPresenca()+","
                    + ""+sc.isTransporte()+","
                    + "'"+sc.getCategorias()+"')";
            cdb = new ConnectionDb();
            cdb.insertQuery(query);
            cdb.getCon().close();
            JOptionPane.showMessageDialog(null, "Serviço criado com sucesso!");
        } catch (SQLException ex) {
            Logger.getLogger(CriarServicoModel.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
}
