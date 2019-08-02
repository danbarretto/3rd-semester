
package model;

import controller.Perfil;
import controller.Persist;
import controller.Usuario;
import java.sql.SQLException;
import java.util.Date;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JOptionPane;
import java.sql.*;
/**
 * Classe responsável pelo manejamento de novos usuários entre o programa e o bd
 * @author daniel
 */
public class CriarContaModel {
   
    private ConnectionDb cdb = new ConnectionDb();
    
    /**
     * Cadastra novo usuário no banco de dados de acordo com os dados na persistência
     * @return true para sucesso, false para erro
     */
    public boolean cadastraUsuario(){
        try {
            Usuario user = Persist.getUser();
            Perfil pm = Persist.getPerfilModel();
            ResultSet rs = cdb.selectQuery("SELECT * from perfil where cpf_cnpj='"+pm.getCpf_cnpj()+"';");
            if(rs.next()){
                JOptionPane.showMessageDialog(null, "CPF/CNPJ já cadastrado"); //Cpf_Cnpj deve ser único
                return false;
            }
            cdb.getCon().close();
            rs = cdb.selectQuery("SELECT * from usuario where email='"+user.getEmail()+"';");
            if(rs.next()){
                JOptionPane.showMessageDialog(null, "Email já cadastrado"); //Email deve ser único
                return false;
            }
            cdb.getCon().close();
            //Primeiro cadastra-se o perfil para depois cadastrar o usuário
            cdb.insertQuery("INSERT INTO perfil(name, birthday, cpf_cnpj, university, professionalDesc) VALUES('"+pm.getNome()+"','"+pm.getDataNasc()+"','"+pm.getCpf_cnpj()+"','"+pm.getUniversidade()+"','"+pm.getDescricaoProf()+"')");
            cdb.getCon().close();
            String secPass = SecurePassword.securePassword(user.getSenha());
            cdb.insertQuery("INSERT INTO usuario(permission, email, password, cpf_cnpj) VALUES("+user.getPermissao()+",'"+user.getEmail()+"','"+secPass+"','"+user.getCpf_cnpj()+"');");
            cdb.getCon().close();
            JOptionPane.showMessageDialog(null, "Conta criada com sucesso!");
        } catch (SQLException ex) {
            Logger.getLogger(CriarContaModel.class.getName()).log(Level.SEVERE, null, ex);
            JOptionPane.showMessageDialog(null, "Erro ao criar conta:\n"+ex.getMessage());
        }
        return true;
    }
}
