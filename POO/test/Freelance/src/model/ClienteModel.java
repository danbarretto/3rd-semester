
package model;

/**
 * Classe responsável pelo manejamento de dados de clientes entre programa e banco de dados
 * @author lucas
 */

import controller.Perfil;
import controller.Persist;
import java.sql.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import controller.Usuario;
import java.util.List;

public class ClienteModel {
    private ConnectionDb cdb;
    
    public ClienteModel(ConnectionDb cdb) {
        this.cdb = cdb;
    }
    
    public void selectClientes(){
        
    }
    
    /**
     * Popula lista de usuários com o mesmo tipo de 
     * @param listUsuarios
     */
    public void populateClientes(List<Usuario> listUsuarios){
        try {          
            for(Usuario usuario : listUsuarios) {
                String query = "SELECT * FROM perfil WHERE cpf_cnpj = " + usuario.getCpf_cnpj()+ " ORDER BY name";
                ResultSet rs = cdb.selectQuery(query);
                
                Perfil cliente = new Perfil(
                    rs.getString("nome"),
                    rs.getString("cpf_cnpj"),
                    rs.getString("university"),
                    rs.getString("professionalDesc"),
                    rs.getString("birthday"),
                    rs.getString("escolaridade"),
                    rs.getString("cidade"),
                    rs.getString("cep"),
                    rs.getString("experiencia"),
                    rs.getString("motivacao"),
                    rs.getString("especializacao"),
                    rs.getString("areaAtuacao"),
                    rs.getInt("anoFormacao"),
                    rs.getString("estado")
                );

                Persist.getListClientes().add(cliente);
            }
            
            cdb.getCon().close();
        } catch (SQLException ex) {
            Logger.getLogger(ServicoModel.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
