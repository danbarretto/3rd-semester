
package model;

/**
 * Classe responsável pelo manejamento de empresas entre o programa e o bd
 * @author lucas
 */

import controller.EmpresaController;
import controller.Perfil;
import controller.Persist;
import java.sql.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import controller.Usuario;
import java.util.List;

public class EmpresaModel {
    private ConnectionDb cdb;
    
    /**
     * Construtor
     * @param cdb objeto da Classe de conexão a ser usado
     */
    public EmpresaModel(ConnectionDb cdb) {
        this.cdb = cdb;
    }
    
    public void selectEmpresas(){
        
    }
    
    /**
     * Seleciona todas as empresas da lista de usuário e as adiciona na lista na classe de persistência
     */
    public void populateEmpresas(){
        try {          
            for(Usuario usuario : Persist.getListUsuarios()) {
                if(usuario.getPermissao() != 2)//Caso usuário não for pessoa jurídica
                    continue;
                    
                String query = "SELECT * FROM perfil WHERE cpf_cnpj = '" + usuario.getCpf_cnpj() + "'";
                ResultSet rs = cdb.selectQuery(query);
                rs.next();
                
                System.out.println(query);
                
                Perfil perfil = new Perfil(
                    rs.getString("name"),
                    rs.getString("cpf_cnpj"),
                    rs.getString("cidade"),
                    rs.getString("cep"),
                    rs.getString("motivacao"),
                    rs.getString("especializacao"),
                    rs.getString("areaAtuacao"),
                    rs.getString("estado")
                );
                //Novo perfil carregado
                usuario.setPerfil(perfil);
                EmpresaController empresa = new EmpresaController(usuario);
                Persist.getListEmpresas().add(empresa); //Adição da empresa na persistência
            }
            
            cdb.getCon().close();
        } catch (SQLException ex) {
            Logger.getLogger(ServicoModel.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
