
package model;

/**
 * Classe responsável pelo manejamento de dados de usuários entre programa e bd
 * @author lucas
 */

import controller.Persist;
import java.sql.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import controller.Usuario;

public class UsuarioModel {
    private ConnectionDb cdb;
    
    /**
     * Construtor
     * @param cdb objeto da classe de conexão
     */
    public UsuarioModel(ConnectionDb cdb) {
        this.cdb = cdb;
    }
    
    public void selectUsuarios(){
        
    }
    
    /**
     * Popula a lista de usuários selecionados por tipo de permissão (1 = pessoa física/2 = pessoa jurídica)
     * @param tipo
     */
    public void populateUsuarios(int tipo){
        try {
            if(tipo != 1 && tipo != 2)
                throw new IllegalArgumentException("Tipo de usuário inválido");
            
            String queryUsuarios = "SELECT * FROM usuario WHERE permission = " + tipo + " ORDER BY email";
            ResultSet rs = cdb.selectQuery(queryUsuarios);
            while(rs.next()){
                Usuario usuario = new Usuario(
                        rs.getInt("permission"),
                        rs.getString("cpf_cnpj"),
                        rs.getString("email"),
                        rs.getString("password")
                );
                
                Persist.getListUsuarios().add(usuario);
            }
            cdb.getCon().close();
        } catch (SQLException ex) {
            Logger.getLogger(ServicoModel.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IllegalArgumentException ex) {
            Logger.getLogger(ServicoModel.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
