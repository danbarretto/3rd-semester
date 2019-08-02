
package model;

/**
 * Classe responsável pelo manejamento de dados de serviçoi entre programa e banco de dados
 * @author daniel
 */

import controller.EmpresaController;
import controller.Persist;
import java.sql.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import controller.ServicoController;

public class ServicoModel {
    private ConnectionDb cdb;
    
    /**
     * Construtor
     * @param cdb objeto da classe de conexão
     */
    public ServicoModel(ConnectionDb cdb) {
        this.cdb = cdb;
    }
    
    public void selectServicos() {
        
    }
    
    /**
     * Popula lista de serviços de cada empresa presente na lista de empresas na classe de persistência
     */
    public void populateServicos() {
        try {
            for(EmpresaController empresa : Persist.getListEmpresas()) {
                String query = "SELECT * FROM servico WHERE emailEmpresa = '" + empresa.getUsuario().getEmail() + "' ORDER BY categorias";
                ResultSet rs = cdb.selectQuery(query);
                while(rs.next()) {
                    ServicoController servico = new ServicoController(
                            rs.getString("descricao"),
                            rs.getString("servico"),
                            rs.getString("dataAnuncio"),
                            rs.getString("cidade"),
                            rs.getString("estado"),
                            rs.getString("emailEmpresa"),
                            rs.getString("entrega"),
                            rs.getString("categorias"),
                            rs.getFloat("valor"),
                            rs.getBoolean("presenca"),
                            rs.getBoolean("transporte"),
                            rs.getInt("id"),
                            rs.getString("nomeEmpresa")
                    );

                    empresa.getListServicos().add(servico);
                }
            }
            
            cdb.getCon().close();
        } catch (SQLException ex) {
            Logger.getLogger(ServicoModel.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
